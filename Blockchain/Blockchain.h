#ifndef BLOCKCHAIN_BLOCKCHAIN_H
#define BLOCKCHAIN_BLOCKCHAIN_H

#include <cstdint>
#include <iostream>
#include <vector>
#include "Block.h"

class Blockchain {
public:

    Block GetLast();

    void AddBlock(Block NewBlock);

private:
    std::vector<Block> _Node = {};
};


#endif //BLOCKCHAIN_BLOCKCHAIN_H
