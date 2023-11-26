#include <gtest/gtest.h>
#include <n_shared_ptr.h>
#include <log_struct.h>

TEST(TestSharedPtr, DefaultConstructor) {
    naive::shared_ptr<int> sp;
    ASSERT_TRUE(sp.get() == nullptr);
}

TEST(TestSharedPtr, Constructor) {
    naive::shared_ptr<int> sp(new int{5});
    ASSERT_EQ(*sp, 5);
}

TEST(TestSharedPtr, CopyConstructor) {
    naive::shared_ptr<int> sp(new int{5});
    auto other = sp;
    ASSERT_EQ(*sp, 5);
    ASSERT_EQ(*other, 5);
}

TEST(TestSharedPtr, AssignmentOperator) {
    naive::shared_ptr<int> sp(new int{5});
    naive::shared_ptr<int> other(new int{3});
    sp = other;
    ASSERT_EQ(*sp, 3);
    ASSERT_EQ(*other, 3);
}

TEST(TestSharedPtr, MoveConstructor) {
    naive::shared_ptr<int> sp(new int{5});
    auto other = std::move(sp);
    ASSERT_EQ(*other, 5);
}

TEST(TestSharedPtr, MoveAssignmentOperator) {
    naive::shared_ptr<int> sp(new int{5});
    naive::shared_ptr<int> other(new int{3});
    sp = std::move(other);
    ASSERT_EQ(*sp, 3);
}

// modifiers

TEST(TestSharedPtr, ResetMethod) {
    naive::shared_ptr<int> sp(new int{5}), other(new int{3});
    sp.reset();
    other.reset(new int{10});
    ASSERT_EQ(*other, 10);
}

TEST(TestSharedPtr, SwapMethod) {
    naive::shared_ptr<int> sp(new int{5}), other(new int{3});
    sp.swap(other);
    ASSERT_EQ(*sp, 3);
    ASSERT_EQ(*other, 5);
}

// observers

TEST(TestSharedPtr, GetMethod) {
    naive::shared_ptr<int> sp(new int{5});
    ASSERT_EQ(*sp.get(), 5);
}

TEST(TestSharedPtr, DereferenceOperator) {
    struct S {
        int foo() { return 42; }

        std::string bar() { return "hello"; }

        int x = 5;
    };
    std::shared_ptr<int> up(new int{5});
    ASSERT_EQ(*up, 5);
    naive::shared_ptr<S> up_s(new S);
    ASSERT_EQ(up_s->foo(), 42);
    ASSERT_EQ(up_s->bar(), "hello");
    ASSERT_EQ((*up_s).x, 5);

}

TEST(A, B) {
    std::shared_ptr<int[]> sp(new int[3]{1, 2, 3});
    for (int i = 0; i < 3; ++i) {
        std::cout << sp[i] << '\n';
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}