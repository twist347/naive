#include <gtest/gtest.h>
#include <n_type_traits.h>


TEST(TestTypeTraits, IntegtalConstant) {
    using a = naive::integral_constant<int, 3>;
    using b = naive::integral_constant<int, 6>;
    static_assert(2 * a::value == b::value);
    static_assert(!naive::is_same_v<a, b>);
    static_assert(!naive::is_same_v<a::type, b::type>);

    using b1 = naive::bool_constant<true>;
    using b2 = naive::bool_constant<false>;
    static_assert(std::is_same_v<b1, naive::true_type>);
    static_assert(std::is_same_v<b2, naive::false_type>);
    ASSERT_TRUE(true);
}

// primary type categories

TEST(TestTypeTraits, IsVoid) {
    static_assert(naive::is_void_v<void>);
    static_assert(!naive::is_void_v<int>);
    static_assert(!naive::is_void_v<std::string>);
    static_assert(!naive::is_void_v<int *>);
    static_assert(!naive::is_void_v<const int &>);
    static_assert(!naive::is_void_v<void *>);
    ASSERT_TRUE(true);
}

TEST(TestTypeTraits, IsNullPointer) {
    static_assert(naive::is_null_pointer_v<decltype(nullptr)>);
    static_assert(!naive::is_null_pointer_v<int>);
    ASSERT_TRUE(true);
}

TEST(TestTypeTraits, IsFloatingPoint) {
    static_assert(naive::is_floating_point_v<float>);
    static_assert(naive::is_floating_point_v<double>);
    static_assert(naive::is_floating_point_v<long double>);
    static_assert(!naive::is_floating_point_v<int>);
    static_assert(!naive::is_floating_point_v<double *>);
    static_assert(naive::is_floating_point_v<const double>);
    ASSERT_TRUE(true);
}

TEST(TestTypeTraits, IsArray) {
    static_assert(naive::is_array_v<int[]>);
    static_assert(naive::is_array_v<int[5]>);
    static_assert(!naive::is_array_v<int *>);
    ASSERT_TRUE(true);
}

TEST(TestTypeTraits, IsPointer) {
    static_assert(naive::is_pointer_v<int *>);
    static_assert(naive::is_pointer_v<const int *>);
    static_assert(!naive::is_pointer_v<int &>);
    ASSERT_TRUE(true);
}

TEST(TestTypeTraits, IsLvalueReference) {
    static_assert(naive::is_lvalue_reference_v<int &>);
    static_assert(naive::is_lvalue_reference_v<const int &>);
    ASSERT_TRUE(true);
}

TEST(TestTypeTraits, IsRvalueReference) {
    static_assert(naive::is_rvalue_reference_v<int &&>);
    static_assert(!naive::is_rvalue_reference_v<int &>);
    ASSERT_TRUE(true);
}

TEST(TestTypeTraits, Rank) {
    static_assert(naive::rank_v<int> == 0);
    static_assert(naive::rank_v<int[]> == 1);
    static_assert(naive::rank_v<int[][3]> == 2);
    static_assert(naive::rank_v<int[][2][3]> == 3);
    ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}