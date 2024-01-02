#include <n_sort.h>
#include <n_vector.h>
#include <gtest/gtest.h>
#include <test_stuff/test_utils.h>

TEST(TestNaiveSort, BubbleSort) {
    auto n = 10000;
    naive::vector<int> v(n);
    fill_rnd_nums(v.begin(), v.end(), -1000, 1000);
    naive::bubble_sort(v.begin(), v.end());
    ASSERT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(TestNaiveSort, SelectionSort) {
    auto n = 10000;
    naive::vector<int> v(n);
    fill_rnd_nums(v.begin(), v.end(), -1000, 1000);
    naive::selection_sort(v.begin(), v.end());
    ASSERT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(TestNaiveSort, InsertionSort) {
    auto n = 10000;
    naive::vector<int> v(n);
    fill_rnd_nums(v.begin(), v.end(), -1000, 1000);
    naive::insertion_sort(v.begin(), v.end());
    ASSERT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(TestNaiveSort, CountingSort) {
    auto n = 10000;
    naive::vector<int> v(n);
    fill_rnd_nums(v.begin(), v.end(), -1000, 1000);
    naive::counting_sort(v.begin(), v.end());
    ASSERT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(TestNaiveSort, QuickSort) {
    auto n = 10000;
    naive::vector<int> v(n);
    fill_rnd_nums(v.begin(), v.end(), -1000, 1000);
    auto start = std::chrono::steady_clock::now();
    naive::quick_sort(v.begin(), v.end());
    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << '\n';
    ASSERT_TRUE(std::is_sorted(v.begin(), v.end()));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}