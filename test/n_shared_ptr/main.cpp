#include <gtest/gtest.h>
#include <n_shared_ptr.h>
#include <log_struct.h>
#include <memory>

TEST(TestSharedPtr, DefaultConstructor) {
    naive::shared_ptr<std::string> sp;
}

TEST(TestSharedPtr, DefaultConstructorArray) {
    naive::shared_ptr<std::string[]> sp;
}

TEST(TestSharedPtr, Constructor) {
    naive::shared_ptr<std::string> sp(new std::string{"hello"});
    ASSERT_EQ(*sp, "hello");
}

TEST(TestSharedPtr, ConstructorArray) {
    naive::shared_ptr<std::string[]> sp(new std::string[3]{"hello", "world", "c++"});
    ASSERT_EQ(sp[1], "world");
}

TEST(TestSharedPtr, CopyConstructor) {
    naive::shared_ptr<std::string> sp(new std::string{"hello"});
    auto other = sp;
    auto other1 = other;
    ASSERT_EQ(*sp, "hello");
    ASSERT_EQ(*other, "hello");
    ASSERT_EQ(*other1, "hello");
}

TEST(TestSharedPtr, CopyConstructorArray) {
    naive::shared_ptr<std::string[]> sp(new std::string[3]{"hello", "world", "c++"});
    auto other = sp;
    auto other1 = other;
    ASSERT_EQ(sp[1], "world");
    ASSERT_EQ(other[0], "hello");
    ASSERT_EQ(other1[2], "c++");
}

TEST(TestSharedPtr, AssignmentOperator) {
    naive::shared_ptr<std::string> sp(new std::string{"hello"});
    naive::shared_ptr<std::string> other(new std::string{"world"});
    sp = other;
    ASSERT_EQ(*sp, "world");
    ASSERT_EQ(*other, "world");
}

TEST(TestSharedPtr, AssignmentOperatorArray) {
    naive::shared_ptr<std::string[]> sp(new std::string[3]{"hello", "world", "c++"});
    naive::shared_ptr<std::string[]> other(new std::string[2]{"java", "python"});
    sp = other;
    ASSERT_EQ(sp[1], "python");
    ASSERT_EQ(other[0], "java");
}

TEST(TestSharedPtr, MoveConstructor) {
    naive::shared_ptr<std::string> sp(new std::string{"hello"});
    auto other = std::move(sp);
    ASSERT_EQ(*other, "hello");
}

TEST(TestSharedPtr, MoveConstructorArray) {
    naive::shared_ptr<std::string[]> sp(new std::string[3]{"hello", "world", "c++"});
    auto other = std::move(sp);
    ASSERT_EQ(other[1], "world");
}

TEST(TestSharedPtr, MoveAssignmentOperator) {
    naive::shared_ptr<std::string> sp(new std::string{"hello"});
    naive::shared_ptr<std::string> other(new std::string{"world"});
    sp = std::move(other);
    ASSERT_EQ(*sp, "world");
}

TEST(TestSharedPtr, MoveAssignmentOperatorArray) {
    naive::shared_ptr<std::string[]> sp(new std::string[3]{"hello", "world", "c++"});
    naive::shared_ptr<std::string[]> other(new std::string[2]{"java", "python"});
    sp = std::move(other);
    ASSERT_EQ(sp[1], "python");
}

// modifiers

TEST(TestSharedPtr, ResetMethod) {
    naive::shared_ptr<std::string> sp(new std::string{"hello"}), other(new std::string{"world"});
    sp.reset();
    other.reset(new std::string{"c++"});
    ASSERT_EQ(*other, "c++");
}

TEST(TestSharedPtr, ResetMethodArray) {
    naive::shared_ptr<std::string[]> sp(new std::string[3]{"hello", "world", "c++"}),
            other(new std::string[2]{"java", "python"});
    sp.reset();
    other.reset(new std::string[2]{"rust", "linux"});
    ASSERT_EQ(other[1], "linux");
}

TEST(TestSharedPtr, SwapMethod) {
    naive::shared_ptr<std::string> sp(new std::string{"hello"}), other(new std::string{"world"});
    sp.swap(other);
    ASSERT_EQ(*sp, "world");
    ASSERT_EQ(*other, "hello");
}

TEST(TestSharedPtr, SwapMethodArray) {
    naive::shared_ptr<std::string[]> sp(new std::string[3]{"hello", "world", "c++"}),
            other(new std::string[2]{"java", "python"});
    sp.swap(other);
    ASSERT_EQ(sp[1], "python");
    ASSERT_EQ(other[2], "c++");
}

// observers

TEST(TestSharedPtr, GetMethod) {
    naive::shared_ptr<std::string> sp(new std::string{"hello"});
    auto ptr = sp.get();
    ASSERT_EQ(ptr, &*(sp));
    ASSERT_EQ(*ptr, "hello");
}

TEST(TestSharedPtr, GetMethodArray) {
    naive::shared_ptr<std::string[]> sp(new std::string[3]{"hello", "world", "c++"});
    auto ptr = sp.get();
    ASSERT_EQ(ptr[1], "world");
}

TEST(TestSharedPtr, DereferenceOperator) {
    struct S {
        int foo() { return 42; }

        std::string bar() { return "hello"; }

        int x = 5;
    };
    naive::shared_ptr<std::string> sp(new std::string{"hello"});
    ASSERT_EQ(*sp, "hello");
    naive::shared_ptr<S> sp_s(new S);
    ASSERT_EQ(sp_s->foo(), 42);
    ASSERT_EQ(sp_s->bar(), "hello");
    ASSERT_EQ((*sp_s).x, 5);
}

TEST(TestSharedPtr, DereferenceOperatorArray) {
    struct S {
        int foo() { return 42; }

        std::string bar() { return "hello"; }

        int x = 5;
    };
    naive::shared_ptr<std::string[]> sp(new std::string[2]{"hello", "world"});
    ASSERT_EQ(sp[0], "hello");
    naive::shared_ptr<S[]> up_s(new S[2]);
    ASSERT_EQ(up_s[0].foo(), 42);
    ASSERT_EQ(up_s[1].bar(), "hello");
    ASSERT_EQ((up_s.get() + 1)->x, 5);
}

TEST(TestSharedPtr, UseCount) {
    naive::shared_ptr<std::string> empty;
    ASSERT_EQ(empty.use_count(), 0);
    naive::shared_ptr<std::string> sp(new std::string{"hello"});
    ASSERT_EQ(sp.use_count(), 1);
    auto copy = sp;
    ASSERT_EQ(sp.use_count(), 2);
    ASSERT_EQ(copy.use_count(), 2);
    sp.reset();
    ASSERT_EQ(copy.use_count(), 1);
}

TEST(TestSharedPtr, UseCountArray) {
    naive::shared_ptr<std::string[]> empty;
    ASSERT_EQ(empty.use_count(), 0);
    naive::shared_ptr<std::string[]> sp(new std::string[3]{"hello", "world", "c++"});
    ASSERT_EQ(sp.use_count(), 1);
    auto copy = sp;
    ASSERT_EQ(sp.use_count(), 2);
    ASSERT_EQ(copy.use_count(), 2);
    copy.reset();
    ASSERT_EQ(sp.use_count(), 1);
}

TEST(TestSharedPtr, OperatorBool) {
    naive::shared_ptr<std::string> sp(new std::string{"hello"});
    bool flag_sp = sp ? true : false;
    ASSERT_TRUE(flag_sp);

    naive::shared_ptr<std::string[]> sp_array(new std::string[2]{"hello", "world"});
    bool flag_sp_array = sp ? true : false;
    ASSERT_TRUE(flag_sp_array);

    naive::shared_ptr<std::string> empty;
    bool flag_empty = empty ? true : false;
    ASSERT_TRUE(!flag_empty);

    naive::shared_ptr<std::string[]> empty_array;
    bool empty_array_flag = empty ? true : false;
    ASSERT_TRUE(!empty_array_flag);
}

TEST(TestSharedPtr, MakeUniqueFunction) {
    auto sp = naive::make_shared<std::string>("hello");
    ASSERT_EQ(*sp, "hello");
}

TEST(TestSharedPtr, MakeUniqueFunctionArray) {
    auto sp = naive::make_shared<std::string[]>(3);
    sp[0] = "hello";
    sp[1] = "world";
    sp[2] = "c++";
    ASSERT_EQ(sp[0], "hello");
    ASSERT_EQ(sp[1], "world");
    ASSERT_EQ(sp[2], "c++");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}