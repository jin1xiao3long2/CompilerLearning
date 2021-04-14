//
// Created by XM on 2021/3/24.
//

#include "compilerStest.hpp"
#include <iostream>

int main(){
    std::string i;
    std::getline(std::cin, i);
    std::cout << i.length() << std::endl;
    std::cout << i << std::endl;
    for(auto s : i){
        std::cout << s << '1    2' << std::endl;
    }
}