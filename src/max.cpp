#include <iostream>
#include <list>
#include <thread>
#include <chrono>
#include <cstdint>
#include <vector>
#include <math.h>

std::vector<int32_t> vec = {11,4,-3,2,1,8,5,4,5,-12,4,6,2,7,4,2,5,7,8,1,2,6,7,53,1,99,33,23,4,6,7,3,2,4,6,76,4,6,7,5,56,7,3,4,65,7,9,1,34,6,78,5,8,9,3,6,7,4,2,5,7,8,9,21,2,5,4,9};

int32_t maximum(std::vector<int32_t> &input){ // Takes 3 numbers, return the largest one
    if(input.empty()){
        return 0;
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
        vec1.clear();
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