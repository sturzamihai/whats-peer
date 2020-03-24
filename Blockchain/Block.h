#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H
#include <cstdint>
#include <iostream>

class Block {
public:
    std::string PrevHash;
    Block(uint32_t IndexIn, const string &DataIn);
    std::string GetHash();
    void MineBlock(uint32_t Difficulty);

private:
    uint32_t _Index;
    int64_t _Nonce;
    std::string _Data;
    std::string _Hash;
    time_t _Time;
    std::string _CalculateHash() const;
};
#endif //BLOCKCHAIN_BLOCK_H


