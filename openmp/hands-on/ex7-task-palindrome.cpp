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
g++ -std=c++11 -Wall -Wextra ex7-task-palindrome.cpp -o exe -Wno-unknown-pragmas && ./exe
OpenMP Compile:
g++ -std=c++11 -Wall -Wextra -fopenmp ex7-task-palindrome.cpp -o exe && ./exe
*/

int main(void){
    InfoOpenMP();

    cout<<"Part 0"<<endl;

    printf("A ");
    printf("race ");
    printf("car ");
    printf("is fun to watch.\n");

    printf("\nPart 2\n");

    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("A ");
            #pragma omp task
            { printf("race "); }
            #pragma omp task
            { printf("car "); }
            printf("is fun to watch.\n");
        }
    }

    return 0;
}
