#include <entity/util/ClassUtil.hpp>
#include <gtest/gtest.h>
using namespace framework;

namespace gtest_case {
  struct Dummy {};
  enum TestEnum { VALUE };
  TEST(ClassUtilTest, BasicIntType) {
    constexpr int value = 0;
    EXPECT_EQ(ClassUtil::getTypeId(value), "int const & __ptr64");
  }

  TEST(ClassUtilTest, ConstIntType) {
    constexpr int value = 0;
    EXPECT_EQ(ClassUtil::getTypeId(value), "int const & __ptr64");
  }

  TEST(ClassUtilTest, VolatileIntType) {
    volatile constexpr int value = 0;
    EXPECT_EQ(ClassUtil::getTypeId(value), "int const volatile & __ptr64");
  }

  TEST(ClassUtilTest, ConstVolatileIntType) {
    volatile constexpr int value = 0;
    EXPECT_EQ(ClassUtil::getTypeId(value), "int const volatile & __ptr64");
  }

  TEST(ClassUtilTest, PointerType) {
    int* ptr = nullptr;
    EXPECT_EQ(ClassUtil::getTypeId(ptr), "int * __ptr64 const & __ptr64");
  }

  TEST(ClassUtilTest, ConstPointerType) {
    const int* ptr = nullptr;
    EXPECT_EQ(ClassUtil::getTypeId(ptr), "int const * __ptr64 const & __ptr64");
  }

  TEST(ClassUtilTest, ReferenceType) {
    constexpr int value = 0;
    const int& ref = value;
    EXPECT_EQ(ClassUtil::getTypeId(ref), "int const & __ptr64");
  }

  TEST(ClassUtilTest, ConstReferenceType) {
    constexpr int value = 0;
    const int& ref = value;
    EXPECT_EQ(ClassUtil::getTypeId(ref), "int const & __ptr64");
  }

  TEST(ClassUtilTest, ArrayType) {
    int arr[5];
    EXPECT_EQ(ClassUtil::getTypeId(arr), "int const (& __ptr64)[5]");
  }

  TEST(ClassUtilTest, ClassType) {
    constexpr Dummy obj;
    EXPECT_EQ(ClassUtil::getTypeId(obj), "struct gtest_case::Dummy const & __ptr64");
  }

  TEST(ClassUtilTest, EnumType) {
    constexpr TestEnum val = VALUE;
    EXPECT_EQ(ClassUtil::getTypeId(val), "enum gtest_case::TestEnum const & __ptr64");
  }

  TEST(ClassUtilTest, FunctionPointerType) {
    int (*funcPtr)(int) = nullptr;
    EXPECT_EQ(ClassUtil::getTypeId(funcPtr), "int (__cdecl*const & __ptr64)(int)");
  }

  TEST(ClassUtilTest, TemplateInstanceType) {
    const std::vector<std::list<int>> obj;
    EXPECT_EQ(ClassUtil::getTypeId(obj), "class std::vector<class std::list<int,class std::allocator<int> >,class std::allocator<class std::list<int,class std::allocator<int> > > > const & __ptr64");
  }
}
