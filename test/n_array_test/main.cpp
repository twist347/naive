#include <gtest/gtest.h>
#include <n_array.h>

TEST(TestNaiveArray, TraitsTest) {
    using t = naive::array<std::string>;
    static_assert(std::is_same_v<t::value_type, std::string>);
    static_assert(std::is_same_v<t::size_type, std::size_t>);
    static_assert(std::is_same_v<t::reference, std::string &>);
    static_assert(std::is_same_v<t::const_reference, const std::string &>);
    static_assert(std::is_same_v<t::pointer, std::string *>);
    static_assert(std::is_same_v<t::const_pointer, const std::string *>);
    static_assert(std::is_same_v<t::iterator, std::string *>);
    static_assert(std::is_same_v<t::const_iterator, const std::string *>);
    static_assert(std::is_same_v<t::reverse_iterator, std::reverse_iterator<std::string *>>);
    static_assert(std::is_same_v<t::const_reverse_iterator, std::reverse_iterator<const std::string *>>);
    static_assert(std::is_same_v<t::difference_type, std::ptrdiff_t>);
    ASSERT_TRUE(1);
}

TEST(TestNaiveArray, DefaultConstructorTest) {
    naive::array<std::string> arr;
    ASSERT_EQ(arr.size(), 0);
}


TEST(TestNaiveArray, SizeConstructorTest) {
    naive::array<std::string> arr(3);
    ASSERT_EQ(arr.size(), 3);
}

TEST(TestNaiveArray, SizeAndValConstructorTest) {
    naive::array<std::string> arr(3, "hello");
    ASSERT_EQ(arr.size(), 3);
    for (const auto &val: arr) {
        ASSERT_EQ(val, "hello");
    }
}

TEST(TestNaiveArray, InitListConstructorTest) {
    naive::array<std::string> arr{"hello", "world", "c++"};
    ASSERT_EQ(arr.size(), 3);
    ASSERT_EQ(arr[0], "hello");
    ASSERT_EQ(arr[1], "world");
    ASSERT_EQ(arr[2], "c++");
}

TEST(TestNaiveArray, CopyConstructorTest) {
    naive::array<std::string> arr{"hello", "world", "c++"};
    auto other = arr;
    ASSERT_EQ(other.size(), arr.size());
    ASSERT_EQ(arr[0], "hello");
    ASSERT_EQ(arr[1], "world");
    ASSERT_EQ(arr[2], "c++");
    ASSERT_EQ(other[0], "hello");
    ASSERT_EQ(other[1], "world");
    ASSERT_EQ(other[2], "c++");
}

TEST(TestNaiveArray, CopyAssignmentTest) {
    naive::array<std::string> arr{"hello", "world", "c++"};
    naive::array<std::string> other{"java", "python"};
    other = arr;
    ASSERT_EQ(other.size(), arr.size());
    ASSERT_EQ(other.size(), arr.size());
    ASSERT_EQ(arr[0], "hello");
    ASSERT_EQ(arr[1], "world");
    ASSERT_EQ(arr[2], "c++");
    ASSERT_EQ(other[0], "hello");
    ASSERT_EQ(other[1], "world");
    ASSERT_EQ(other[2], "c++");
}

TEST(TestNaiveArray, MoveConstructorTest) {
    naive::array<std::string> arr{"hello", "world", "c++"};
    auto sz = arr.size();
    auto other = std::move(arr);
    ASSERT_EQ(other.size(), sz);
    ASSERT_EQ(other[0], "hello");
    ASSERT_EQ(other[1], "world");
    ASSERT_EQ(other[2], "c++");
}

TEST(TestNaiveArray, MoveAssignmentTest) {
    naive::array<std::string> arr{"hello", "world", "c++"};
    naive::array<std::string> other{"java", "python"};
    auto arr_sz = arr.size(), other_arr = other.size();
    other = std::move(arr);
    ASSERT_EQ(other.size(), arr_sz);
    ASSERT_EQ(other[0], "hello");
    ASSERT_EQ(other[1], "world");
    ASSERT_EQ(other[2], "c++");
}

TEST(TestNaiveArray, SubscriptOperatorTest) {
    naive::array<std::string> arr{"hello", "world", "c++"};
    naive::array<std::string> carr{"java", "python"};
    ASSERT_EQ(arr[2], "c++");
    ASSERT_EQ(carr[1], "python");
    decltype(arr)::value_type val = "good";
    arr[2] = val;
    ASSERT_EQ(arr[2], val);
}

TEST(TestNaiveArray, DataMethodTest) {
    naive::array<std::string> arr{"hello", "world", "c++"};
    naive::array<std::string> carr{"java", "python"};
    auto d = arr.data();
    auto cd = carr.data();
    ASSERT_EQ(*(d + 2), "c++");
    ASSERT_EQ(*(cd + 1), "python");
    decltype(arr)::value_type val = "good";
    *(d + 2) = val;
    ASSERT_EQ(arr[2], val);
    ASSERT_EQ(*(d + 2), val);
}

TEST(TestNaiveArray, AtMethodTest) {
    naive::array<std::string> arr{"hello", "world", "c++"};
    naive::array<std::string> carr{"java", "python"};
    ASSERT_EQ(arr.at(0), "hello");
    ASSERT_EQ(carr.at(1), "python");
    ASSERT_THROW(arr.at(10), std::out_of_range);
    ASSERT_THROW(carr.at(9), std::out_of_range);
    decltype(arr)::value_type val = "good";
    arr.at(2) = val;
    ASSERT_EQ(arr.at(2), val);
}

TEST(TestNaiveArray, FrontMethodTest) {
    naive::array<std::string> arr{"hello", "world", "c++"};
    naive::array<std::string> carr{"java", "python"};
    ASSERT_EQ(arr.front(), "hello");
    ASSERT_EQ(carr.front(), "java");
    decltype(arr)::value_type val = "good";
    arr.front() = val;
    ASSERT_EQ(arr.front(), val);
}

TEST(TestNaiveArray, BacktMethodTest) {
    naive::array<std::string> arr{"hello", "world", "c++"};
    naive::array<std::string> carr{"java", "python"};
    ASSERT_EQ(arr.back(), "c++");
    ASSERT_EQ(carr.back(), "python");
    decltype(arr)::value_type val = "good";
    arr.back() = val;
    ASSERT_EQ(arr.back(), val);
}

TEST(TestNaiveArray, IteratorsTest) {
    naive::array<std::string> arr{"hello", "world", "c++"};
    naive::array<std::string> carr{"java", "python"};
    ASSERT_EQ(*arr.begin(), "hello");
    ASSERT_EQ(*(arr.begin() + 1), "world");
    ASSERT_EQ(*(arr.begin() + 2), "c++");
    ASSERT_EQ(*carr.cbegin(), "java");
    ASSERT_EQ(*(carr.cbegin() + 1), "python");
    *arr.begin() = "good";
    ASSERT_EQ(*arr.begin(), "good");
}

TEST(TestNaiveArray, ReverseIteratorsTest) {
    naive::array<std::string> arr{"hello", "world", "c++"};
    naive::array<std::string> carr{"java", "python"};
    auto back_arr = arr.back(), back_carr = carr.back();
    ASSERT_EQ(*(arr.rbegin()), "c++");
    ASSERT_EQ(*(arr.rbegin() + 2), "hello");
    ASSERT_EQ(*(arr.rend() - 1), "hello");
    ASSERT_EQ(*(carr.crbegin()), "python");
    ASSERT_EQ(*(carr.crend() - 1), "java");
    *arr.begin() = "good";
    ASSERT_EQ(*arr.begin(), "good");
}

TEST(TestNaiveArray, SizeandEmptyMethodsTest) {
    naive::array<std::string> arr{"hello", "world", "c++"}, earr;
    ASSERT_EQ(earr.size(), 0);
    ASSERT_TRUE(earr.empty());

    ASSERT_EQ(arr.size(), static_cast<decltype(earr)::size_type>(3));
    ASSERT_FALSE(arr.empty());
}

TEST(TestNaiveArray, FillMethodTest) {
    naive::array<std::string> arr(3), other{"hello", "world", "c++"};
    auto val = "good";
    arr.fill(val);
    other.fill(val);
    for (const auto &i: arr) {
        ASSERT_EQ(i, val);
    }

    for (const auto &i: other) {
        ASSERT_EQ(i, val);
    }
}

TEST(TestNaiveArray, SwapMethodTest) {
    naive::array<std::string> arr{"hello", "world", "c++"};
    naive::array<std::string> other{"java", "python"};
    auto arr_sz = arr.size(), other_sz = other.size();
    arr.swap(other);
    ASSERT_EQ(arr.size(), other_sz);
    ASSERT_EQ(other.size(), arr_sz);
    ASSERT_EQ(arr[0], "java");
    ASSERT_EQ(arr[1], "python");
    ASSERT_EQ(other[0], "hello");
    ASSERT_EQ(other[1], "world");
    ASSERT_EQ(other[2], "c++");
}

TEST(TestNaiveArray, EqualOperatorTest) {
    naive::array<std::string> arr{"hello", "world", "c++"};
    naive::array<std::string> arr1{"hello", "world", "c++"};
    naive::array<std::string> other1{"java", "python"};
    naive::array<std::string> other2{"java", "rust"};
    ASSERT_EQ(arr, arr1);
    ASSERT_NE(arr, other2);
    ASSERT_NE(arr, other1);
}

TEST(TestNaiveArray, ExceptionSafetyTest) {
    static int count = 0;

    struct bad_struct {

        bad_struct() = default;

        bad_struct(bad_struct &&) = default;

        bad_struct &operator=(bad_struct &&) = default;

        bad_struct(const bad_struct &) {
            ++count;
            if (count == 5) {
                count = 0;
                throw std::bad_alloc{};
            }
            std::cout << "copying\n";
        }

        bad_struct &operator=(const bad_struct &other) {
            bad_struct copy(other);
            std::swap(*this, copy);
            return *this;
        }

        ~bad_struct() = default;
    };

    bad_struct b1, b2, b3;
    naive::array<bad_struct> v(3);
    v[0] = b1;
    v[1] = b2;
    v[2] = b3;
    try {
        auto v1 = v; // oops
    } catch (std::bad_alloc &) {
        std::cout << "exception catched\n";
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}