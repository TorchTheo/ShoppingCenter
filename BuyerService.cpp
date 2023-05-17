#include "include/BuyerService.h"
#include "include/GlobalInfo.h"
#include <iostream>
#include <iomanip>

void BuyerService::showMenu() {
    system("clear");
    std::cout << "============================================================================================================" << std::endl;
    std::cout << "1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.修改个人信息 7.充值 8.返回登录界面" << std::endl;
    std::cout << "============================================================================================================" << std::endl;
}

User* BuyerService::regi() {
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
    GlobalInfo * g = GlobalInfo::getInstance();
    User* user = new Buyer(g->uid_cnt++, username, password, sex, contact, address, 0);
    g->users.push_back(user);
    std::cout << "**********************注册成功**********************\n";
    GlobalInfo::ppause();
    return user;
}

void BuyerService::setUser(User* _user) {
    user = (Buyer*)_user;
}

void BuyerService::query() {
    GlobalInfo * g = GlobalInfo::getInstance();
    g->showAllCommodities();
    uint64_t cid;
    std::cout << "请输入您要查询的商品ID：";
    std::cin >> cid;
    getchar();
    bool flag = false;
    for (auto c :  g->commodities) {
        if (cid == c->getCid()) {
            flag = true;
            if (c->getStatus() == Commodity::XJ) {
                std::cout << "对不起，商品已下架O^O" << std::endl;
                return;
            }
            std::cout << "名称：\t\t" << c->getCid() << std::endl;
            std::cout << "描述：\t\t" << c->getDesc() << std::endl;
            printf("价格：\t\t%.1lf\n", c->getPrice());
            std::cout << "上架时间：\t" << c->getDate() << std::endl;
            std::cout << "卖家ID：\t" << g->cu_map[c->getCid()] << std::endl;
            std::cout << "商品状态：\t";
            std::cout << "销售中" << std::endl;
            break;
        }

    }
    std::cout << "*****************************************************************************" << std::endl;
    if (flag == false)
        std::cout << "您所输入的ID有误，商品不存在" << std::endl;
}

void BuyerService::searchCommodity() {
    std::string key;
    std::cout << "输入关键字：";
    std::cin >> key;
    getchar();
    std::cout << "*******************************************************************************\n";
    int num = 0;
    GlobalInfo * g = GlobalInfo::getInstance();
    for (auto c : g->commodities) {
        if (c->getName().find(key) != -1) {
            num++;
            if (num == 1) {
                std::cout << "ID\t\t名称\t\t\t价格\t\t状态\n";
            }
            std::cout << c->getCid() << "\t\t" << std::left << std::setw(24) << c->getName()
                 << "\t" << c->getPrice() << "\t\t";
            if (c->getStatus() == Commodity::XJ)
                std::cout << "已下架\n";
            else if (c->getStatus() == Commodity::ZS)
                std::cout << "销售中\n";
            else if (c->getStatus() == Commodity::SC)
                std::cout << "已出售\n";
        }
    }
    if (!num)
        std::cout << "没有找到您想要的商品\n";
    std::cout << "*******************************************************************************\n";
    GlobalInfo::ppause();
}

void BuyerService::action() {
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
                g->showAllCommodities();
                GlobalInfo::ppause();
                break;
            case 2:
                purchase();
                break;
            case 3:
                searchCommodity();
                break;
            case 4:
                showOrders();
                break;
            case 5:
                query();
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

void BuyerService::purchase() {
    auto g = GlobalInfo::getInstance();
    g->showAllCommodities();
    std::cout << "输入您想购买的物品ID：";
    uint64_t id;
    std::cin >> id;
    getchar();
    Commodity* c = GlobalInfo::getCommodity(id);
    if (!c) {
        std::cout << "您所输入的ID有误，商品不存在" << std::endl;
        GlobalInfo::ppause();
        return;
    }
    if (c->getStatus() == Commodity::XJ) {
        std::cout << "该商品已下架\n";
        GlobalInfo::ppause();
        return;
    }
    printf("您的现有余额为：%.1lf\n", user->getBalance());
    std::cout << "*****************************************************************************" << std::endl;
    char choice;
    std::cout << "您确定要购买此商品吗?(y/n)" << std::endl;
    std::cin >> choice;
    getchar();
    if (choice == 'y') {
        if (user->getBalance() - c->getPrice() < 0) {
            std::cout << "对不起，您的余额不足" << std::endl;
            return;
        }
        else {
            User *vendor = GlobalInfo::getUser(g->cu_map[c->getCid()]);
            time_t now = time(0);
            tm* ltm = localtime(&now);
            std::cout << "购买成功\n您的余额为：\t";
            c->setStatus(Commodity::SC);
            user->setBalance(user->getBalance() - c->getPrice());
            vendor->setBalance(vendor->getBalance() + c->getPrice());
            printf("%.1lf\n", user->getBalance());
            std::string date = std::to_string(1900 + ltm->tm_year) + "-" + ((1 + ltm->tm_mon) >= 10 ? std::to_string(1 + ltm->tm_mon) : "0" + std::to_string(1 + ltm->tm_mon)) + "-" + ((ltm->tm_mday) >= 10 ? std::to_string(ltm->tm_mday) : "0" + std::to_string(ltm->tm_mday));
            std::cout << "交易时间：\t" <<date<< std::endl;
            std::cout << "*****************************************************************************" << std::endl;
            uint64_t oid = g->oid_cnt++;;
            auto o = new Order(oid, c->getCid(), vendor->getUid(), user->getUid(), date);
            pushOrder(o);
            GlobalInfo::ppause();
        }
    }
    else if (choice == 'n') {
        std::cout << "取消成功" << std::endl;
        GlobalInfo::ppause();
    }
    else {
        std::cin.clear();
        std::cin.sync();
        std::cout<<"输入有误\n";
        GlobalInfo::ppause();
    }
}

void BuyerService::modifyInfo() {
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
void BuyerService::findPassword() {
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
void BuyerService::pushOrder(Order* order) {
    auto g = GlobalInfo::getInstance();
    g->orders.push_back(order);
    auto bid = order->getBuyerID(), sid = order->getSellerID();
    auto buyer = GlobalInfo::getUser(bid), seller = GlobalInfo::getUser(sid);
    buyer->orders.push_back(order->getOid());
    seller->orders.push_back(order->getOid());
}
void BuyerService::recharge() {
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
void BuyerService::showOrders() {
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