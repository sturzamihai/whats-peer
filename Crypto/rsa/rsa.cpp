#include "rsa.h"
#include <ctime>
#include <iostream>
#include <random>
#include <algorithm>
#include <string>
#include <boost/math/common_factor.hpp>
#include "../Utils/base64/base64.h"
#include <boost/lexical_cast.hpp>
#include <tuple>

template<typename T>
T modpow(T base, T exp, T modulus) {
    base %= modulus;
    T result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}

bool RSA::_IsPrime(uint64_t n) {
    if (n <= 3)
        return n > 1;
    else if (n % 2 == 0 || n % 3 == 0)
        return false;

    uint64_t i = 5;

    while (i * i <= n) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
        i = i + 6;
    }

    return true;
}

uint64_t RSA::_CalculateD(uint64_t e, uint64_t t) {
    e = e % t;
    for (uint64_t x = 1; x < t; x++)
        if ((e * x) % t == 1)
            return x;
}

uint64_t RSA::_CalculateEncryption(uint64_t d, uint64_t key, uint64_t n) {
    uint64_t res = modpow<uint64_t>(d, key, n); // calculate the encrypted value
    return res;
}

std::string RSA::Encrypt(const std::string data, std::string publicKey) {
    auto keys = _HandleKeys(publicKey);
    uint64_t n = std::get<0>(keys);
    uint64_t k = std::get<1>(keys);

    std::vector<uint64_t> values;
    uint64_t maxlen = 0, currlen = 0;
    // add every encrypted character into our vector and determine the max length
    for (uint64_t i = 0; i < data.length(); i++) { // iterate the message
        values.push_back(_CalculateEncryption(data[i], k, n));
        currlen = std::to_string(values.back()).length();
        if (currlen > maxlen) maxlen = currlen;
    }

    std::string encrypted = "";
    encrypted.append(std::to_string(maxlen));
    encrypted.append("s");
    for (uint64_t i = 0; i < values.size(); i++) {
        // pad the encrypted data with 0 in the beginning until required size is met
        currlen = std::to_string(values[i]).length();
        if (currlen < maxlen) {
            for (uint64_t j = currlen; j < maxlen; j++) {
                encrypted.append("0");
            }
            encrypted.append(std::to_string(values[i])); // add the rest of the data in the final string
        } else {
            encrypted.append(std::to_string(values[i]));
        }
    }

    return base64_encode(reinterpret_cast<const unsigned char *>(encrypted.c_str()),
                         encrypted.size()); // export it as base64
}

std::tuple<uint64_t, uint64_t> RSA::_HandleKeys(std::string key) {
    key = base64_decode(key);
    try {
        uint64_t n = boost::lexical_cast<uint64_t>(key.substr(1, key.find(",") - 1));
        key.pop_back();
        key.erase(0, key.find(",") + 1);
        uint64_t k = boost::lexical_cast<uint64_t>(key);
        return std::make_tuple(n, k);
    }
    catch (boost::bad_lexical_cast) {
        throw std::runtime_error("Invalid key format. Expected a tuple from N and key.");
    }
}

std::string RSA::Decrypt(const std::string data, std::string privateKey) {
    std::string encrypted = base64_decode(data);
    auto keys = _HandleKeys(privateKey);
    uint64_t n = std::get<0>(keys);
    uint64_t k = std::get<1>(keys);
    // find the sequence pattern
    uint64_t seq = boost::lexical_cast<uint64_t>(encrypted.substr(0, encrypted.find("s")));
    encrypted.erase(0, encrypted.find("s") + 1);
    std::string decrypted = "";
    // explore sequences until the end of the file
    while (encrypted.length() > 0) {
        decrypted.append(std::string(1, (char) _CalculateEncryption(
                boost::lexical_cast<uint64_t>(encrypted.substr(0, seq)), k,
                n))); // add them to the decrypted string
        encrypted.erase(0, seq);
    }
    return decrypted; // return the final string
}

Keychain RSA::ShowKeys() {
    Keychain final;
    final.publicKey = _CreateKey(_n, _e);
    final.privateKey = _CreateKey(_n, _d);
    return final;
}

std::string RSA::_CreateKey(uint64_t n, uint64_t k) {
    std::string pair;
    pair.append("("), pair.append(std::to_string(n));
    pair.append(","), pair.append(std::to_string(k)), pair.append(")");
    return base64_encode(reinterpret_cast<const unsigned char *>(pair.c_str()),
                         pair.size());
}

RSA::RSA() {
    // create the prime number range
    std::vector<uint64_t> primes;
    for (uint64_t i = 6547; i <= 65537; i++) {
        if (_IsPrime(i)) {
            primes.push_back(i);
        }
    }

    // start a random engine and choose two prime numbers
    std::random_device rd; // C++11 random engine;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist;

    uint64_t ppoz, qpoz;
    ppoz = dist(gen, decltype(dist)::param_type{0, (int) primes.size()}); // find random values for p
    qpoz = dist(gen, decltype(dist)::param_type{0, (int) primes.size()}); // find random values for q

    // assign the new random values
    _p = primes[ppoz];
    _q = primes[qpoz];

    // compute the n
    _n = _p * _q;

    // find the phi, if _p and _q are prime that means we just need to find the lcm of the two and substracting 1
    _phi = boost::math::lcm(_p - 1, _q - 1);

    // searching for a good _e, 1<_e<_phi && gcd(_e,_phi) == 1
    _e = dist(gen, decltype(dist)::param_type{2, (int) _phi});
    while (_e < _phi) {
        if (boost::math::gcd((long) _e, (long) _phi) == 1)
            break;
        _e++;
    }

    // compute d - the modular multiplicative inverse of _e modulo _phi.
    _d = _CalculateD(_e, _phi);

}

