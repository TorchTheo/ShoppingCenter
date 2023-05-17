#include "include/SellerService.h"
#include "include/Fruit.h"
#include "include/Computer.h"
#include "include/CommodityFactory.h"
#include "include/GlobalInfo.h"
#include <iostream>
#include <iomanip>

Commodity* SellerService::putUpCommodity() {
    GlobalInfo * g = GlobalInfo::getInstance();
    std::cout << "输入-1来取消发布\n";
    std::string Mname;
    std::cout << "请输入商品名称（禁止使用空格等分隔符）：";
    std::cin >> Mname;
    getchar();
    if(Mname == "-1") {
        std::cout << "取消发布\n";
        GlobalInfo::ppause();
        return nullptr;
    }
    double price;
    std::cout << "请输入商品价格：";
    std::cin >> price;
    getchar();
    if(price == -1) {
        std::cout << "取消发布\n";
        GlobalInfo::ppause();
        return nullptr;
    }
    int type;
    std::cout << "请输入商品类型（0.水果 1.电脑）：";
    std::cin >> type;
    getchar();
    if(type == -1) {
        std::cout << "取消发布\n";
        GlobalInfo::ppause();
        return nullptr;
    }
    Commodity *c = nullptr;
    switch(type) {
        case 0: {
            std::cout << "请输入保质期：";
            int day;
            std::cin >> day;
            getchar();
            c = CommodityFactory::getCommodity(CommodityFactory::FRUIT);
            c->setCid(g->cid_cnt++);
            c->setName(Mname);
            c->setPrice(price);
            ((Fruit*)c)->setDay(day);
            break;
        }
        case 1: {
            std::string cpu, mem, disk, graphic; 
            std::cout << "请输入CPU规格：";
            std::cin >> cpu; getchar();
            std::cout << "请输入内存规格：";
            std::cin >> mem; getchar();
            std::cout << "请输入硬盘规格：";
            std::cin >> disk; getchar();
            std::cout << "请输入显卡规格：";
            std::cin >> graphic; getchar();
            c = CommodityFactory::getCommodity(CommodityFactory::COMPUTER);
            c->setCid(g->cid_cnt++);
            c->setName(Mname);
            c->setPrice(price);
            ((Computer*)c)->setCpu(cpu);
            ((Computer*)c)->setMem(mem);
            ((Computer*)c)->setDisk(disk);
            ((Computer*)c)->setGraphic(graphic);
            break;
        }
    }
    std::cout << "请确认发布商品的信息无误" << std::endl;
    std::cout << "********************************************************************************************" << std::endl;
    std::cout << "商品名称：" << c->getName() << std::endl;
    std::cout << "商品价格：" << c->getPrice() << std::endl;
    std::cout << "商品描述：" << c->getDesc() << std::endl;
    std::cout << "********************************************************************************************" << std::endl << std::endl;
    std::cout << "您确认要发布该商品吗(y/n)\n";
    char choice;
    std::cin >> choice;
    getchar();
    if (choice == 'y') {
        std::cout << "商品发布成功!" << std::endl;
        g->commodities.push_back(c);
        g->cu_map.insert({c->getCid(), user->getUid()});
        user->inventory->commodities.push_back(c->getCid());
    }
    else if (choice == 'n')
        std::cout << "取消成功" << std::endl;
    else {
        std::cin.clear();
        std::cin.sync();
        std::cout<<"输入有误\n";
        GlobalInfo::ppause();
    }
    GlobalInfo::ppause();
    return c;
}

void SellerService::showCommodities() {
    std::cout << "您发布的商品清单如下" << std::endl;
    std::cout << "**********************************************************************************\n";
    std::cout << "ID\t\t名称\t\t\t价格\t上架时间\t商品状态\n";
    for (auto cid : user->inventory->commodities) {
        auto c = GlobalInfo::getCommodity(cid);
        std::cout << c->getCid() << "\t\t" << std::left << std::setw(24) << c->getName() << "\t";
        printf("%.1lf\t", c->getPrice());
        std::cout << c->getDate() << "\t";
        if (c->getStatus() == Commodity::XJ) {
            std::cout << "已下架\n";
        }
        else if (c->getStatus() == Commodity::ZS) {
            std::cout << "销售中\n";
        }
        else if (c->getStatus() == Commodity::SC) {
            std::cout << "已售出\n";
        }
    }
    std::cout << "**********************************************************************************\n";
    GlobalInfo::ppause();
}

void SellerService::showMenu() {
    system("clear");
    std::cout << "========================================================================================================" << std::endl;
    std::cout << "1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.修改个人信息 7.充值 8.返回登录界面" << std::endl;
    std::cout << "========================================================================================================" << std::endl;
}

User* SellerService::regi() {
    GlobalInfo * g = GlobalInfo::getInstance();
    std::cout<<"*******您可以输入-1来取消注册*******\n";
    std::string username, password, contact, address;
    bool sex;
    while (1) {
        std::cout << "请输入用户名（不超过10位的字母或汉字）：";
        std::cin >> username;
        getchar();
        if(username == "-1") {
            std::cout<<"*******注册取消*******\n";
            GlobalInfo::ppause();
            return nullptr;
        }
        if (GlobalInfo::checkRegisterUsername(username))
            break;
    }
    while (1) {
        std::cout << "请输入密码（不超过20个字符，只能为小写字母和数字）：";
        std::cin >> password;
        getchar();
        if(password == "-1") {
            std::cout<<"*******注册取消*******\n";
            GlobalInfo::ppause();
            return nullptr;
        }
        if (GlobalInfo::checkRegisterPassword(password)) {
            std::string check;
            std::cout << "请再次输入密码：";
            std::cin >> check;
            getchar();
            if(check == password)
                break;
            else
                std::cout << "两次密码不同，请重新输入\n";
        }

    }
    while (1) {
        std::cout << "请输入性别（1.男 0.女）";
        std::cin >> sex;
        getchar();
        if(sex == -1) {
            std::cout<<"*******注册取消*******\n";
            GlobalInfo::ppause();
            return nullptr;
        }
        if (sex == 1 || sex == 0)
            break;
        else
            std::cout << "请输入正确的序号\n";
    }
    while (1) {
        std::cout << "请输入联系方式：";
        std::cin >> contact;
        getchar();
        if(contact == "-1") {
            std::cout<<"*******注册取消*******\n";
            GlobalInfo::ppause();
            return nullptr;
        }
        if (GlobalInfo::checkRegisterContact(contact))
            break;
    }
    std::cout << "请输入地址：";
    std::cin >> address;
    getchar();
    if(address == "-1") {
        std::cout<<"*******注册取消*******\n";
        GlobalInfo::ppause();
        return nullptr;
    }
    User* user = new Seller(g->uid_cnt++, username, password, sex, contact, address, 0);
    g->users.push_back(user);
    std::cout << "**********************注册成功**********************\n";
    GlobalInfo::ppause();
    return user;
}

void SellerService::setUser(User *_user) {
    user = (Seller*)_user;
}

void SellerService::modifyCommodity() {
    showCommodities();
    uint64_t _cid;
    std::cout << "*********************************************************************************************" << std::endl;
    std::cout << "请输入修改商品ID（无法修改商品类别）：";
    std::cin >> _cid;
    getchar();
    uint64_t cid = 0;
    for (auto id : user->inventory->commodities) 
        if (id == _cid) {
            cid = id;
            break;
        }
    if (cid == 0) {
        std::cout << "!!!您输入的商品不属于你或者不存在!!!\n";
        GlobalInfo::ppause();
        return;
    }
    auto c = GlobalInfo::getCommodity(cid);
    std::cout << "请输入修改商品属性（1.名称 2.价格 3.详情）：";
    std::string s;
    double price = 0;
    int choice;
    std::cin >> choice;
    getchar();
    if (choice == 1) {
        std::cout << "请输入修改后的商品名称：";
        std::cin >> s;
        getchar();
        std::cout << "\n请确认修改信息无误\n";
        std::cout << "****************************************\n";
        std::cout << "商品ID：" << c->getCid() << std::endl;
        std::cout << "商品名称：" << s << std::endl;
        printf("商品价格：%.1lf\n", c->getPrice());
        std::cout << "商品描述：" << c->getDesc() << std::endl;
        std::cout << "****************************************\n";
        char option;
        std::cout << "确认修改?(y/n)\n";
        std::cin >> option;
        getchar();
        if (option == 'y') {
            c->setName(s);
            std::cout << "修改成功！\n";
            std::cout << "*********************************************************************************************" << std::endl;
        }
        else
            std::cout << "取消修改\n";
    } else if (choice == 2) {
        std::cout << "请输入修改后的商品价格：";
        std::cin >> price;
        getchar();
        std::cout << "\n请确认修改信息无误\n";
        std::cout << "****************************************\n";
        std::cout << "商品ID：" << c->getCid() << std::endl;
        std::cout << "商品名称：" << c->getName() << std::endl;
        printf("商品价格：%.1lf\n", price);
        std::cout << "商品描述：" << c->getDesc() << std::endl;
        std::cout << "****************************************\n";
        char option;
        std::cout << "确认修改?(y/n)\n";
        std::cin >> option;
        getchar();
        if (option == 'y') {
            c->setPrice(price);
            std::cout << "修改成功！\n";
            std::cout << "*********************************************************************************************" << std::endl;
        }
        else {
            std::cout << "取消修改\n";
        }
    } else if (choice == 3) {
        c->modify();
    } else {
        std::cout << "属性不存在，修改失败\n";
        std::cout << "*********************************************************************************************" << std::endl;
    }
    GlobalInfo::ppause();
}

void SellerService::putDownCommodity() {
    showCommodities();
    uint64_t _cid;
    std::cout << "请输入您想要下架商品的ID：";
    std::cin >> _cid;
    getchar();
    uint64_t cid = 0;
    for (auto id : user->inventory->commodities) 
        if (id == _cid) {
            cid = id;
            break;
        }
    if (cid == 0) {
        std::cout << "!!!您输入的商品不属于你或者不存在!!!\n";
        GlobalInfo::ppause();
        return;
    }
    auto c = GlobalInfo::getCommodity(cid);
    if (c->getStatus() == Commodity::XJ) {
        std::cout << "对不起，该商品已下架\n";
        GlobalInfo::ppause();
        return;
    }
    if (c->getStatus() == Commodity::SC) {
        std::cout << "对不起，该商品已售出，无法下架\n";
        GlobalInfo::ppause();
        return;
    }
    std::cout << "请确认商品信息\n";
    std::cout << "**************************************************\n";
    std::cout << "商品ID：" << c->getCid() << std::endl;
    std::cout << "商品名称：" << c->getName() << std::endl;
    printf("商品价格：%.1lf\n", c->getPrice());
    std::cout << "商品描述：" << c->getDesc() << std::endl;
    std::cout << "**************************************************\n";
    std::cout << "是否下架该商品？（y/n）";
    char choice;
    std::cin >> choice;
    getchar();
    if (choice == 'y') {
        c->setStatus(Commodity::XJ);
        std::cout << "下架成功\n";
    }
    else if(choice == 'n')
        std::cout << "取消下架\n";
    else {
        std::cin.clear();
        std::cin.sync();
        std::cout<<"输入有误\n";
        GlobalInfo::ppause();
    }
    GlobalInfo::ppause();
}

void SellerService::action() {
    system("clear");
    auto g = GlobalInfo::getInstance();
    int choice;
    while (1) {
        showMenu();
        std::cout << "输入操作：";
        std::cin >> choice;
        getchar();
        switch (choice) {
            case 1:
                putUpCommodity();
                break;
            case 2:
                showCommodities();
                break;
            case 3:
                modifyCommodity();
                break;
            case 4:
                putDownCommodity();
                break;
            case 5:
                showOrders();
                break;
            case 6:
                modifyInfo();
                break;
            case 7:
                recharge();
                break;
            case 8:
                GlobalInfo::ppause();
                return;
        }
    }
    g->ppause();
}

void SellerService::modifyInfo() {
    user->showInfo();
    std::cout << "请选择你要修改的属性(1.用户名 2.联系方式 3.地址 4.登录密码)：";
    std::string s;
    int choice;
    bool flag = true;
    char option;
    std::cin >> choice;
    getchar();
    switch (choice)
    {
        case 1:
            std::cout << "请输入修改后的用户名：";
            std::cin >> s;
            getchar();
            if (s != user->getUsername()) {
                flag = GlobalInfo::checkUsername(s);
                if (!flag) {
                    std::cout << "用户名重复\n";
                    GlobalInfo::ppause();
                    return;
                }
            }
            std::cout << "是否修改？（y/n）\n";
            std::cin >> option;
            getchar();
            if (option == 'y') {
                user->setUsername(s);
                std::cout << "修改成功\n";
                GlobalInfo::ppause();
                return;
            }
            else {
                std::cout << "取消修改\n";
                GlobalInfo::ppause();
                return;
            }
            break;
        case 2:
            std::cout << "请输入修改后的联系方式：";
            std::cin >> s;
            getchar();
            std::cout << "是否修改？（y/n）\n";
            std::cin >> option;
            getchar();
            if (option == 'y') {
                user->setContact(s);
                std::cout << "修改成功\n";
                GlobalInfo::ppause();
                return;
            }
            else {
                std::cout << "取消修改\n";
                GlobalInfo::ppause();
                return;
            }
            break;
        case 3:
            std::cout << "请输入修改后的地址：";
            std::cin >> s;
            getchar();
            std::cout << "是否修改？（y/n）\n";
            std::cin >> option;
            getchar();
            if (option == 'y') {
                user->setAddress(s);
                std::cout << "修改成功\n";
                GlobalInfo::ppause();
                return;
            }
            else {
                std::cout << "取消修改\n";
                GlobalInfo::ppause();
                return;
            }
            break;
        case 4:
            std::cout << "请输入修改后的密码：";
            std::cin >> s;
            getchar();
            std::cout << "是否修改？（y/n）\n";
            std::cin >> option;
            getchar();
            if (option == 'y') {
                user->setPassword(s);
                std::cout << "修改成功\n";
                GlobalInfo::ppause();
                return;
            }
            else {
                std::cout << "取消修改\n";
                GlobalInfo::ppause();
                return;
            }
            break;
        default:
            std::cin.clear();
            std::cin.sync();
            std::cout << "\n请输入正确的操作序号" << std::endl;
            GlobalInfo::ppause();
            break;
    }
}
void SellerService::findPassword() {
    std::cout << "请输入您预留的联系方式：";
    std::string _contact;
    std::cin >> _contact;
    getchar();
    if(_contact == user->getContact()) {
        std::cout<<"*******验证成功*******\n请输入新的密码：";
        std::string pass;
        std::string check;
        std::cin >> pass;
        getchar();
        std::cout << "请再次输入密码：";
        std::cin >> check;
        getchar();
        if(check == pass) {
            std::cout << "*******密码已经重新设置*******\n";
            user->setPassword(pass);
        }
        else
            std::cout<<"!!!两次输入密码不同，请重试!!!\n";
    }
    else
        std::cout<<"联系方式有误，重新设置密码失败\n";
    GlobalInfo::ppause();
}
void SellerService::pushOrder(Order* order) {
    auto g = GlobalInfo::getInstance();
    g->orders.push_back(order);
    auto bid = order->getBuyerID(), sid = order->getSellerID();
    auto buyer = GlobalInfo::getUser(bid), seller = GlobalInfo::getUser(sid);
    buyer->orders.push_back(order->getOid());
    seller->orders.push_back(order->getOid());
}
void SellerService::recharge() {
    std::cout << "您的当前余额为：" << user->getBalance() << std::endl;
    std::cout << "请输入充值数目：";
    double money;
    std::cin >> money;
    getchar();
    std::cout << "************************************************************\n";
    if(money <= 0) {
        std::cout<<"充值金额不能为0或负数\n";
        return;
    }
    user->setBalance(user->getBalance() + money);
    std::cout << "充值成功\n";
    printf("当前余额：%.1lf\n", user->getBalance());
    GlobalInfo::ppause();
}
void SellerService::showOrders() {
    std::cout << "*************************************************************************************" << std::endl;
    std::cout << "订单ID:\t\t商品ID：\t交易时间：\t交易金额：\t卖家ID：\t买家ID：\n";
    for (auto oid : user->orders) {
        auto order = GlobalInfo::getOrder(oid);
        std::cout << order->getOid() << "\t\t"
                << order->getCid() << "\t\t"
                << order->getDate() << "\t";
        printf("%.1lf\t\t", order->getTransaction());
        std::cout << order->getSellerID() << "\t\t"
                << order->getBuyerID() << std::endl;
    }
    std::cout << "*************************************************************************************" << std::endl;
    GlobalInfo::ppause();
}