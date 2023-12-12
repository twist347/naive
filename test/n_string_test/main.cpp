#include <gtest/gtest.h>
#include <n_string.h>
#include <string>
#include <vector>

constexpr static std::size_t min_capacity = 8;

TEST(TestNaiveString, DefaultConstructor) {
    naive::string s;
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.capacity(), min_capacity);
    ASSERT_EQ(std::strcmp(s.c_str(), ""), 0);
}

TEST(TestNaiveString, CountAndCharConstructor) {
    naive::string s(3, 'a');
    ASSERT_EQ(s.size(), 3);
    ASSERT_EQ(s.capacity(), min_capacity);
    ASSERT_EQ(std::strcmp(s.c_str(), "aaa"), 0);
}

TEST(TestNaiveString, CstringAndCountConstructor) {
    naive::string s("hello world", 7);
    ASSERT_EQ(s.size(), 7);
    ASSERT_EQ(s.capacity(), min_capacity);
    ASSERT_EQ(std::strcmp(s.c_str(), "hello w"), 0);
}

TEST(TestNaiveString, CstringConstructor) {
    naive::string s("hello world");
    ASSERT_EQ(s.size(), 11);
    ASSERT_EQ(s.capacity(), 12);
    ASSERT_EQ(std::strcmp(s.c_str(), "hello world"), 0);
}

TEST(TestNaiveString, CopyConstructor) {
    naive::string s("hello");
    auto other = s;
    ASSERT_EQ(s.size(), 5);
    ASSERT_EQ(s.capacity(), min_capacity);
    ASSERT_EQ(std::strcmp(s.c_str(), "hello"), 0);
    ASSERT_EQ(other.size(), s.size());
    ASSERT_EQ(other.capacity(), s.capacity());
    ASSERT_EQ(std::strcmp(other.c_str(), s.c_str()), 0);
}

TEST(TestNaiveString, CopyAssignmentOperator) {
    naive::string s("hello");
    naive::string other("world");
    s = other;
    ASSERT_EQ(other.size(), 5);
    ASSERT_EQ(other.capacity(), min_capacity);
    ASSERT_EQ(std::strcmp(other.c_str(), "world"), 0);
    ASSERT_EQ(s.size(), other.size());
    ASSERT_EQ(s.capacity(), other.capacity());
    ASSERT_EQ(std::strcmp(s.c_str(), other.c_str()), 0);
}

TEST(TestNaiveString, MoveConstructor) {
    naive::string s("hello");
    auto other = std::move(s);
    ASSERT_EQ(other.size(), 5);
    ASSERT_EQ(other.capacity(), min_capacity);
    ASSERT_EQ(std::strcmp(other.c_str(), "hello"), 0);
}

TEST(TestNaiveString, MoveAssignmentOperator) {
    naive::string s("hello");
    naive::string other("world");
    s = std::move(other);
    ASSERT_EQ(s.size(), 5);
    ASSERT_EQ(s.capacity(), min_capacity);
    ASSERT_EQ(std::strcmp(s.c_str(), "world"), 0);
}

TEST(TestNaiveString, GetAllocattorMethod) {
    naive::string s("hello");
    auto alloc = s.get_allocator();
    auto ptr = alloc.allocate(3);
    ptr[0] = 'a';
    ptr[1] = 'b';
    ptr[2] = '\0';
    ASSERT_EQ(std::strcmp(ptr, "ab"), 0);
    alloc.deallocate(ptr, 3);
}

// access

TEST(TestNaiveString, SubscriptOperator) {
    naive::string s{"abc"};
    ASSERT_EQ(s[0], 'a');
    ASSERT_EQ(s[1], 'b');
    ASSERT_EQ(s[2], 'c');
    s[1] = 'h';
    ASSERT_EQ(std::strcmp(s.c_str(), "ahc"), 0);
    naive::string cs{"xyz"};
    ASSERT_EQ(cs[0], 'x');
    ASSERT_EQ(cs[1], 'y');
    ASSERT_EQ(cs[2], 'z');
}

TEST(TestNaiveString, DataMethodTest) {
    naive::string s{"hello"};
    auto ptr = s.data();
    ASSERT_EQ(std::strcmp(ptr, "hello"), 0);
    const naive::string cs{"hello"};
    auto cptr = cs.data();
    ASSERT_EQ(std::strcmp(cptr, "hello"), 0);
}

TEST(TestNaiveString, AtMethodTest) {
    naive::string s{"hello"};
    ASSERT_EQ(s.at(1), 'e');
    ASSERT_THROW(s.at(5), std::out_of_range);
    const naive::string cs{"hello"};
    ASSERT_EQ(cs.at(1), 'e');
    ASSERT_THROW(cs.at(5), std::out_of_range);
}

TEST(TestNaiveString, FrontMethodTest) {
    naive::string s{"hello"};
    ASSERT_EQ(s.front(), 'h');
    const naive::string cs{"hello"};
    ASSERT_EQ(cs.front(), 'h');
}

TEST(TestNaiveString, BackMethodTest) {
    naive::string s{"hello"};
    ASSERT_EQ(s.back(), 'o');
    const naive::string cs{"hello"};
    ASSERT_EQ(cs.back(), 'o');
}

TEST(TestNaiveString, CStrMethodTest) {
    naive::string s{"hello"};
    auto cstr = s.c_str();
    ASSERT_EQ(std::strcmp(cstr, "hello"), 0);
    ASSERT_EQ(std::strlen(cstr), 5);
    const naive::string cs{"hello"};
    auto ccstr = cs.c_str();
    ASSERT_EQ(std::strcmp(ccstr, "hello"), 0);
    ASSERT_EQ(std::strlen(ccstr), 5);
}

TEST(TestNaiveString, IteratorTest) {
    naive::string s{"hello"};
    std::string stds = "hello";
    auto idx = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        ASSERT_EQ(*it, stds[idx++]);
    }
    *(s.begin() + 2) = 'x';
    ASSERT_EQ(s, naive::string{"hexlo"});
    const naive::string cs{"hello"};
    idx = 0;
    for (auto it = cs.begin(); it != cs.end(); ++it) {
        ASSERT_EQ(*it, stds[idx++]);
    }
}

TEST(TestNaiveString, ReverseIteratorTest) {
    naive::string s{"hello"};
    std::string stds = "hello";
    auto idx = stds.size() - 1;
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        ASSERT_EQ(*it, stds[idx--]);
    }
    *(s.rbegin() + 1) = 'x';
    ASSERT_EQ(s, naive::string{"helxo"});
    const naive::string cs{"hello"};
    idx = stds.size() - 1;
    for (auto it = cs.rbegin(); it != cs.rend(); ++it) {
        ASSERT_EQ(*it, stds[idx--]);
    }
}

TEST(TestNaiveString, SizeMethodTest) {
    naive::string s{"hello"};
    ASSERT_EQ(s.size(), 5);
    ASSERT_EQ(s.length(), 5);
    naive::string empty;
    ASSERT_EQ(empty.size(), 0);
    ASSERT_EQ(empty.length(), 0);
}


TEST(TestNaiveString, CapacityMethodTest) {
    naive::string s{"hello"};
    ASSERT_EQ(s.capacity(), min_capacity);
    naive::string empty;
    ASSERT_EQ(empty.capacity(), min_capacity);
    naive::string big{"c++ is fantastic!!!"};
    ASSERT_EQ(big.capacity(), big.size() + 1);
}

TEST(TestNaiveString, MaxSizeMethodTest) {
    naive::string s{"hello"};
    ASSERT_EQ(s.max_size(), std::numeric_limits<decltype(s)::size_type>::max());
}

TEST(TestNaiveString, EmptyMethodTest) {
    naive::string s{"hello"};
    ASSERT_FALSE(s.empty());
    naive::string empty;
    ASSERT_TRUE(empty.empty());
}

TEST(TestNaiveString, ReserveMethodTest) {
    naive::string s{"hello"};

    s.reserve(7);
    ASSERT_EQ(s.size(), 5);
    ASSERT_EQ(s, naive::string{"hello"});
    ASSERT_EQ(s.capacity(), min_capacity);

    s.reserve(15);
    ASSERT_EQ(s.size(), 5);
    ASSERT_EQ(s, naive::string{"hello"});
    ASSERT_EQ(s.capacity(), 15);

    s.reserve(10);
    ASSERT_EQ(s.size(), 5);
    ASSERT_EQ(s, naive::string{"hello"});
    ASSERT_EQ(s.capacity(), 15);

    s.reserve(5);
    ASSERT_EQ(s.size(), 5);
    ASSERT_EQ(s, naive::string{"hello"});
    ASSERT_EQ(s.capacity(), 15);

    naive::string empty;
    empty.reserve(5);
    ASSERT_EQ(empty.size(), 0);
    ASSERT_EQ(empty, naive::string{});
    ASSERT_EQ(empty.capacity(), min_capacity);

    empty.reserve(20);
    ASSERT_EQ(empty.size(), 0);
    ASSERT_EQ(empty, naive::string{});
    ASSERT_EQ(empty.capacity(), 20);
}

TEST(TestNaiveString, ShrinkToFitMethodTest) {
    naive::string s{"hello"};

    s.reserve(7);
    s.shrink_to_fit();
    ASSERT_EQ(s.size(), 5);
    ASSERT_EQ(s.capacity(), min_capacity);
    ASSERT_EQ(s, naive::string{"hello"});

    s.reserve(20);
    ASSERT_EQ(s.size(), 5);
    ASSERT_EQ(s.capacity(), 20);
    ASSERT_EQ(s, naive::string{"hello"});

    s.shrink_to_fit();
    ASSERT_EQ(s.size(), 5);
    ASSERT_EQ(s.capacity(), min_capacity);
    ASSERT_EQ(s, naive::string{"hello"});

    naive::string empty;
    empty.reserve(20);
    empty.shrink_to_fit();
    ASSERT_EQ(empty.size(), 0);
    ASSERT_EQ(empty, naive::string{});
    ASSERT_EQ(empty.capacity(), min_capacity);
    empty.reserve(5);
    empty.shrink_to_fit();
    ASSERT_EQ(empty.capacity(), min_capacity);
}

TEST(TestNaiveString, ClearMethodTest) {
    naive::string s{"hello"};
    s.clear();
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.capacity(), min_capacity);
    naive::string empty;
    ASSERT_EQ(empty.size(), 0);
    ASSERT_EQ(empty.capacity(), min_capacity);
}

TEST(TestNaiveString, ResizeMethodTest) {
    naive::string s{"hello"};
    s.resize(3);
    ASSERT_EQ(s.size(), 3);
    ASSERT_EQ(s.capacity(), min_capacity);
    ASSERT_EQ(s, naive::string{"hel"});
    s.resize(20);
    ASSERT_EQ(s.size(), 20);
    ASSERT_EQ(s.capacity(), s.size() + 1);
    s.resize(20);
    ASSERT_EQ(s.size(), 20);
    ASSERT_EQ(s.capacity(), s.size() + 1);
    s.resize(10);
    ASSERT_EQ(std::strcmp(s.c_str(), "hel"), 0);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
