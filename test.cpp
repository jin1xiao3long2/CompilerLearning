#include <deque>
#include <iostream>

int add(int a, int b){
    return a+b;
}

int mul(int a, int b){
    return a*b;
}

void show(int (*func)(int, int), int a, int b){
        std::cout << func(a,b) << std::endl;
}


int main(){
    int *a = new int (3);
    int *b = a;
    std::cout << "a is :  " << *a << "   b is : " << *b << std::endl;
    a = nullptr;
    std::cout  << "   b is : " << *b << std::endl;
    return 0;
}