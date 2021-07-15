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
g++ -std=c++11 -Wall -Wextra ex5-loop.cpp -o exe -Wno-unknown-pragmas && ./exe
OpenMP Compile:
g++ -std=c++11 -Wall -Wextra -fopenmp ex5-loop.cpp -o exe && ./exe
*/

#define N 10000
typedef float Decimal;


int main(void){
    InfoOpenMP();

    // Choose the system's random device -- Entropy dependent
    random_device r;
    // Create a seed sequence -> Improves psudo-random numbers!
    seed_seq sseq{r(), r(), r(), r(), r(), r(), r(), r()};
    // Create two engines
    default_random_engine gen1(sseq);
    mt19937_64 gen2(sseq);
    // Now define and parametrize the distributions
    uniform_real_distribution<Decimal> unif(-1, 1);
    normal_distribution<Decimal> normal(0, 1);
 
    SimpleTimer _t;

    cout<<"Part 1: fill static vector with random noise"<<endl;

    // Notice it is a static array -> in the stack!
    // How is the array initialized?
    Decimal v1[N];

    _t.start("Random fill");
    // Fill the vector with random normal noise
    for(int it; it < N; it++)
        v1[it] = normal(gen2);
    _t.stop(); _t.print();

    cout<<endl<<"Part 2: "<<endl;

    /*
        Exercise:
        1. Create another vector v2 with uniform data
        2. Create function that sums two vectors into res (openMP)
        3. Create function that computes the mean and variance (openMP)
        4. Create function that computes inner product (openMP)
        5. Create function that computes the norm product (openMP)
        6. Check that the variance has to be ~4/3 for res (openMP)
        7. PRO: Fill vectors v1 and v2 using parallel threads (random vector)
    */

    return 0;
}
