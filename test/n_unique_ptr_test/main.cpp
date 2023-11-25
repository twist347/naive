#include <gtest/gtest.h>
#include <n_unique_ptr.h>
#include <memory>
#include <log_struct.h>

TEST(TestUniquePtr, TraitsAndSize) {
    using t = const naive::unique_ptr<int> &;
    using t_arr = naive::unique_ptr<int[]>;
    static_assert(sizeof(t) == sizeof(int *));
    static_assert(sizeof(t_arr) == sizeof(int *));
    static_assert(std::is_same_v<std::remove_cvref_t<t>::element_type, int>);
    static_assert(std::is_same_v<std::remove_cvref_t<t>::pointer, int *>);
    ASSERT_TRUE(1);
}

TEST(TestUniquePtr, DefaultConstructor) {
    naive::unique_ptr<int> up;
    ASSERT_EQ(up.get(), nullptr);
}

TEST(TestUniquePtr, Constructor) {
    naive::unique_ptr<int> up(new int{5});
    ASSERT_EQ(*up, 5);
}

TEST(TestUniquePtr, ConstructorArray) {
    naive::unique_ptr<int[]> up(new int[3]{1, 2, 3});
    ASSERT_EQ(up[0], 1);
    ASSERT_EQ(up[1], 2);
    ASSERT_EQ(up[2], 3);
}

TEST(TestUniquePtr, ConstructorCustomDeleter) {
    auto del = [](int *ptr) { delete ptr; };
    naive::unique_ptr<int, decltype(del)> up(new int{4}, del);
    ASSERT_EQ(*up, 4);
}

TEST(TestUniquePtr, ConstructorCustomDeleterArray) {
    auto del = [](int *ptr) { delete[] ptr; };
    naive::unique_ptr<int[], decltype(del)> up(new int[3]{1, 2, 3}, del);
    std::cout << sizeof(up) << '\n';
    ASSERT_EQ(up[0], 1);
    ASSERT_EQ(up[1], 2);
    ASSERT_EQ(up[2], 3);
}

TEST(TestUniquePtr, MoveSemantics) {
    naive::unique_ptr<int> up(new int{5});
    auto m_up = std::move(up);
    ASSERT_EQ(*m_up, 5);
    naive::unique_ptr<int> other_up(new int{3});
    m_up = std::move(other_up);
    ASSERT_EQ(*m_up, 3);
}

TEST(TestUniquePtr, MoveSemanticsArray) {
    naive::unique_ptr<int[]> up(new int[3]{1, 2, 3});
    auto m_up = std::move(up);
    ASSERT_EQ(m_up[0], 1);
    ASSERT_EQ(m_up[1], 2);
    ASSERT_EQ(m_up[2], 3);
    naive::unique_ptr<int[]> other_up(new int[2]{5, 10});
    m_up = std::move(other_up);
    ASSERT_EQ(m_up[0], 5);
    ASSERT_EQ(m_up[1], 10);
}

TEST(TestUniquePtr, DereferenceOperator) {
    struct S {
        int foo() { return 42; }

        std::string bar() { return "hello"; }
    };

    naive::unique_ptr<int> up(new int{5});
    ASSERT_EQ(*up, 5);
    naive::unique_ptr<S> up_s(new S);
    ASSERT_EQ(up_s->foo(), 42);
    ASSERT_EQ(up_s->bar(), "hello");
}

TEST(TestUniquePtr, SubscriptOperator) {
    naive::unique_ptr<int[]> up(new int[3]{3, 5, 8});
    ASSERT_EQ(up[0], 3);
    ASSERT_EQ(up[1], 5);
    ASSERT_EQ(up[2], 8);
}

TEST(TestUniquePtr, ReleaseMethod) {
    naive::unique_ptr<int> up(new int{5});
    auto ptr = up.release();
    ASSERT_EQ(*ptr, 5);
    delete ptr;
}

TEST(TestUniquePtr, ReleaseMethodArray) {
    naive::unique_ptr<int[]> up(new int[3]{1, 2, 3});
    auto ptr = up.release();
    ASSERT_EQ(ptr[0], 1);
    ASSERT_EQ(ptr[1], 2);
    ASSERT_EQ(ptr[2], 3);
    delete[] ptr;
}

TEST(TestUniquePtr, ResetMethod) {
    naive::unique_ptr<int> up(new int{3});
    up.reset(new int{5});
    ASSERT_EQ(*up, 5);
}

TEST(TestUniquePtr, SwapMethodArray) {
    naive::unique_ptr<int[]> up(new int[3]{1, 2, 3}), other(new int[2]{5, 10});
    up.swap(other);
    ASSERT_EQ(up[0], 5);
    ASSERT_EQ(up[1], 10);
    ASSERT_EQ(other[0], 1);
    ASSERT_EQ(other[1], 2);
    ASSERT_EQ(other[2], 3);
}

TEST(TestUniquePtr, SwapMethod) {
    naive::unique_ptr<int> up(new int{5}), other(new int{3});
    up.swap(other);
    ASSERT_EQ(*up, 3);
    ASSERT_EQ(*other, 5);
}

// observers

TEST(TestUniquePtr, GetMethod) {
    naive::unique_ptr<int> up(new int{5});
    auto ptr = up.get();
    ASSERT_EQ(*ptr, 5);
}

TEST(TestUniquePtr, GetMethodArray) {
    naive::unique_ptr<int[]> up(new int[3]{1, 2, 3});
    auto ptr = up.get();
    ASSERT_EQ(ptr[0], 1);
    ASSERT_EQ(ptr[1], 2);
    ASSERT_EQ(ptr[2], 3);
}

TEST(TestUniquePtr, GetDeleterMethod) {
    naive::unique_ptr<int> up(new int{5});
    auto del = up.get_deleter();
    int *ptr = new int{3};
    del(ptr);
}

TEST(TestUniquePtr, GetDeleterMethodArray) {
    naive::unique_ptr<int[]> up(new int[3]{1, 2, 3});
    auto del = up.get_deleter();
    int *ptr = new int[3]{1, 2, 3};
    del(ptr);
}

TEST(TestUniquePtr, OperatorBool) {
    naive::unique_ptr<int> up(new int{5});
    bool flag_up = up ? true : false;
    ASSERT_TRUE(flag_up);

    naive::unique_ptr<int> other;
    bool flag_other = up ? true : false;
    ASSERT_TRUE(flag_other);
}

TEST(TestUniquePtr, ThreeWayComparisonOperator) {
    naive::unique_ptr<int[]> up(new int[3]{1, 2, 3});
}

TEST(TestUniquePtr, MakeUniqueFunction) {
    auto up = naive::make_unique<int>(3);
    ASSERT_EQ(*up, 3);
}

TEST(TestUniquePtr, MakeUniqueFunctionArray) {
    auto up = naive::make_unique<int[]>(3);
    for (int i = 0; i < 3; ++i) up[i] = i + 1;
    for (int i = 0; i < 3; ++i) ASSERT_EQ(up[i], i + 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}