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

    int v[] = {-2,4,5,1,-3,0,0,1};
    #pragma omp parallel private(v)
    {
        int TID = omp_get_thread_num();
        #pragma omp critical
        {
            printf("\tInside Block - Thread ID is %d\n",TID);
            v[TID%8] = 100;
            sleep(1);
            cout<<"OMP:: [ ";
            for(int i=0;i<8;i++){
                cout<<v[i];
                if(i!=7)
                    cout<<", ";
            }
            cout<<" ]"<<endl;
        }
        printf("In parallel region - Thread ID is %d\n",TID);
    } /*-- End of parallel region --*/

    cout<<"[ ";
    for(int i=0;i<8;i++){
        cout<<v[i];
        if(i!=7)
            cout<<", ";
    }
    cout<<" ]"<<endl;


    return 0;
}
