#include <gtest/gtest.h>
#include <n_vector.h>
#include <vector>

TEST(A, B) {
    naive::vector<int> v {1, 2, 3, 4, 5};
    std::cout << v << '\n';
    std::cout << v.size() << ' ' << v.capacity() << '\n';
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}