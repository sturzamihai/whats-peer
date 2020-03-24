#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H
#include <cstdint>
#include <ctime>
#include <iostream>

class Block {
public:
    Block(std::string index, std::string data, int64_t nonce, std::string prevHash, time_t timeStamp);

    std::string GenerateHash();

    std::string GetPrevHash();

private:

    std::string _Index;
    std::string _Data;
    int64_t _Nonce;
    std::string _PreviousHash;
    time_t _TimeStamp;

};

#endif //BLOCKCHAIN_BLOCK_H


