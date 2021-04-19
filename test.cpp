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
    show(add, 1 ,2);
    show(mul ,1 ,2);
    return 0;
}