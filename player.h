#include <string>
#include <iostream>
#include <vector>
#include "Monster.h"
#include "item.h"

class player {
    public:
    std::string name;
    std::vector<item> playerItems;
    std::vector<Monster> playerMonsters;

    player(std::string name_) : name(name_){}

    void addMonster(Monster newMonster) {
        int choice = 99;
        if (playerMonsters.size() < 4) 
        {
            playerMonsters.push_back(newMonster);
            //std::cout << "\n \n \n \n \n \n \n \n \n" << std::endl;
            std::cout << newMonster.name << " Has been added to your group!" << std::endl;
        } else {
            std::cout << "No available space, please choose a replacement" << std::endl;
            for (int i = 0; i < playerMonsters.size(); i++)
            {
                std::cout << i + 1 << ": " << playerMonsters[i].name << std::endl;
            }
            std::cout << "0: Cancel" << std::endl;
            while (choice != 0)
            {
            std::cin.clear();
            std::cin >> choice;
                if (choice > 4)
                {
                    std::cout << "pick a valid number" << std::endl;
                    continue;
                }
                playerMonsters.erase(playerMonsters.begin() + choice -1);
                playerMonsters.push_back(newMonster);
                break;
            }
        }
    }

    void showPlayerItems(){
        if (playerItems.empty())
        {
            std::cout << "No Items available" << std::endl;
            return;
        }
        for (int i = 0; i < playerItems.size(); i++)
        {
            std::cout << " | " << playerItems[i].name;
        }
        std::cout << " | " << std::endl;
    }

    void showPlayerMonsters(){
        if (playerMonsters.empty())
        {
            std::cout << "No monsters available" << std::endl;
            return;
        }

        for (int i = 0; i < playerMonsters.size(); i++)
        {
            std::cout << playerMonsters[i].name
            << " Health: " << playerMonsters[i].getCurrentHealth()
            << " Damage: " << playerMonsters[i].getAttackDMG()
            << " Items: [";
            for (int j = 0; j < playerMonsters[i].monsterItems.size(); j++)
            {
                playerMonsters[i].monsterItems[j].getItemName();
                std::cout << ", ";
            };
            
            std::cout << "]" << std::endl;
        }   
    }
    std::string getPlayerName(){
        return name;
    }

    std::vector<item> getPlayerItems(){
        return playerItems;
    }

    void addItem(item item_){
        playerItems.push_back(item_);
    }

};