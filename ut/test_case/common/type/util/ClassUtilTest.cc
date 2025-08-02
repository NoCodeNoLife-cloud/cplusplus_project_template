#include <gtest/gtest.h>

#include "type/util/ClassUtil.hpp"

namespace gtest_case {
struct Dummy {};

enum TestEnum { VALUE };

TEST(ClassUtilTest, BasicIntType) {
  constexpr int value = 0;
  EXPECT_EQ(common::ClassUtil::getTypeId(value), "int");
}

TEST(ClassUtilTest, ConstIntType) {
  constexpr int value = 0;
  EXPECT_EQ(common::ClassUtil::getTypeId(value), "int");
}

TEST(ClassUtilTest, VolatileIntType) {
  volatile constexpr int value = 0;
  EXPECT_EQ(common::ClassUtil::getTypeId(value), "int");
}

TEST(ClassUtilTest, ConstVolatileIntType) {
  volatile constexpr int value = 0;
  EXPECT_EQ(common::ClassUtil::getTypeId(value), "int");
}

TEST(ClassUtilTest, PointerType) {
  int* ptr = nullptr;
  EXPECT_EQ(common::ClassUtil::getTypeId(ptr), "int * __ptr64");
}

TEST(ClassUtilTest, ConstPointerType) {
  const int* ptr = nullptr;
  EXPECT_EQ(common::ClassUtil::getTypeId(ptr), "int const * __ptr64");
}

TEST(ClassUtilTest, ReferenceType) {
  constexpr int value = 0;
  const int& ref = value;
  EXPECT_EQ(common::ClassUtil::getTypeId(ref), "int");
}

TEST(ClassUtilTest, ConstReferenceType) {
  constexpr int value = 0;
  const int& ref = value;
  EXPECT_EQ(common::ClassUtil::getTypeId(ref), "int");
}

TEST(ClassUtilTest, ArrayType) {
  int arr[5];
  EXPECT_EQ(common::ClassUtil::getTypeId(arr), "int [5]");
}

TEST(ClassUtilTest, ClassType) {
  constexpr Dummy obj;
  EXPECT_EQ(common::ClassUtil::getTypeId(obj), "struct gtest_case::Dummy");
}

TEST(ClassUtilTest, EnumType) {
  constexpr TestEnum val = VALUE;
  EXPECT_EQ(common::ClassUtil::getTypeId(val), "enum gtest_case::TestEnum");
}

TEST(ClassUtilTest, FunctionPointerType) {
  int (*funcPtr)(int) = nullptr;
  EXPECT_EQ(common::ClassUtil::getTypeId(funcPtr), "int (__cdecl*)(int)");
}

TEST(ClassUtilTest, TemplateInstanceType) {
  const std::vector<std::list<int>> obj;
  EXPECT_EQ(common::ClassUtil::getTypeId(obj),
            "class std::vector<class std::list<int,class std::allocator<int> >,class "
            "std::allocator<class std::list<int,class std::allocator<int> > > >");
}
}  // namespace gtest_case
