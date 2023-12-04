#include <gtest/gtest.h>
#include <n_real.h>

TEST(TestNaiveReal, Constructor) {
    naive::real r{3.14};
    ASSERT_DOUBLE_EQ(r, 3.14);
}

TEST(TestNaiveReal, PlusOperator) {
    naive::real x{3.14}, y{2.1};
    ASSERT_DOUBLE_EQ(x + y, 5.24);
    x += y;
    ASSERT_DOUBLE_EQ(x, 5.24);
}

TEST(TestNaiveReal, MinusOperator) {
    naive::real x{3.14}, y{2.1};
    ASSERT_DOUBLE_EQ(x - y, 1.04);
    x -= y;
    ASSERT_DOUBLE_EQ(x, 1.04);
}

TEST(TestNaiveReal, MultiplyOperator) {
    naive::real x{3.14}, y{2.1};
    ASSERT_DOUBLE_EQ(x * y, 6.594);
    x *= y;
    ASSERT_DOUBLE_EQ(x, 6.594);
}

TEST(TestNaiveReal, DivideOperator) {
    naive::real x{3.14}, y{2.1};
    ASSERT_DOUBLE_EQ(x / y, 1.4952380952380953);
    x /= y;
    ASSERT_DOUBLE_EQ(x, 1.4952380952380953);
}

TEST(TestNaiveReal, ModeOperator) {
    naive::real x{5}, y{2};
    static_assert(std::is_same_v<decltype(x)::value_type, int>);
    static_assert(std::is_same_v<decltype(y)::value_type, int>);
    ASSERT_EQ(x % y, 1);
}

TEST(TestNaiveReal, IncrementOperator) {
    naive::real<int> x{5};
    ASSERT_EQ(++x, 6);
    auto y = x++;
    ASSERT_EQ(y, 6);
    ASSERT_EQ(x, 7);
}

TEST(TestNaiveReal, DecrementOperator) {
    naive::real<int> x{5};
    ASSERT_EQ(--x, 4);
    auto y = x--;
    ASSERT_EQ(y, 4);
    ASSERT_EQ(x, 3);
}

TEST(TestNaiveReal, AddreessOfOperator) {
    naive::real x{5};
    auto ptr = &x;
    ASSERT_EQ(*ptr, 5);
    *ptr = 100;
    ASSERT_EQ(x, 100);
}

TEST(TestNaiveReal, SpaceshipOperator) {
    using namespace naive;
    real x{3.1}, y{3.1};
    ASSERT_DOUBLE_EQ(x, y);
    real a{5.12}, b{x};
    ASSERT_TRUE(a > b);
    ASSERT_TRUE(b < a);
    ASSERT_TRUE(x >= b);
    ASSERT_TRUE(b <= x);
    ASSERT_TRUE(a != b);
    ASSERT_TRUE(x == b);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}