#include <iostream>

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



int main(){

    bool isRunning = true;
    int menu;

     while(isRunning){

        menu = startGame();

        switch(menu){
        case 1: 
            //createCharacter(mainCharacter);
            //menu = fightMenu1();
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