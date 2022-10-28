#ifndef WHATS_PEER_RSA_H
#define WHATS_PEER_RSA_H

#include <cstdint>
#include <string>

struct Keychain {
    std::string publicKey;
    std::string privateKey;
};

class RSA {
public:
    RSA();

    static std::string Encrypt(std::string data, std::string publicKey);

    static std::string Decrypt(std::string data, std::string privateKey);

    Keychain ShowKeys();

private:
    uint64_t _p;
    uint64_t _q;

    uint64_t _n;
    uint64_t _phi;

    uint64_t _e;
    uint64_t _d;

    static bool _IsPrime(uint64_t n);

    static uint64_t _CalculateD(uint64_t e, uint64_t t);

    static uint64_t _CalculateEncryption(uint64_t d, uint64_t key, uint64_t n);

    static std::tuple<uint64_t, uint64_t> _HandleKeys(std::string key);

    std::string _CreateKey(uint64_t n, uint64_t k);
};


#endif //WHATS_PEER_RSA_H
