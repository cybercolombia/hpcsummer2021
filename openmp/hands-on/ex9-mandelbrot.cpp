#include <iostream>
#include <fstream>
#include <iterator>
#include <complex>
#include <cmath>
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

#define R_minX -2
#define R_maxX 1
#define R_minY -1
#define R_maxY 1
#ifndef NUM_POINTS
    #define NUM_POINTS 1000
#endif
#ifndef LIMIT
    #define LIMIT 100
#endif

typedef float myprec;
#define Comp std::complex<float>

// int Mandelbrot(Comp z0,uint limit = 100){
//     // Comp z = z0;
//     Comp z(0,0);
//     for (uint i = 0; i < limit; ++i) {
//         if (norm(z) > 4.0)
//             return i;
//         z = z*z + z0;
//     }
//     return limit;
// }
int mandelbrot(double real, double imag) {
    int limit = 100;
    double zReal = real;
    double zImag = imag;

    for (int i = 0; i < limit; ++i) {
        double r2 = zReal * zReal;
        double i2 = zImag * zImag;
        
        if (r2 + i2 > 4.0) return i;

        zImag = 2.0 * zReal * zImag + imag;
        zReal = r2 - i2 + real;
    }
    return limit;
}


int main(void){
    InfoOpenMP();

    SimpleTimer _t;
    uint N;
    uint maxIt;

    cout<<"Part 1: fill the Mandelbrot Matrix"<<endl;

    // Comp z0(R_minX,R_minY);
    // Comp dz_re((R_maxX-R_minX)/N,0);
    // Comp dz_im(0,(R_maxY-R_minY)/N);
    // z0 = z0+(dz_re+dz_im)*Comp(0.5,0);
    float dz_re =(R_maxX-R_minX)/NUM_POINTS;
    float dz_im =(R_maxY-R_minY)/NUM_POINTS;

    uint MandelMat[NUM_POINTS][NUM_POINTS];
    VectorMemUsage(NUM_POINTS*NUM_POINTS*sizeof(uint),"MandelMat");

    _t.start("Compute mandelbrot region");
    for(uint j = 0; j < NUM_POINTS; j++)
        for(uint k = 0; k < NUM_POINTS; k++){
            // MandelMat[j][k] = Mandelbrot(
            //     z0+Comp(j,0)*dz_re+Comp(k,0)*dz_im,maxIt
            // );
            // MandelMat[j][k] = Mandelbrot(
            //     Comp(R_minX+(j+0.5)*dz_re,R_minY+(k+0.5)*dz_im)
            // );
            MandelMat[j][k] = mandelbrot(
                R_minX+(j+0.5)*dz_re,R_minY+(k+0.5)*dz_im
            );
        }
    _t.stop(); _t.print();

    ofstream output_file("./mandelbrot.dat");
    for(uint j = 0; j < NUM_POINTS; j++){
        for(uint k = 0; k < NUM_POINTS; k++)
            output_file<<MandelMat[j][k]<<"  ";
        output_file<<"\n";
    }
    return 0;
}
