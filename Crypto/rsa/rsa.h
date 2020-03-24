//
// Created by sturzamihai on 24.03.2020.
//

#ifndef WHATS_PEER_RSA_H
#define WHATS_PEER_RSA_H

#include <cstdint>

class RSA {
private:
    uint32_t p;
    uint32_t q;

    bool _IsPrime(double x);
};


#endif //WHATS_PEER_RSA_H
