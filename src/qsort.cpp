#include <iostream>
#include <cstdint>
#include <vector>
#include <math.h>
#include <random>
#include <chrono>

std::random_device rd;
std::uniform_int_distribution<int32_t> dist(-9999999,9999999);
std::vector<int32_t> vec(10000000u);

int32_t partition(std::vector<int32_t> &vec, int32_t start, int32_t end){
    int32_t pivot = vec[end];
    int32_t mid = start;

    for(auto i {start}; i < end; ++i){
        if(vec[i] < pivot){
            if(mid != i){
                int32_t tmp = vec[i];
                vec[i] = vec[mid];
                vec[mid] = tmp;
            }
            mid++;
        }
    }
    vec[end] = vec[mid];
    vec[mid] = pivot;

    return mid;
}

void qsort(std::vector<int32_t> &v, int32_t start, int32_t end){

    if(start >= end){ return; }
    int32_t mid = partition(v,start,end);

    qsort(v, start, mid - 1);
    qsort(v, mid + 1, end);
}

int main(){

     for(auto i {0uz}; i < vec.size(); ++i){
        vec[i] = dist(rd);
    }

    auto start = std::chrono::high_resolution_clock::now();
    qsort(vec, 0, vec.size() - 1);
    std::cout << vec.back();
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "\nTime: " << duration.count() << " Microseconds";

    return 0;
}