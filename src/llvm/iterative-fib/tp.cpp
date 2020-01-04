#include <stdio.h>
#include <iostream>
#include <fstream>

#include "fib.hpp"

int main(int argc, char *argv[]) {

    if(argc < 4) {
        printf("Invalid arguments: 1=out_file,2=time_in_sec,3=time_in_nanosec");
        return -1;
    }
    
    std::ofstream outfile (argv[1]);
    int32_t time_in_sec = atoi(argv[2]);
    int32_t time_in_ns = atoi(argv[3]);

    std::cout << "Outfile: " << argv[1] << ", time_in_sec=" << time_in_sec;
    std::cout << ", time_in_nanosec=" << time_in_ns << std::endl;

    testThroughput(outfile, time_in_sec, time_in_ns);
    //RecursiveFibonnaciMethod::testThroughput(outfile, time_in_sec, time_in_ns);

    outfile.close();
    return 0;
}