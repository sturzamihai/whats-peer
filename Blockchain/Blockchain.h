#ifndef BLOCKCHAIN_BLOCKCHAIN_H
#define BLOCKCHAIN_BLOCKCHAIN_H

#include <cstdint>
#include <vector>
#include "Block.h"

class Blockchain {
public:
    Blockchain(uint32_t difficulty);

    void AddBlock(Block nBlock);

private:
    uint32_t _Difficulty;
    std::vector<Block> _Chain;

    Block _GetLastBlock() const;
};

#endif //BLOCKCHAIN_BLOCKCHAIN_H
