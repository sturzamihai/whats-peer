#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H

#include <cstdint>
#include <iostream>

class Block {
    // TODO: Create block class
public:
    string PrevHash;
    Block(uint32_t IndexIn,const string &DataIn);
    string GetHash();
    void MineBlock(uint32_t Difficulty);

private:
    uint32_t _Index;
    int64_t _Nonce;
    string _Data;
    string _Hash;
    time_t _Time;

    string _CalculateHash() const;
};

#endif //BLOCKCHAIN_BLOCK_H

