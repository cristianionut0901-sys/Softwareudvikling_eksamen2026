#include <string>
#include <iostream>
#include <limits>
#include "player.h"
#include "Monster.h"
#include <random>

//Instance of main protagonists
std::vector<Monster> enemyMonsters;
player mainCharacter("TempName");

void spacer(){
    std::cout << "\n \n \n \n \n" << std::endl;
}

//Section of screen displays:
int startGame(){
    int choice = 0;
        std::cout << "-------- Software udvikling the spil -------" << std::endl;
        std::cout << "1: ----------- Create character ------------" << std::endl;
        std::cout << "0: ----------------- Exit ------------------" << std::endl;
        spacer();
        std::cin.clear();
        std::cin >> choice;
    return choice;
}

void createCharacter(player& mainCharacter){

        std::string name;
        std::cout << "-------- Type in the character name --------" << std::endl;
        std::cin.clear();
        std::cin >> name;
        mainCharacter.name = name;
        Monster hest1("Hest1", 4, 1);
        Monster hest2("Hest2", 4, 1);
        mainCharacter.addMonster(hest1);
        mainCharacter.addMonster(hest2);
}

bool checkPlayerStatus(){
    for (int i = 0; i < mainCharacter.playerMonsters.size(); i++)
        {
            if (mainCharacter.playerMonsters[i].getCurrentHealth() > 0)
                {
                    return true;
                }
        }
    return false;
}

bool randomStart(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<>coinFlip(0, 1);
    return coinFlip(gen) == 1;
}

void monsterOnMonster(Monster& monster1, Monster& monster2){
    monster2.damageTaken(monster1.getAttackDMG());
}

void battleMenu(Monster& chosenEnemyMonster, player& mainCharacter) {
    std::cout << "Battle entered and the enemy is: " 
    << chosenEnemyMonster.getName() << std::endl; 
    bool inBattle = true;
    int choice = 0;
    bool firstround = true;
    bool RoundWon = true;
    while (inBattle)
    {
        //Checks if player is still alive
        if (!checkPlayerStatus())
        {
            std::cout << "Battle has ended, players monsters is all gone" << std::endl;
            inBattle = false;
            RoundWon = false;
            break;
        }
        
        //Checks if Monster is still alive
        if (chosenEnemyMonster.getCurrentHealth() <= 0) {
            std::cout << "ENEMY HAS BEEN SLAIN, YOU WIN" << std::endl;
            inBattle = false;
            break;
        }

        //Enemy gets first hit
        if (randomStart() && firstround)
        {
            std::cout << "-------Enemy gets the first hit------" << std::endl;
            for (int i = 0; i < mainCharacter.playerMonsters.size(); i++)
            {
                if (mainCharacter.playerMonsters[i].getCurrentHealth() > 0)
                {
                    monsterOnMonster(chosenEnemyMonster, mainCharacter.playerMonsters[i]);
                    firstround = false;
                    break;
                }
            }
        }
        std::cout << "-------------Your Monsters------------" << std::endl;
        mainCharacter.showPlayerMonsters();
        std::cout << "-------------Enemy Monster------------" << std::endl;
        std::cout << chosenEnemyMonster.getName() << " Health: " << chosenEnemyMonster.getCurrentHealth() 
        << " Damage: " << chosenEnemyMonster.getAttackDMG() << std::endl;

        std::cout << "----------Choose your action!---------" << std::endl;
        std::cout << "1: Attack" << std::endl;
        std::cout << "0: Exit" << std::endl;
        std::cin.clear();
        std::cin >> choice;

        if (choice == 1)
        {
            for (int i = 0; i < mainCharacter.playerMonsters.size(); i++)
            {
                if (mainCharacter.playerMonsters[i].getCurrentHealth() > 0)
                {
                    std::cout << mainCharacter.playerMonsters[i].getName() << " Attacks:"
                    << chosenEnemyMonster.getName() << std::endl;
                    monsterOnMonster(mainCharacter.playerMonsters[i], chosenEnemyMonster);
                }
            }
        }

        if (choice == 0)
        {
            inBattle = false;
        }
        spacer();
    }

    for (int i = 0; i < mainCharacter.playerMonsters.size(); i++)
    {
        if (mainCharacter.playerMonsters[i].getCurrentHealth() > 0)
        {
            chosenEnemyMonster.fullyHeal();
            mainCharacter.playerMonsters[i].fullyHeal();
        }
    }

    if (RoundWon)
    {
        std::cout << "Add " << chosenEnemyMonster.getName() << " To your batch of monsters? " << std::endl;
        std::cout << "1: Yes" << std::endl;
        std::cout << "2: No" << std::endl;
        std::cin.clear();
        std::cin >> choice;
        if (choice == 1)
        {
            mainCharacter.addMonster(chosenEnemyMonster);
        }
    }

    spacer();
}

int fightMenu1(){
    bool isFighting = true;
    int choice = 0;
    while (isFighting)
    {
        std::cout << "-------------Your Monsters------------" << std::endl;
        mainCharacter.showPlayerMonsters();
        std::cout << "-------- Choose your enemy -------" << std::endl;
        for (int i = 0; i < enemyMonsters.size(); i++)
        {
            std::cout << i + 1 << ": Name: " << enemyMonsters[i].getName()
            << " Hp: " << enemyMonsters[i].getCurrentHealth()
            << " Dmg: " << enemyMonsters[i].getAttackDMG() << std::endl;
        }
        
        std::cout << "0: ----------------- Exit ------------------" << std::endl;
        spacer();
        std::cin.clear();
        std::cin >> choice;
        if (choice == 0)
        {
            return 0;
        }
        
        if (choice > 0 && choice <= enemyMonsters.size()) 
        {
            battleMenu(enemyMonsters[choice - 1], mainCharacter); 
        } else {
            std::cout << "Invalid monster" << std::endl;
        }
    }
    return 0;
}

int main(){
    bool isRunning = true;
    int menu;

    //Initial create of default monsters
    enemyMonsters.push_back(Monster("Weak Goblin", 4, 2));
    enemyMonsters.push_back(Monster("Green smurf", 8, 3));
    enemyMonsters.push_back(Monster("Strong Goblin", 10, 4));
    enemyMonsters.push_back(Monster("Stronger goblin", 15, 5));
    enemyMonsters.push_back(Monster("Ceasar", 30, 5));
    enemyMonsters.push_back(Monster("Unicorn", 50, 8));
    enemyMonsters.push_back(Monster("Drakon", 100, 10));

    while(isRunning){

        menu = startGame();

        switch(menu){
        case 1: 
            createCharacter(mainCharacter);
            menu = fightMenu1();
            break;
        case 0: 
            isRunning = false;
            break;
        default:
            std::cout << "Oops not a valid option" << std::endl;
            break;
        }
    }
    
    return 0;
}