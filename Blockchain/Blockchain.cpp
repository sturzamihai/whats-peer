#include "Blockchain.h"
#include <iostream>


Block Blockchain::GetLast() {
    if (_Node.empty()) {
    } else {
        return _Node.back(); // We fetch the latest block that was added to our node
    }
}

void Blockchain::AddBlock(Block NewBlock) {
    _Node.push_back(NewBlock); // We are adding a new block to the node
}
