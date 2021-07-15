#include <iostream>
#include <fstream>
#include <cmath>
#include <complex>
#include <random>
#include <vector>
#include <array> // This is interesting...
#include <algorithm>

#include <unistd.h>
#define INFO_BUFFER_SIZE 1024

#include "defs.h"

using namespace std;

/*
Compile:
g++ -std=c++11 -Wall -Wextra ex8-task-fibonacci.cpp -o exe -Wno-unknown-pragmas && ./exe
OpenMP Compile:
g++ -std=c++11 -Wall -Wextra -fopenmp ex8-task-fibonacci.cpp -o exe && ./exe
*/

int fib(uint x);

int main(void){
    InfoOpenMP();

    cout<<"Part 1"<<endl;

    SimpleTimer _t;

    uint N;
    cout<<"Enter a positive integer ";
    cin>>N;

    printf("\nPart 1\n");

    _t.start("Fib test");
    printf("Fib[%d] = %d\n",N,fib(N));
    _t.stop(); _t.print();

    return 0;
}


int fib(uint x){
    if(x == 0 || x == 1)
        return 1;
    else
        return fib(x-1) + fib(x-2);
}
