#ifndef WHATS_PEER_RSA_H
#define WHATS_PEER_RSA_H

#include <cstdint>
#include <string>

class RSA {
public:
    RSA();

    std::string Encrypt(std::string data, uint64_t publicKey); // TODO(Mihai): Make them static
    std::string Decrypt(std::string data, uint64_t privateKey);

private:
    uint64_t _p;
    uint64_t _q;

    uint64_t _n;
    uint64_t _phi;

    uint64_t _e;
    uint64_t _d;

    static bool _IsPrime(uint64_t n);

    static uint64_t _CalculateD(uint64_t e, uint64_t t);

    uint64_t _CalculateEncryption(uint64_t d, uint64_t key, uint64_t n);
};


#endif //WHATS_PEER_RSA_H
