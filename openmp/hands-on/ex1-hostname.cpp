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
g++ -std=c++11 -Wall -Wextra ex1-hostname.cpp -o exe -Wno-unknown-pragmas && ./exe
OpenMP Compile:
g++ -std=c++11 -Wall -Wextra -fopenmp ex1-hostname.cpp -o exe && ./exe
*/

int main(void){
    InfoOpenMP();
    // cout.sync_with_stdio(false);

    char hostname[INFO_BUFFER_SIZE];
    char username[INFO_BUFFER_SIZE];

    cout<<"Part 1"<<endl;

    #pragma omp parallel
    {
        gethostname(hostname, INFO_BUFFER_SIZE);
        getlogin_r(username, INFO_BUFFER_SIZE);

        printf("Hostname %s in thread %d\n",hostname,omp_get_thread_num());
        printf("Username %s in thread %d\n",username,omp_get_thread_num());
    } /*-- End of parallel region --*/

    cout<<endl<<"Part 2"<<endl;

    #pragma omp parallel
    {
        gethostname(hostname, INFO_BUFFER_SIZE);
        getlogin_r(username, INFO_BUFFER_SIZE);

        cout<<"Hostname "<<hostname<<" in thread "<<omp_get_thread_num()<<endl;
        cout<<"Username "<<username<<" in thread "<<omp_get_thread_num()<<endl;
    } /*-- End of parallel region --*/

    /*
        Exercise:
        1. Use `std::flush`? How about a critical region?
        2. Where is the race condition?
    */

    return 0;
}
