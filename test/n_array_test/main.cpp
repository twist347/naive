#include <gtest/gtest.h>
#include <n_array.h>

TEST(TestNaiveArray, TraitsTest) {
    using t = naive::array<int>;
    static_assert(std::is_same_v<t::value_type, int>);
    static_assert(std::is_same_v<t::size_type, std::size_t>);
    static_assert(std::is_same_v<t::reference, int &>);
    static_assert(std::is_same_v<t::const_reference, const int &>);
    static_assert(std::is_same_v<t::pointer, int *>);
    static_assert(std::is_same_v<t::const_pointer, const int *>);
    static_assert(std::is_same_v<t::iterator, int *>);
    static_assert(std::is_same_v<t::const_iterator, const int *>);
    static_assert(std::is_same_v<t::reverse_iterator, std::reverse_iterator<int *>>);
    static_assert(std::is_same_v<t::const_reverse_iterator, std::reverse_iterator<const int *>>);
    static_assert(std::is_same_v<t::difference_type, std::ptrdiff_t>);
    ASSERT_TRUE(1);
}


TEST(TestNaiveArray, DefaultConstructorTest) {
    naive::array<int> arr;
    ASSERT_EQ(arr.size(), naive::utils::to<decltype(arr)::size_type>(0));
}


TEST(TestNaiveArray, SizeConstructorTest) {
    naive::array<int> arr(3);
    ASSERT_EQ(arr.size(), naive::utils::to<decltype(arr)::size_type>(3));
}

TEST(TestNaiveArray, SizeAndValConstructorTest) {
    naive::array<int> arr(3, 5);
    ASSERT_EQ(arr.size(), 3);
    for (auto val: arr) {
        ASSERT_EQ(val, 5);
    }
}

TEST(TestNaiveArray, InitListConstructorTest) {
    naive::array<int> arr{1, 2, 3, 4, 5};
    ASSERT_EQ(arr.size(), 5);
    for (size_t i = 0; i < arr.size(); ++i) {
        ASSERT_EQ(arr[i], i + 1);
    }
}

TEST(TestNaiveArray, CopyConstructorTest) {
    naive::array<int> arr{1, 2, 3, 4, 5};
    auto other = arr;
    ASSERT_EQ(other.size(), arr.size());
    for (size_t i = 0; i < other.size(); ++i) {
        ASSERT_EQ(arr[i], other[i]);
    }
}

TEST(TestNaiveArray, CopyAssignmentTest) {
    naive::array<int> arr{1, 2, 3, 4, 5};
    naive::array<int> other{1, 2, 3};
    other = arr;
    ASSERT_EQ(other.size(), arr.size());
    for (size_t i = 0; i < other.size(); ++i) {
        ASSERT_EQ(arr[i], other[i]);
    }
}

TEST(TestNaiveArray, MoveConstructorTest) {
    naive::array<int> arr{1, 2, 3, 4, 5};
    auto sz = arr.size();
    auto other = std::move(arr);
    ASSERT_EQ(arr.size(), naive::utils::to<decltype(arr)::size_type>(0));
    ASSERT_EQ(other.size(), sz);
    for (size_t i = 0; i < other.size(); ++i) {
        ASSERT_EQ(other[i], i + 1);
    }
}

TEST(TestNaiveArray, MoveAssignmentTest) {
    naive::array<int> arr{1, 2, 3, 4, 5};
    naive::array<int> other{1, 2, 3};
    auto arr_sz = arr.size(), other_arr = other.size();
    other = std::move(arr);
    ASSERT_EQ(arr.size(), naive::utils::to<decltype(arr)::size_type>(0));
    ASSERT_EQ(other.size(), arr_sz);
    for (size_t i = 0; i < other.size(); ++i) {
        ASSERT_EQ(other[i], i + 1);
    }
}

TEST(TestNaiveArray, SubscriptOperatorTest) {
    naive::array<int> arr{1, 2, 3, 4, 5};
    const naive::array<int> carr{1, 2, 3};
    ASSERT_EQ(arr[2], 3);
    ASSERT_EQ(carr[1], 2);
    decltype(arr)::value_type val = 812;
    arr[2] = val;
    ASSERT_EQ(arr[2], val);
}

TEST(TestNaiveArray, DataMethodTest) {
    naive::array<int> arr{1, 2, 3, 4, 5};
    const naive::array<int> carr{1, 2, 3};
    auto d = arr.data();
    auto cd = carr.data();
    ASSERT_EQ(*(d + 2), 3);
    ASSERT_EQ(*(cd + 1), 2);
    decltype(arr)::value_type val = 812;
    *(d + 2) = val;
    ASSERT_EQ(arr[2], val);
    ASSERT_EQ(*(d + 2), val);
}

TEST(TestNaiveArray, AtMethodTest) {
    naive::array<int> arr{1, 2, 3, 4, 5};
    const naive::array<int> carr{1, 2, 3};
    ASSERT_EQ(arr.at(0), 1);
    ASSERT_EQ(carr.at(2), 3);
    ASSERT_THROW(arr.at(10), std::out_of_range);
    ASSERT_THROW(carr.at(9), std::out_of_range);
    decltype(arr)::value_type val = 123;
    arr.at(2) = val;
    ASSERT_EQ(arr.at(2), val);
}

TEST(TestNaiveArray, FrontMethodTest) {
    naive::array<int> arr{1, 2, 3, 4, 5};
    const naive::array<int> carr{1, 2, 3};
    ASSERT_EQ(arr.front(), 1);
    ASSERT_EQ(carr.front(), 1);
    decltype(arr)::value_type val = 319;
    arr.front() = val;
    ASSERT_EQ(arr.front(), val);
}

TEST(TestNaiveArray, BacktMethodTest) {
    naive::array<int> arr{1, 2, 3, 4, 5};
    const naive::array<int> carr{1, 2, 3};
    ASSERT_EQ(arr.back(), 5);
    ASSERT_EQ(carr.back(), 3);
    decltype(arr)::value_type val = 319;
    arr.back() = val;
    ASSERT_EQ(arr.back(), val);
}

TEST(TestNaiveArray, IteratorsTest) {
    naive::array<int> arr{1, 2, 3, 4, 5};
    const naive::array<int> carr{1, 2, 3};
    decltype(arr)::value_type val = 0;
    for (auto it = arr.begin(), it_end = arr.end(); it != it_end; ++it) {
        ASSERT_EQ(*it, ++val);
    }
    val = 0;
    for (auto it = carr.begin(), it_end = carr.end(); it != it_end; ++it) {
        ASSERT_EQ(*it, ++val);
    }
    for (auto it = arr.begin(), it_end = arr.end(); it != it_end; ++it) {
        auto tmp = *it;
        *it = tmp * tmp;
        ASSERT_EQ(*it, tmp * tmp);
    }
}

TEST(TestNaiveArray, ReverseIteratorsTest) {
    naive::array<int> arr{1, 2, 3, 4, 5};
    const naive::array<int> carr{1, 2, 3};
    decltype(arr)::value_type back_arr = arr.back(), back_carr = carr.back();
    for (auto it = arr.rbegin(), it_end = arr.rend(); it != it_end; ++it) {
        ASSERT_EQ(*it, back_arr--);
    }
    for (auto it = carr.rbegin(), it_end = carr.rend(); it != it_end; ++it) {
        ASSERT_EQ(*it, back_carr--);
    }
    for (auto it = arr.begin(), it_end = arr.end(); it != it_end; ++it) {
        auto tmp = *it;
        *it = tmp * tmp;
        ASSERT_EQ(*it, tmp * tmp);
    }
}

TEST(TestNaiveArray, ConstReverseIteratorsTest) {
    naive::array<int> arr{1, 2, 3, 4, 5};
    const naive::array<int> carr{1, 2, 3};
    decltype(arr)::value_type back_arr = arr.back(), back_carr = carr.back();
    for (auto it = arr.crbegin(), it_end = arr.crend(); it != it_end; ++it) {
        ASSERT_EQ(*it, back_arr--);
    }
    for (auto it = carr.crbegin(), it_end = carr.crend(); it != it_end; ++it) {
        ASSERT_EQ(*it, back_carr--);
    }
}

TEST(TestNaiveArray, SizeandEmptyMethodsTest) {
    naive::array<int> earr, arr{1, 2, 3};
    ASSERT_EQ(earr.size(), naive::utils::to<decltype(earr)::size_type>(0));
    ASSERT_TRUE(earr.empty());

    ASSERT_EQ(arr.size(), naive::utils::to<decltype(earr)::size_type>(3));
    ASSERT_FALSE(arr.empty());
}

TEST(TestNaiveArray, FillMethodTest) {
    naive::array<int> arr(3), other{1, 2, 3, 4, 5};
    auto val = 25;
    arr.fill(val);
    other.fill(val);
    for (auto i: arr) {
        ASSERT_EQ(i, val);
    }

    for (auto i: other) {
        ASSERT_EQ(i, val);
    }
}

TEST(TestNaiveArray, SwapMethodTest) {
    naive::array<int> arr{1, 2, 3}, other{1, 2, 3, 4, 5};
    auto arr_sz = arr.size(), other_sz = other.size();
    arr.swap(other);
    auto val = 0;
    ASSERT_EQ(arr.size(), other_sz);
    ASSERT_EQ(other.size(), arr_sz);
    for (auto i: arr) {
        ASSERT_EQ(i, ++val);
    }
    val = 0;
    for (auto i: other) {
        ASSERT_EQ(i, ++val);
    }
}

TEST(TestNaiveArray, EqualOperatorTest) {
    naive::array<int> arr{1, 2, 3}, other1{1, 2, 3}, other2{1, 2, 3, 4, 5}, other3{4, 5, 6};
    ASSERT_EQ(arr, other1);
    ASSERT_NE(arr, other2);
    ASSERT_NE(arr, other3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}