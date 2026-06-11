#ifndef MONSTER_H
#define MONSTER_H
#include "item.h"
#include <string>
#include <iostream>
#include <vector>

class Monster {
    public:
    std::string name;
    int health;
    int maxHealth;
    int attack;
    std::vector<item> monsterItems;

    Monster(std::string name_, int health_, int attack_) : name(name_), health(health_), maxHealth(health_), attack(attack_){}

    void fullyHeal(){
        health = maxHealth;
    }

    void heal(int heal){
        health += heal;
        if (health > maxHealth)
        {
            health = maxHealth;
        }
    }
    std::string getName(){
        return name;
    }
    void damageTaken(int damage) {
        std::cout << name << " has taken "<< damage << " Damage" << std::endl;
        health -= damage;
    }

    int getCurrentHealth(){
        return health;
    }

    int getAttackDMG(){
        return attack;
    }

    void addItem(item theItem){
       monsterItems.push_back(theItem);
    }

    void removeItem(int choice){
        if (choice > 0 && choice <= monsterItems.size()) {
        monsterItems.erase(monsterItems.begin() + choice - 1);
        }
    }
    
    std::vector<item> getItems(){
        return monsterItems;
    }
};


#endif