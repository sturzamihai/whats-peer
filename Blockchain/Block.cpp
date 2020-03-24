#include "Block.h"
#include "sha256.h"
#include <sstream>
Block::Block(uint32_t IndexIn, const string &DataIn): _Index(IndexIn), _Data(DataIn){
    _Nonce = -1;
    _Time = time(nullptr);
}
string Block::GetHash() {
    return _Hash;
}
void Block::MineBlock(uint32_t Difficulty) {
    char cstr[Difficulty + 1];
    for(uint32_t i=0; i<Difficulty;++i){
        cstr[i]='0';
    }
    cstr[Difficulty]='\0';
    stirng str(cstr);
    do{
        _Nonce++;
        _Hash = _CalculateHash();
    }while(_Hash.substr(0,Difficulty)!=str);
    cout << "Block mined: " << _Hash << endl;
}
inline string Block::_CalculateHash() const {
    stringstream ss;
    ss << _Index << _Time << _Data << _Nonce << PrevHash;
    return sha256(ss.str());
}