#include <iostream>
#include "include/Controller.h"
#include "include/GlobalInfo.h"

int main() {
    auto g = GlobalInfo::getInstance();
    auto con = Controller::getInstance();
    int choice;
    while(1) {
        con->showMenu();
        std::cout << "输入操作：";
        std::cin >> choice;
        getchar();
        switch(choice) {
            case 1:
                con->Login();
                break;
            case 2:
                con->buyerRegister();
                break;
            case 3:
                con->sellerRegister();
                break;
            case 4:
                con->findPass();
                break;
            case 5:
                con->exitSys();
                break;
            default:
                std::cout << "\033[31m未知命令\n\033[0m";
                g->ppause();
                break;
        }
    }
    return 0;
}