#include <string>
#include <iostream>
#include <vector>
#include "Monster.h"

class cave {
    public:
    std::string name;
    std::vector<Monster> caveMonsters;
    
    cave(std::string name_) : name(name_){}

    std::string getCaveName(){
        return name;
    }

    std::vector<Monster> getCaveMonsters(){
        return caveMonsters;
    }
};