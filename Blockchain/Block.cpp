#include "Block.h"
#include <sstream>
#include "sha256.h"

Block::Block(uint32_t index, const std::string data) : _Index(index), _Data(data) {
    _Nonce = -1;
    _Time = time(nullptr);
}

std::string Block::GetHash() {
    return _Hash;
}

uint32_t Block::GetIndex() {
    return _Index;
}

void Block::MineBlock(uint32_t difficulty) {
    char cstr[difficulty + 1];
    for (uint32_t i = 0; i < difficulty; ++i) {
        cstr[i] = '0';
    }
    cstr[difficulty] = '\0';
    std::string str(cstr);
    do {
        _Nonce++;
        _Hash = _CalculateHash();
    } while (_Hash.substr(0, difficulty) != str);
    std::cout << "Block mined: " << _Hash << std::endl;
}

inline std::string Block::_CalculateHash() const {
    std::stringstream ss;
    ss << _Index << _Time << _Data << _Nonce << _PrevHash;
    return sha256(ss.str());
}