#include <iostream>
#include <list>
#include <thread>
#include <chrono>
#include <cstdint>
#include <vector>
#include <math.h>
#include <atomic>
#include <random>

std::random_device rd;
std::uniform_int_distribution<int32_t> dist(-9999999,9999999);
std::vector<int32_t> vec(10000000u);

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
    std::vector<int32_t> vec2;
    std::atomic<int32_t> result(0);

    for(auto i{1uz}; i<=std::thread::hardware_concurrency(); ++i){
        std::vector<int32_t> v(in.begin(), in.begin() + in.size()/std::thread::hardware_concurrency() + (in.size()%std::thread::hardware_concurrency()));
        vec1.clear();
        vec1.insert_range(vec1.begin(), v);
        in.erase(in.begin(), in.begin() + v.size());

        std::thread t([&](){
            result.exchange(maximum(vec1));
        });
        t.join();

        vec2.emplace_back(result.load());
    }
    std::cout << maximum(vec2);
}

int main(){

    for(auto i {0uz}; i < vec.size(); ++i){
        vec[i] = dist(rd);
    }

    auto start = std::chrono::high_resolution_clock::now();
    split(vec);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "\nTime: " << duration.count() << " Microseconds";

    return 0;
}