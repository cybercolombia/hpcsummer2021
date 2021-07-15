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
g++ -std=c++11 -Wall -Wextra ex2-master-single.cpp -o exe -Wno-unknown-pragmas && ./exe
OpenMP Compile:
g++ -std=c++11 -Wall -Wextra -fopenmp ex2-master-single.cpp -o exe && ./exe
*/

int main(void){
    InfoOpenMP();

    cout<<"Part 1"<<endl;

    #pragma omp parallel
    {
        int TID = omp_get_thread_num();
        sleep(omp_get_thread_num());

        printf("In parallel region - Thread ID is %d\n",TID);
    } /*-- End of parallel region --*/

    cout<<endl<<"Part 2"<<endl;

    int extra_time = 0;
    #pragma omp parallel
    {
        int TID = omp_get_thread_num();
        #pragma omp master
        {
            printf("\tInside Block - Thread ID is %d\n",TID);
            sleep(1);
            extra_time = 1;
        }
        sleep(TID+extra_time);
        printf("In parallel region - Thread ID is %d\n",TID);
    } /*-- End of parallel region --*/

    /*
        Exercise:
        1. Use master/single with nowait to see what happens
        2. Place a barrier to have sync... perhaps a flush!
        3. Create a shared static vector before the parallel region
           and copy it to each thread, modify it. How do you get results from
           specific thread out of the parallel region for example?
        4. Create private static vectors, how do you make sure the results
           from specific thread remain out of the parallel region?
    */

    return 0;
}
