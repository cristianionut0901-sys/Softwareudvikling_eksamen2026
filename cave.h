#include <string>
#include <iostream>
#include <vector>
#include "Monster.h"
#include "item.h"


class cave {
    public:
    std::string name;
    std::vector<Monster> caveMonsters;
    std::vector<item> caveItems;
    
    cave(std::string name_) : name(name_){}

    std::string getCaveName(){
        return name;
    }

    std::vector<Monster>& getCaveMonsters() {
        return caveMonsters;
    }

    void addMonsterToCave(Monster monster){
        caveMonsters.push_back(monster);
    }
    void addItem(item item_){
        caveItems.push_back(item_);
    }
    std::vector<item> getCaveItems(){
        return caveItems;
    }
};