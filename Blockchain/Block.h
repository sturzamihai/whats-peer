#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H
#include <cstdint>
#include <iostream>

class Block {
public:
    Block(uint32_t index, const std::string data);

    std::string GetHash();

    uint32_t GetIndex();

    void MineBlock(uint32_t difficulty);

private:
    uint32_t _Index;
    int64_t _Nonce;
    std::string _PrevHash;
    std::string _Data;
    std::string _Hash;
    time_t _Time;
    std::string _CalculateHash() const;
};
#endif //BLOCKCHAIN_BLOCK_H


