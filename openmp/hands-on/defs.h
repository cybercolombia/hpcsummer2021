#include <sys/time.h>
#include <unordered_map>
#include <string>

/*
    OpenMP Headers and helper functions
*/
#ifdef _OPENMP
    #include <omp.h>
    #define TRUE  1
    #define FALSE 0
    // #define OMP_HARD_LIMIT 4
#else
    #define omp_get_thread_num() 0
#endif

void InfoOpenMP(void){
#ifdef _OPENMP
    std::unordered_map<unsigned,std::string> map{
        {200505,"2.5"},{200805,"3.0"},
        {201107,"3.1"},{201307,"4.0"},
        {201511,"4.5"},{201811,"5.0"},
        {202011,"5.1"}
    };
    std::cout<<"[OMP] OpenMP enabled"<<std::endl;
#ifdef OMP_HARD_LIMIT
    (void) omp_set_num_threads(OMP_HARD_LIMIT);
#endif
    std::cout<<"[OMP] num threads "<<omp_get_num_threads()<<std::endl;
    std::cout << "[OMP] {INFO} API version: " << map.at(_OPENMP) << ".\n";
#else
    std::cout<<"[OMP] OpenMP disabled"<<std::endl;
#endif
}

/*
    Compute array sizes the human way!
*/
void VectorMemUsage(unsigned int bytes,std::string s=""){
    char r_array[128] = "0 Bytes";
    if (bytes > 0){
        if (bytes >= 1073741824) snprintf(
            r_array, sizeof r_array,
            "%.2f GBytes", (((float) bytes)/1073741824)
        );
        else if (bytes >= 1048576) snprintf(
            r_array, sizeof r_array,
            "%.2f MBytes", (((float) bytes)/1048576)
        );
        else if (bytes >= 1024) snprintf(
            r_array, sizeof r_array,
            "%.2f KBytes", (((float) bytes)/1024)
        );
        else snprintf(
            r_array, sizeof r_array,
            "%d Bytes", bytes
        );
    }
    std::cout << "[Vector] '"<<s<<"' mem usage = " << r_array << std::endl;
};


/*
    Simple timer class
*/
class SimpleTimer{

protected:

    timeval start_tv,end_tv;
    long long start_time;
    long long end_time;
    double mu_sec;
    std::string t;

public:

    SimpleTimer(std::string tag = "[SimpleTimer]") : t(tag) { };
    ~SimpleTimer(void){ };

    void start(std::string retag = ""){
        if(retag != "")
            t = retag;
        gettimeofday(&start_tv,NULL);
        gettimeofday(&end_tv,NULL);
        mu_sec = 0;
    }

    void stop(void){
        gettimeofday(&end_tv,NULL);
        start_time=start_tv.tv_sec*1000000LL+start_tv.tv_usec;
        end_time=end_tv.tv_sec*1000000LL+end_tv.tv_usec;
        mu_sec=(double) (end_time-start_time);
    }

    double delta(void){ return mu_sec; };//Microseconds

    void print(void){
        if(mu_sec > 60e6){ // We are talking in minutes
            uint32_t min;
            double sec;
            min = (uint32_t) mu_sec/6.0e7;
            sec = mu_sec*1.0e-6 - 60*min;
            std::cout<<t<<"\t"<<sec<<":"<<mu_sec*1.0e-6<<" min"<<std::endl;
        }
        else if(mu_sec > 1e6) // We are talking in seconds
            std::cout<<t<<"\t"<<mu_sec*1.0e-6<<" s"<<std::endl;
        else if(mu_sec > 1e3) // We are talking in miliseconds
            std::cout<<t<<"\t"<<mu_sec*1.0e-3<<" ms"<<std::endl;
        else if(mu_sec > 1e3) // We are talking in microseconds
            std::cout<<t<<"\t"<<mu_sec<<" mu_s"<<std::endl;
    };

};
