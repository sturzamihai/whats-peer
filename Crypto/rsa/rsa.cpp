#include "rsa.h"
#include <ctime>
#include <iostream>
#include <random>
#include <algorithm>
#include <string>
#include <boost/math/common_factor.hpp>
#include "../Utils/base64/base64.h"
#include <boost/lexical_cast.hpp>

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
    uint64_t k = 1;
    while (k % e != 0) {
        k += t;
    }
    return k / e;
}

uint64_t RSA::_CalculateEncryption(uint64_t d, uint64_t key, uint64_t n) {
    uint64_t res = modpow<uint64_t>(d, key, n); // calculate the encrypted value
    std::cout << res << " " << std::endl;
    return res;
}

std::string RSA::Encrypt(const std::string data, uint64_t publicKey) {
    std::string encrypted = "";
    for (uint64_t i = 0; i < data.length(); i++) { // iterate the message
        encrypted.append(std::to_string(_CalculateEncryption(data[i], publicKey, _n))); // append changes
        encrypted.append(",");
    }
    return base64_encode(reinterpret_cast<const unsigned char *>(encrypted.c_str()), encrypted.size());
}

std::string RSA::Decrypt(const std::string data, uint64_t privateKey) {
    std::string encrypted = base64_decode(data);
    size_t poz = 0;
    std::string decrypted = "";
    while ((poz = encrypted.find(",")) != std::string::npos) {
        decrypted.append(std::string(1, (char) _CalculateEncryption(
                boost::lexical_cast<uint64_t>(encrypted.substr(0, poz)), privateKey, _n)));
        encrypted.erase(0, poz + 1);
    }
    return base64_encode(reinterpret_cast<const unsigned char *>(decrypted.c_str()), decrypted.size());
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

    std::cout << _e << " " << _d << " " << _n << std::endl;
}

