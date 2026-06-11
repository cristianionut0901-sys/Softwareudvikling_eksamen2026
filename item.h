#include <string>
#include <iostream>

class item {
    public:
    std::string name;
    int health;
    int itemValue;
    int attack;

    item(std::string name_, int health_,int itemValue_, int attack_) : name(name_), health(health_), itemValue(itemValue_), attack(attack_){}


};