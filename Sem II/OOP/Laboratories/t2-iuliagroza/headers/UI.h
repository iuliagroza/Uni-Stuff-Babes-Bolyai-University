#pragma once
#include "realestate.h"
#include <fstream>

class UI{
public:
    RealEstateAgency res;

    void print_menu(){
        std::cout<<"1. remove client\n2. list all\n3. add dwelling\n4. save clients to file\n0. exit\n";
    }

    int get_option(){
        int opt;
        std::cout<<"\noption: ";
        std::cin>>opt;
        return opt;
    }

    void start(){
        bool running = true;
        auto d1 = new Dwelling(33000, true);
        auto p1 = new Person(2700, "Georgica");
        auto p2 = new Person(5500, "Manuela");
        auto c1 = new Company(22000, "thieves_company", 3700);
        auto c2 = new Company(333000, "rich_dudes_company", 50000);
        this->res.addClient(p1);
        this->res.addClient(p2);
        this->res.addClient(c1);
        this->res.addClient(c2);
        this->res.addDwelling(d1);
        while(running){
            print_menu();
            int option = get_option();
            switch(option){
                case 0:{ // exit
                    running = false;
                    std::cout<<"\n\ngoodbye!";
                    break;}
                case 1:{ // remove client
                    std::string nam;
                    std::cout<<"name: ";
                    std::cin>>nam;
                    this->res.removeClient(nam);
                    break;
                }
                case 2:{ // show all
                    std::cout<<"CLIENTS\n";
                    for(auto i: this->res.getAllClients())
                        std::cout<<i->to_string()<<std::endl;
                    std::cout<<"\n\nDWELLINGS\n";
                    for(auto i: this->res.getAllDwellings())
                        std::cout<<"dwelling: "<<i->to_string()<<std::endl;
                    break;
                }
                case 3:{ // add dwelling
                    Dwelling* m;
                    double price;
                    int prof;
                    bool profit;
                    std::cout<<"input price: ";
                    std::cin>>price;
                    std::cout<<"input if profitable or not (1 = yes, anything else = no): ";
                    std::cin>>prof;
                    if(prof == 1)
                        profit = true;
                    else
                        profit = false;
                    m = new Dwelling(price, profit);
                    this->res.addDwelling(m);
                    std::cout<<"interested clients:\n";
                    for(auto i: this->res.getInterestedClients(m)){
                        std::cout<<i->to_string()<<std::endl;
                    }
                    std::cout<<std::endl;
                    break;
                }
                case 4:{ // clients to file
                    this->res.writeToFile("clients.txt");
                    break;
                }
                default:{
                    std::cout<<"invalid option!\n\n";
                    break;

                }
            }

        }
    }
};