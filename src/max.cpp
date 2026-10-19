#include <iostream>
#include <list>
#include <thread>
#include <chrono>
#include <cstdint>
#include <vector>
#include <math.h>

std::vector<int32_t> vec = {11,4,-3,2,1,8,5,4,5,-12,4,6,2,7,4,2,5,7,8,1,2,6,7,53,1,99,33,23};

int32_t maximum(std::vector<int32_t> &input){ // Takes 3 numbers, return the largest one
    if(input.empty()){
        throw std::invalid_argument("Empty vector");
    }
    for(auto i{0uz}; i + 1u < input.size(); ++i){
        if(input[i]>input[i+1u]){
            std::swap(input[i],input[i+1u]);
        }
    }
    return input.back();
}

void split(std::vector<int32_t> &in){
    std::vector<int32_t> vec1;
    int32_t result{};

    for(auto i{1uz}; i<=std::thread::hardware_concurrency(); ++i){
        std::vector<int32_t> v(in.begin(), in.begin() + in.size()/std::thread::hardware_concurrency() + (in.size()%std::thread::hardware_concurrency()));
        vec1.insert_range(vec1.begin(), v);
        in.erase(in.begin(), in.begin() + v.size());

        std::thread t([&](){
            result = maximum(vec1);
        });
        t.join();

        std::cout << result << "\n";
    }
}

int main(){

    auto start = std::chrono::high_resolution_clock::now();
    split(vec);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    return 0;
}