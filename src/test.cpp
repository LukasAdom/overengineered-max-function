#include <iostream>
#include <cstdint>
#include <vector>
#include <math.h>


int16_t maximum(const int16_t a, const int16_t b, const int16_t c){ // Takes 3 numbers, return the largest one
    std::vector<int16_t> vec = {a,b,c};
    std::cout << __func__ << '(' << a << ", " << b << ", " << c << "): ";

    for(auto i{0uz}; i + 1u < vec.size(); ++i){
        if(vec[i]>vec[i+1u]){
            std::swap(vec[i],vec[i+1u]);
        }
    }
    return vec.back();
}

int main(){

    return 0;
}