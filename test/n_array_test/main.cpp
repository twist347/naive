#include <gtest/gtest.h>
#include "n_array.h"
#include "n_real.h"

TEST(A, B) {
    naive::real r{3.14};
    ASSERT_TRUE(r == 3.14);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}