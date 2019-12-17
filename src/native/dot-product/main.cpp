#include <cstdint>
#include <iostream>
using namespace std;

int32_t dotProduct(int32_t *a, int32_t *b, int32_t length ) {
    int32_t result = 0;
    
    for(int i = 0; i < length; i++){
        result += a[i] * b[i];
    }

    return result;
}


int main() {
    cout << "running function";
    
    #define MATRIX_LENGTH 2
    
    int32_t _a [MATRIX_LENGTH] = {1,2};
    int32_t _b [MATRIX_LENGTH] = {1,2};

    int32_t result = dotProduct( _a, _b, MATRIX_LENGTH);
    cout << "Dot product result: " << result << endl;
    return 0;
}