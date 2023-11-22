#pragma once

#include <iostream>
#include <string>
#include <random>
#include <chrono>

template<class T>
void print_vec(const T &t) {
    std::cout << "size: " << t.size() << ", cap: " << t.capacity() << '\n';
    if constexpr (std::is_fundamental_v<typename T::value_type>
            || std::is_same_v<typename T::value_type, std::string>) {
        for (auto &&i: t) {
            std::cout << i << ' ';
        }
    }
    std::cout << '\n';
}

template<class Iter, class Value>
constexpr void fill_rnd_nums(Iter first, Iter last, Value min, Value max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dis(min, max);
    for (auto it = first; it != last; ++it) {
        *it = dis(gen);
    }
}
