#include "Block.h"
#include <sstream>
#include "sha256.h"

Block::Block(uint32_t IndexIn, const std::string &DataIn) : _Index(IndexIn), _Data(DataIn) {
    _Nonce = -1;
    _Time = time(nullptr);
}

std::string Block::GetHash() {
    return _Hash;
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
    ss << _Index << _Time << _Data << _Nonce << PrevHash;
    return sha256(ss.str());
}