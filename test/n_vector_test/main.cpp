#include <gtest/gtest.h>
#include <n_vector.h>
#include <vector>
#include <log_struct.h>
#include <test_stuff/test_utils.h>

TEST(TestNaiveVector, DefaultConstructorTest) {
    naive::vector<int> v;
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), 0);
}

TEST(TestNaiveVector, SizeConstructorTest) {
    std::vector<int> v(3);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v.capacity(), 3);
}

TEST(TestNaiveVector, SizeAndValConstructorTest) {
    naive::vector<int> v(3, 5);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v.capacity(), 3);
    for (auto val: v) {
        ASSERT_EQ(val, 5);
    }
}

TEST(TestNaiveVector, InitListConstructorTest) {
    naive::vector<int> v{1, 2, 3};
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v.capacity(), 3);
    auto i = 0;
    for (auto val: v) {
        ASSERT_EQ(val, ++i);
    }
}

TEST(TestNaiveVector, CopyConstructorTest) {
    naive::vector<int> v{1, 2, 3};
    auto other = v;
    ASSERT_EQ(other.size(), v.size());
    ASSERT_EQ(other.capacity(), v.capacity());
    for (size_t i = 0; i < other.size(); ++i) {
        ASSERT_EQ(v[i], other[i]);
    }
}

TEST(TestNaiveVector, CopyAssignmentTest) {
    naive::vector<int> v{1, 2, 3};
    naive::vector<int> other{1, 2, 3, 4, 5};
    v = other;
    ASSERT_EQ(v.size(), other.size());
    ASSERT_EQ(v.capacity(), other.capacity());
    for (size_t i = 0; i < other.size(); ++i) {
        ASSERT_EQ(v[i], other[i]);
    }
}

TEST(TestNaiveVector, MoveConstructorTest) {
    naive::vector<int> v{1, 2, 3};
    auto sz = v.size(), cap = v.capacity();
    auto other = std::move(v);
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), 0);
    ASSERT_EQ(other.size(), sz);
    ASSERT_EQ(other.capacity(), cap);
    for (size_t i = 0; i < other.size(); ++i) {
        ASSERT_EQ(other[i], i + 1);
    }
}

TEST(TestNaiveVector, MoveAssignmentTest) {
    naive::vector<int> v{1, 2, 3};
    naive::vector<int> other{1, 2, 3, 4, 5};
    auto sz = v.size(), cap = v.capacity();
    other = std::move(v);
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(other.size(), sz);
    ASSERT_EQ(other.capacity(), cap);
    for (size_t i = 0; i < other.size(); ++i) {
        ASSERT_EQ(other[i], i + 1);
    }
}

TEST(TestNaiveVector, SubscriptOperatorTest) {
    naive::vector<int> v{1, 2, 3};
    const naive::vector<int> cv{1, 2, 3, 4, 5};
    ASSERT_EQ(v[2], 3);
    ASSERT_EQ(cv[1], 2);
    decltype(v)::value_type val = 812;
    v[2] = val;
    ASSERT_EQ(v[2], val);
}

TEST(TestNaiveVector, DataMethodTest) {
    naive::vector<int> v{1, 2, 3};
    const naive::vector<int> cv{1, 2, 3, 4, 5};
    auto d = v.data();
    auto cd = cv.data();
    ASSERT_EQ(*(d + 2), 3);
    ASSERT_EQ(*(cd + 1), 2);
    decltype(v)::value_type val = 812;
    *(d + 2) = val;
    ASSERT_EQ(v[2], val);
    ASSERT_EQ(*(d + 2), val);
}

TEST(TestNaiveVector, AtMethodTest) {
    naive::vector<int> v{1, 2, 3, 4, 5};
    const naive::vector<int> cv{1, 2, 3};
    ASSERT_EQ(v.at(0), 1);
    ASSERT_EQ(cv.at(2), 3);
    ASSERT_THROW(v.at(10), std::out_of_range);
    ASSERT_THROW(cv.at(9), std::out_of_range);
    decltype(v)::value_type val = 123;
    v.at(2) = val;
    ASSERT_EQ(v.at(2), val);
}

TEST(TestNaiveVector, FrontMethodTest) {
    naive::vector<int> v{1, 2, 3, 4, 5};
    const naive::vector<int> cv{1, 2, 3};
    ASSERT_EQ(v.front(), 1);
    ASSERT_EQ(cv.front(), 1);
    decltype(v)::value_type val = 319;
    v.front() = val;
    ASSERT_EQ(v.front(), val);
}

TEST(TestNaiveVector, BacktMethodTest) {
    naive::vector<int> v{1, 2, 3, 4, 5};
    const naive::vector<int> cv{1, 2, 3};
    ASSERT_EQ(v.back(), 5);
    ASSERT_EQ(cv.back(), 3);
    decltype(v)::value_type val = 319;
    v.back() = val;
    ASSERT_EQ(v.back(), val);
}

TEST(TestNaiveVector, IteratorsTest) {
    naive::vector<int> v{1, 2, 3, 4, 5};
    const naive::vector<int> cv{1, 2, 3};
    auto val = 0;
    for (auto it = v.begin(), it_end = v.end(); it != it_end; ++it) {
        ASSERT_EQ(*it, ++val);
    }
    val = 0;
    for (auto it = cv.begin(), it_end = cv.end(); it != it_end; ++it) {
        ASSERT_EQ(*it, ++val);
    }
    for (auto it = v.begin(), it_end = v.end(); it != it_end; ++it) {
        auto tmp = *it;
        *it = tmp * tmp;
        ASSERT_EQ(*it, tmp * tmp);
    }
}

TEST(TestNaiveVector, ReverseIteratorsTest) {
    naive::vector<int> v{1, 2, 3, 4, 5};
    const naive::vector<int> cv{1, 2, 3};
    auto back_arr = v.back(), back_carr = cv.back();
    for (auto it = v.rbegin(), it_end = v.rend(); it != it_end; ++it) {
        ASSERT_EQ(*it, back_arr--);
    }
    for (auto it = cv.rbegin(), it_end = cv.rend(); it != it_end; ++it) {
        ASSERT_EQ(*it, back_carr--);
    }
    for (auto it = v.begin(), it_end = v.end(); it != it_end; ++it) {
        auto tmp = *it;
        *it = tmp * tmp;
        ASSERT_EQ(*it, tmp * tmp);
    }
}

TEST(TestNaiveVector, ConstReverseIteratorsTest) {
    naive::vector<int> v{1, 2, 3, 4, 5};
    const naive::vector<int> cv{1, 2, 3};
    auto back_arr = v.back(), back_carr = cv.back();
    for (auto it = v.crbegin(), it_end = v.crend(); it != it_end; ++it) {
        ASSERT_EQ(*it, back_arr--);
    }
    for (auto it = cv.crbegin(), it_end = cv.crend(); it != it_end; ++it) {
        ASSERT_EQ(*it, back_carr--);
    }
}

TEST(TestNaiveVector, SizeandEmptyMethodsTest) {
    naive::vector<int> ev, v{1, 2, 3};
    ASSERT_EQ(ev.size(), 0);
    ASSERT_TRUE(ev.empty());

    ASSERT_EQ(v.size(), 3);
    ASSERT_FALSE(v.empty());
}

TEST(TestNaiveVector, CapacityMethodsTest) {
    naive::vector<std::string> v {"hello", "c++", "world"};
    ASSERT_EQ(v.capacity(), 3);
    ASSERT_EQ(v.size(), 3);
    naive::vector<std::string> empty;
    ASSERT_EQ(empty.capacity(), 0);
    ASSERT_EQ(empty.size(), 0);
}

TEST(TestNaiveVector, ReserveMethodsTest) {
    naive::vector<std::string> v {"hello", "c++", "world"};
    v.reserve(10);
    ASSERT_EQ(v.capacity(), 10);
    ASSERT_EQ(v.size(), 3);
    naive::vector<std::string> empty;
    empty.reserve(20);
    ASSERT_EQ(empty.capacity(), 20);
    ASSERT_EQ(empty.size(), 0);
}

TEST(TestNaiveVector, ShrinkToFitMethodsTest) {
    naive::vector<std::string> v {"hello", "c++", "world"};
    v.reserve(10);
    ASSERT_EQ(v.capacity(), 10);
    ASSERT_EQ(v.size(), 3);
    v.shrink_to_fit();
    ASSERT_EQ(v.capacity(), 3);
    ASSERT_EQ(v.size(), 3);
    naive::vector<std::string> empty;
    empty.reserve(20);
    empty.shrink_to_fit();
    ASSERT_EQ(empty.capacity(), 0);
    ASSERT_EQ(empty.size(), 0);
}

TEST(TestNaiveVector, ClearMethodsTest) {
    naive::vector<std::string> v {"hello", "c++", "world"};
    v.clear();
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), 3);
}

TEST(TestNaiveVector, EraseMethodsTest) {
    naive::vector<std::string> v {"hello", "c++", "world"};
    v.erase(v.begin() + 1);
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v.capacity(), 3);
    ASSERT_EQ(v[0], "hello");
    ASSERT_EQ(v[1], "world");
}

TEST(TestNaiveVector, InsertMethodsTest) {
    naive::vector<std::string> v {"hello", "c++", "world"};
    v.insert(v.begin() + 1, "rust");
    print_vec(v);
    ASSERT_EQ(v.size(), 4);
    ASSERT_EQ(v.capacity(), 6);
    ASSERT_EQ(v[0], "hello");
    ASSERT_EQ(v[1], "rust");
    ASSERT_EQ(v[2], "c++");
    ASSERT_EQ(v[3], "world");
}

TEST(TestNaiveVector, PushBackMethodsTest) {
    naive::vector<std::string> v {"hello", "c++", "world"};
    v.push_back("rust");
    ASSERT_EQ(v.size(), 4);
    ASSERT_EQ(v.capacity(), 6);
    ASSERT_EQ(v[0], "hello");
    ASSERT_EQ(v[1], "c++");
    ASSERT_EQ(v[2], "world");
    ASSERT_EQ(v[3], "rust");
}

TEST(TestNaiveVector, EmplaceBackMethodsTest) {
    naive::vector<std::string> v {"hello", "c++", "world"};
    v.emplace_back();
    ASSERT_EQ(v.size(), 4);
    ASSERT_EQ(v.capacity(), 6);
    ASSERT_EQ(v[0], "hello");
    ASSERT_EQ(v[1], "c++");
    ASSERT_EQ(v[2], "world");
    ASSERT_EQ(v[3], "");
}

TEST(TestNaiveVector, ResizeMethodsTest) {
    naive::vector<std::string> v {"hello", "c++", "world"};
    v.resize(5);
    ASSERT_EQ(v.size(), 5);
    ASSERT_EQ(v.capacity(), 5);
    ASSERT_EQ(v[0], "hello");
    ASSERT_EQ(v[1], "c++");
    ASSERT_EQ(v[2], "world");
    ASSERT_EQ(v[3], "");
    ASSERT_EQ(v[4], "");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}