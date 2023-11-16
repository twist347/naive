#include <gtest/gtest.h>
#include <n_search.h>
#include <n_vector.h>
#include <algorithm>

TEST(TestNaiveSearch, A) {
    naive::vector<int> v{5, 1, 3, 2, 0};
    auto it = naive::linear_search(v.begin(), v.end(), 2);
    ASSERT_NE(it, v.end());
}

TEST(TestNaiveSearch, B) {
    naive::vector<int> v{1, 4, 9, 10, 19, 41};
    auto it = naive::binary_search(v.begin(), v.end(), 41);
    ASSERT_NE(it, v.end());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}