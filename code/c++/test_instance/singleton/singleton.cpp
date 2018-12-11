#include "singleton.h"

#include <iostream>

using namespace std;

int main() {

    string name = "lidongze";
    string university = "buaa";
    SingleTon::init(name, university);
    
    std::cout << SingleTon::instance().get_name() << ", " << 
        SingleTon::instance().get_university() << std::endl;

    string name2 = "mh";
    string university2 = "pk";

    SingleTon::instance().set_name(name2);
    SingleTon::instance().set_university(university2);

    std::cout << SingleTon::instance().get_name() << ", " << 
        SingleTon::instance().get_university() << std::endl;


    string name3 = "baoshuai";
    string university3 = "Tqinghua";
    SingleTon::init(name3, university3);

    std::cout << SingleTon::instance().get_name() << ", " << 
        SingleTon::instance().get_university() << std::endl;

}
