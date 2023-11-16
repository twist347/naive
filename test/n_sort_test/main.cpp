#include <n_sort.h>
#include <n_vector.h>
#include <iostream>
#include <gtest/gtest.h>
#include <random>

template<class Iter, class Value>
constexpr void fill_rnd_nums(Iter first, Iter last, Value min, Value max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    for (auto it = first; it != last; ++it) {
        *it = dis(gen);
    }
}

TEST(TestNaiveSort, BubbleSort) {
    auto n = 1000;
    naive::vector<int> v(n);
    fill_rnd_nums(v.begin(), v.end(), -1000, 1000);
    naive::bubble_sort(v.begin(), v.end());
    ASSERT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(TestNaiveSort, SelectionSort) {
    auto n = 1000;
    naive::vector<int> v(n);
    fill_rnd_nums(v.begin(), v.end(), -1000, 1000);
    naive::selection_sort(v.begin(), v.end());
    ASSERT_TRUE(std::is_sorted(v.begin(), v.end()));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}