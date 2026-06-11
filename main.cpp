#include <string>
#include <iostream>
#include <limits>
#include "player.h"
#include "Monster.h"
#include "item.h"
#include "cave.h"
#include <random>

//Instance of main protagonists
std::vector<Monster> enemyMonsters;
cave cave1("Cave 1");
cave cave2("Cave 2");
cave cave3("Cave 3");
player mainCharacter("TempName");



void spacer(){
    std::cout << "\n \n \n \n \n \n \n \n \n" << std::endl;
}

//Section of screen displays:
int startGame(){
    spacer();
    int choice = 0;
        std::cout << "-------- Software udvikling the spil -------" << std::endl;
        std::cout << "1: ----------- Create character ------------" << std::endl;
        std::cout << "0: ----------------- Exit ------------------" << std::endl;
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
    spacer();
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
        //Ensure no longer first round
        firstround = false;

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
            spacer();
            for (int i = 0; i < mainCharacter.playerMonsters.size(); i++)
            {
                if (mainCharacter.playerMonsters[i].getCurrentHealth() > 0)
                {
                    std::cout << mainCharacter.playerMonsters[i].getName() << " Attacks: "
                            << chosenEnemyMonster.getName() << std::endl;
                    monsterOnMonster(mainCharacter.playerMonsters[i], chosenEnemyMonster);
                }
            }

            if (chosenEnemyMonster.getCurrentHealth() > 0)
            {
                std::cout << "\n------- Enemy attacks back! -------" << std::endl;
                for (int i = 0; i < mainCharacter.playerMonsters.size(); i++)
                {
                    if (mainCharacter.playerMonsters[i].getCurrentHealth() > 0)
                    {
                        monsterOnMonster(chosenEnemyMonster, mainCharacter.playerMonsters[i]);
                        break;
                    }
                }
            }
        }

        if (choice == 0)
        {
            inBattle = false;
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
}

void caveFight(cave& chosenCave){
    for (int i = 0; i < chosenCave.getCaveMonsters().size(); i++)
    {
        Monster& currentCaveEnemy = chosenCave.getCaveMonsters()[i];
        if (currentCaveEnemy.getCurrentHealth() <= 0) {
            continue;
        }
        battleMenu(currentCaveEnemy, mainCharacter);
    }

    if (checkPlayerStatus()){
        std::cout << "Congrats! you have cleared a cave!" << std::endl;
    }
    
}

void healAllMonsters(){
    for (int i = 0; i < mainCharacter.playerMonsters.size(); i++)
    {
        mainCharacter.playerMonsters[i].fullyHeal();
    }
    for (int i = 0; i < enemyMonsters.size(); i++)
    {
        enemyMonsters[i].fullyHeal();
    }
    for (int i = 0; i < cave1.getCaveMonsters().size(); i++)
    {
        cave1.getCaveMonsters()[i].fullyHeal();
    }
    for (int i = 0; i < cave2.getCaveMonsters().size(); i++)
    {
        cave2.getCaveMonsters()[i].fullyHeal();
    }
    for (int i = 0; i < cave3.getCaveMonsters().size(); i++)
    {
        cave3.getCaveMonsters()[i].fullyHeal();
    }
}

int mainMenu1(){
    bool isFighting = true;
    int choice = 0;

    while (isFighting)
    {
        healAllMonsters();
        std::cout << "-------------Your Monsters------------" << std::endl;
        mainCharacter.showPlayerMonsters();
        std::cout << "-------- Choose your enemy -------" << std::endl;
        for (int i = 0; i < enemyMonsters.size(); i++)
        {
            std::cout << i + 1 << ": Name: " << enemyMonsters[i].getName()
            << " Hp: " << enemyMonsters[i].getCurrentHealth()
            << " Dmg: " << enemyMonsters[i].getAttackDMG() << std::endl;
        }
        std::cout << "-------- Go to the Caves instead -------" << std::endl;
        std::cout << "50: Easy cave   - Reward: 1 random item" << std::endl;
        std::cout << "51: Medium cave - Reward: 2 random items" << std::endl;
        std::cout << "52: Hard cave   - Reward: 3 random items" << std::endl;
        std::cout << "0: ----------------- Exit ------------------" << std::endl;
        std::cin.clear();
        std::cin >> choice;
        if (choice == 50)
        caveFight(cave1);
        if (choice == 51)
        caveFight(cave2);
        if (choice == 52)
        caveFight(cave3);
        
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
    cave1.addMonsterToCave(Monster("Weak Goblin", 4, 2));
    cave1.addMonsterToCave(Monster("Weak Goblin", 4, 2));
    cave1.addMonsterToCave(Monster("Weak Goblin", 4, 2));
    cave2.addMonsterToCave(Monster("Strong Goblin", 10, 4));
    cave2.addMonsterToCave(Monster("Strong Goblin", 10, 4));
    cave2.addMonsterToCave(Monster("Ceasar", 30, 5));
    cave3.addMonsterToCave(Monster("Ceasar", 30, 5));
    cave3.addMonsterToCave(Monster("Unicorn", 50, 8));
    cave3.addMonsterToCave(Monster("Drakon", 100, 10));
    //Creation of different items.
    //Name, health, itemValue, damage
    item bomb("Bomb", 100, 100, 10);
    item firebomb("FireBomb", 100, 35, 5);
    item thuderbomb("Thunderbomb", 100, 50, 10);
    item club("Club", 100, 100, 20);
    item fan("Fan", 100, 80, 0);
    item curse("Curse", 100, 20, 1);
    item poison("Poison", 100, 20, 2);  

    while(isRunning){

        menu = startGame();

        switch(menu){
        case 1: 
            createCharacter(mainCharacter);
            menu = mainMenu1();
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