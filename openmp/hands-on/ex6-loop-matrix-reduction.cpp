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
g++ -std=c++11 -Wall -Wextra ex6-loop-matrix-reduction.cpp -o exe -Wno-unknown-pragmas && ./exe
OpenMP Compile:
g++ -std=c++11 -Wall -Wextra -fopenmp ex6-loop-matrix-reduction.cpp -o exe && ./exe
*/

#define N 500
#define M 1000
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

    cout<<"Part 1: fill static matrix with random noise"<<endl;

    // Notice it is a static array -> in the stack!
    Decimal A1[N][M],A2[M][N],res[N][N];
    VectorMemUsage(N*M*sizeof(Decimal),"A1");
    VectorMemUsage(M*N*sizeof(Decimal),"A2");
    VectorMemUsage(N*N*sizeof(Decimal),"res");

    for(int j = 0; j < N; j++)
        for(int k = 0; k < M; k++){
            A1[j][k] = normal(gen2);
        }
    for(int j = 0; j < M; j++)
        for(int k = 0; k < N; k++){
            A2[j][k] = unif(gen2);
        }

    _t.start("Matrix Multiply");
    for(int j = 0; j < N; j++)
        for(int k = 0; k < N; k++)
            for(int l = 0; l < M; l++){
                res[j][k] += A1[j][l]*A2[l][k];
            }
    _t.stop(); _t.print();

    /*
        Exercise:
        0. Set timers!
        1. Fill matrix A2 with uniform data
        2. Create function that multiplies A1 and A2 (openMP)
        3. Create function that computes the mean and variance (openMP)
        4. PRO: Fill matrices in parallel using threads
        5. PRO: Can you average the time to fork and join threads?
        6. PRO: Can you increase the size of the matrices? -> vector+array
    */



    return 0;
}
