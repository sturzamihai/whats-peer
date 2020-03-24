#include "Blockchain.h"

Blockchain::Blockchain(uint32_t difficulty) {
    _Chain.emplace_back(Block(0, "Genesis Block"));
    _Difficulty = difficulty;
}

void Blockchain::AddBlock(Block nBlock) {
    nBlock.PrevHash = _GetLastBlock().GetHash();
    nBlock.MineBlock(_Difficulty);
    _Chain.push_back(nBlock);
}

Block Blockchain::_GetLastBlock() const {
    return _Chain.back();
}
