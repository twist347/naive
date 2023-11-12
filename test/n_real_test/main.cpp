#include <gtest/gtest.h>
#include <n_real.h>

TEST(TestNaiveReal, SimpleTest) {
    naive::real r{3.14};
    ASSERT_DOUBLE_EQ(2 * r, 6.28);
}

TEST(TestNaiveReal, SpaceshipOperator) {
    using namespace naive;
    real x{3.1}, y {3.1};
    std::cout << (x == y) << '\n';
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}