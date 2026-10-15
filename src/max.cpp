#include <iostream>
#include <list>
#include <thread>
#include <chrono>
#include <cstdint>
#include <vector>
#include <math.h>

std::vector<int32_t> vec = {11,4,-3,2,1,8,5,4};

void split(std::vector<int32_t> &in){
    
}

int32_t maximum(std::vector<int32_t> &input){ // Takes 3 numbers, return the largest one



    for(auto i{0uz}; i + 1u < input.size(); ++i){
        if(input[i]>input[i+1u]){
            std::swap(input[i],input[i+1u]);
        }
    }
    return input.back();
}

int main(){

    auto start = std::chrono::high_resolution_clock::now();
    std::cout << maximum(vec);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << duration.count();

    return 0;
}