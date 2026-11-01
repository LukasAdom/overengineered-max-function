#include <iostream>
#include <cstdint>
#include <vector>
#include <math.h>
#include <random>
#include <chrono>

std::random_device rd;
std::uniform_int_distribution<int32_t> dist(-9999999,9999999);
std::vector<int32_t> vec(10000000u);

int32_t maximum(std::vector<int32_t> vec){
    for(auto i{0uz}; i + 1u < vec.size(); ++i){
        if(vec[i]>vec[i+1u]){
            std::swap(vec[i],vec[i+1u]);
        }
    }
    return vec.back();
}

int main(){

     for(auto i {0uz}; i < vec.size(); ++i){
        vec[i] = dist(rd);
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::cout << maximum(vec);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "\nTime: " << duration.count() << " Microseconds";

    return 0;
}