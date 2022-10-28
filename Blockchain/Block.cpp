#include <iostream>
#include "Block.h"
#include <sstream>
#include "../Crypto/sha256/sha256.h"

Block::Block(std::string index, std::string data, int64_t nonce, std::string prevHash, time_t timeStamp) {
    _Index = index;
    _Data = data;
    _Nonce = nonce;
    _PreviousHash = prevHash;
    _TimeStamp = timeStamp;
}

std::string Block::GenerateHash() {
    std::stringstream ss;
    ss << _Index << _Data << _Nonce << _PreviousHash << _TimeStamp;
    return sha256(ss.str());
}

std::string Block::GetPrevHash() {
    return _PreviousHash;
}
