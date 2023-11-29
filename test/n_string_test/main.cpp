#include <gtest/gtest.h>
#include <n_string.h>
#include <string>
#include <vector>

TEST(TestNaiveString, DefaultConstructor) {
    naive::string s;
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.capacity(), 8);
    ASSERT_EQ(std::strcmp(s.c_str(), ""), 0);
}

TEST(TestNaiveString, CountAndCharConstructor) {
    naive::string s(3, 'a');
    ASSERT_EQ(s.size(), 3);
    ASSERT_EQ(s.capacity(), 8);
    ASSERT_EQ(std::strcmp(s.c_str(), "aaa"), 0);
}

TEST(TestNaiveString, CstringAndCountConstructor) {
    naive::string s("hello world", 7);
    ASSERT_EQ(s.size(), 7);
    ASSERT_EQ(s.capacity(), 8);
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
    ASSERT_EQ(s.capacity(), 8);
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
    ASSERT_EQ(other.capacity(), 8);
    ASSERT_EQ(std::strcmp(other.c_str(), "world"), 0);
    ASSERT_EQ(s.size(), other.size());
    ASSERT_EQ(s.capacity(), other.capacity());
    ASSERT_EQ(std::strcmp(s.c_str(), other.c_str()), 0);
}

TEST(TestNaiveString, MoveConstructor) {
    naive::string s("hello");
    auto other = std::move(s);
    ASSERT_EQ(other.size(), 5);
    ASSERT_EQ(other.capacity(), 8);
    ASSERT_EQ(std::strcmp(other.c_str(), "hello"), 0);
}

TEST(TestNaiveString, MoveAssignmentOperator) {
    naive::string s("hello");
    naive::string other("world");
    s = std::move(other);
    ASSERT_EQ(s.size(), 5);
    ASSERT_EQ(s.capacity(), 8);
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

}

TEST(A, B) {
    std::string s;
    s.reserve(100);
    s.shrink_to_fit();
    std::cout << s.capacity() << '\n';
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
