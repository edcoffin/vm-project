#include "simple.hpp"

int32_t simple(int32_t a){
     a = a + 1;
     return a;
}

int32_t simple_runner(int32_t a, int32_t count){
    int32_t result = 0;
    for(int i = 0; i < count; i++){
        result += simple(a);
    }
    return result;
}