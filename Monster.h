#ifndef MONSTER_H
#define MONSTER_H
#include <string>
#include <iostream>

class Monster {
    public:
    std::string name;
    int health;
    int maxHealth;
    int attack;

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
};


#endif