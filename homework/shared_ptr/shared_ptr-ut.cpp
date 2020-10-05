#include "gtest/gtest.h"
#include "shared_ptr.hpp"
#include "NullPtrException.h"
#include <vector>

struct SharedPtrTest : public testing::Test{
    shared_ptr<int> testPtr_1{new int(5)};
};

TEST_F(SharedPtrTest, ConstructorShouldAssign5AndDereferenceOperatorShouldReturnIt){
    ASSERT_EQ(*testPtr_1, 5);
}

TEST_F(SharedPtrTest, SharedRefsShouldBe1AtTheStartPoint){
    ASSERT_EQ(testPtr_1.useCount(), 1);
}

TEST_F(SharedPtrTest, CopyConstructorShouldAssign5ToNewSharedPtrAndRefsAmountShouldBeEqual){
    shared_ptr<int> testPtr_2(testPtr_1);

    ASSERT_EQ(*testPtr_2, 5);
    ASSERT_EQ(testPtr_1.useCount(), 2);
    ASSERT_EQ(testPtr_1.useCount(), testPtr_2.useCount());
}

TEST_F(SharedPtrTest, AfterReturningFromPreviousTestRefsAmountShouldDecrement){
    ASSERT_EQ(testPtr_1.useCount(), 1);
}

TEST_F(SharedPtrTest, AssignmentOperatorShouldAssign5ToNewPtrUsingAnotherPtr){
    shared_ptr<int> testPtr_3;
    testPtr_3 = testPtr_1;

    ASSERT_EQ(*testPtr_3, 5);
    ASSERT_EQ(testPtr_3.useCount(), 2);
}

TEST_F(SharedPtrTest, ShouldThrowExceptionWhileTryingToDereferenceNullptr){
    shared_ptr<int> testPtr_4;

    EXPECT_THROW(*testPtr_4, NullPtrException);
}

TEST_F(SharedPtrTest, MoveAssignmentOperatorShouldAssign10ToPtr){
    testPtr_1 = new int(10);

    ASSERT_EQ(*testPtr_1, 10);
}

TEST_F(SharedPtrTest, AfterMovingRefsAmountShouldBe0){
    shared_ptr<int> sharedTmp_1{new int(10)};
    shared_ptr<int> sharedTmp_2 = std::move(sharedTmp_1);

    ASSERT_EQ(sharedTmp_1.useCount(), 0);
    ASSERT_EQ(sharedTmp_2.useCount(), 1);
}

TEST_F(SharedPtrTest, AfterMovingRefsAfmountShouldBe0){
    std::vector<shared_ptr<int>> vecOfSharedPtr;
    for(size_t i = 0; i < 10; i++){
        vecOfSharedPtr.push_back(shared_ptr<int>(testPtr_1));
    }

    ASSERT_EQ(testPtr_1.useCount(), 11);
}

TEST_F(SharedPtrTest, ShouldResetPtr){
    testPtr_1.reset();

    ASSERT_EQ(testPtr_1.get(), nullptr);

    int* rawPtr = new int{10};

    testPtr_1.reset(rawPtr);

    ASSERT_EQ(testPtr_1.get(), rawPtr);
    ASSERT_EQ(*testPtr_1, *rawPtr);
}