#include <gtest/gtest.h>
#include <n_vector.h>
#include <vector>
#include <memory>
#include <log_struct.h>

template<class T>
void print(T t) {
    for (auto i: t) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

auto nil = naive::utils::to<naive::vector<int>::size_type>(0);
auto three = naive::utils::to<naive::vector<int>::size_type>(3);

TEST(TestNaiveVector, DefaultConstructorTest) {
    naive::vector<int> v;
    ASSERT_EQ(v.size(), nil);
    ASSERT_EQ(v.capacity(), nil);
}

TEST(TestNaiveVector, SizeConstructorTest) {
    std::vector<int> v(3);
    ASSERT_EQ(v.size(), three);
    ASSERT_EQ(v.capacity(), three);
}

TEST(TestNaiveVector, SizeAndValConstructorTest) {
    naive::vector<int> v(3, 5);
    ASSERT_EQ(v.size(), three);
    ASSERT_EQ(v.capacity(), three);
    for (auto val: v) {
        ASSERT_EQ(val, 5);
    }
}

TEST(TestNaiveVector, InitListConstructorTest) {
    naive::vector<int> v{1, 2, 3};
    ASSERT_EQ(v.size(), three);
    ASSERT_EQ(v.capacity(), three);
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
    ASSERT_EQ(v.size(), nil);
    ASSERT_EQ(v.capacity(), nil);
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
    ASSERT_EQ(v.size(), nil);
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

TEST(TestNaiveArray, DataMethodTest) {
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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}