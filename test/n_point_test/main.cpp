#include <gtest/gtest.h>
#include <n_point.h>

TEST(A, B) {
    naive::point<3> p1{1.0, 2.0, 3.0};
    naive::point<3> p2{1.0, 2.0, 3.0};
    auto p3 = p1 + p2;
    std::cout << p3 << '\n';
    ASSERT_EQ(p3[1], 4.0);
}

TEST(A, C) {
    naive::point<2> x{1.0, 2.0};
    naive::point<2> y{1.0, 2.0};
    auto res = x * y;
    std::cout << res << '\n';
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}