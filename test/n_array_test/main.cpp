#include <gtest/gtest.h>
#include <n_array.h>

TEST(TestNaiveArray, SimpleTest) {
    naive::array<int> arr = {1, 2, 3};
    ASSERT_TRUE(arr[1] == 2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}