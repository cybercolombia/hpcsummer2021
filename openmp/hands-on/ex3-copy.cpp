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
g++ -std=c++11 -Wall -Wextra ex3-copy.cpp -o exe -Wno-unknown-pragmas && ./exe
OpenMP Compile:
g++ -std=c++11 -Wall -Wextra -fopenmp ex3-copy.cpp -o exe && ./exe
*/

int main(void){
    InfoOpenMP();

    cout<<"Part 1"<<endl;

    int x = 10;

    cout<<"thread "<<omp_get_thread_num()<<" original value: "<<x<<endl;
    #pragma omp parallel private(x)
    {
        int TID = omp_get_thread_num();
        printf("thread %d value: %d\n",TID,x);
    } /*-- End of parallel region --*/
    cout<<"thread "<<omp_get_thread_num()<<" after value: "<<x<<endl;

    cout<<endl<<"Part 2"<<endl;

    /*
        Exercise: Think about all previous exercises
        1. can you use firstprivate or threadprivate?
    */

    return 0;
}
