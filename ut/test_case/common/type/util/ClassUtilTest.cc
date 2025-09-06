#include <gtest/gtest.h>

#include "type/util/ClassUtil.hpp"

namespace gtest_case {
struct Dummy {};

enum TestEnum { VALUE };

TEST(ClassUtilTest, BasicIntType) {
  constexpr int32_t value = 0;
  EXPECT_EQ(fox::ClassUtil::getTypeId(value), "int32_t");
}

TEST(ClassUtilTest, ConstIntType) {
  constexpr int32_t value = 0;
  EXPECT_EQ(fox::ClassUtil::getTypeId(value), "int32_t");
}

TEST(ClassUtilTest, VolatileIntType) {
  volatile constexpr int32_t value = 0;
  EXPECT_EQ(fox::ClassUtil::getTypeId(value), "int32_t");
}

TEST(ClassUtilTest, ConstVolatileIntType) {
  volatile constexpr int32_t value = 0;
  EXPECT_EQ(fox::ClassUtil::getTypeId(value), "int32_t");
}

TEST(ClassUtilTest, PointerType) {
  int32_t* ptr = nullptr;
  EXPECT_EQ(fox::ClassUtil::getTypeId(ptr), "int32_t * __ptr64");
}

TEST(ClassUtilTest, ConstPointerType) {
  const int32_t* ptr = nullptr;
  EXPECT_EQ(fox::ClassUtil::getTypeId(ptr), "int32_t const * __ptr64");
}

TEST(ClassUtilTest, ReferenceType) {
  constexpr int32_t value = 0;
  const int32_t& ref = value;
  EXPECT_EQ(fox::ClassUtil::getTypeId(ref), "int32_t");
}

TEST(ClassUtilTest, ConstReferenceType) {
  constexpr int32_t value = 0;
  const int32_t& ref = value;
  EXPECT_EQ(fox::ClassUtil::getTypeId(ref), "int32_t");
}

TEST(ClassUtilTest, ArrayType) {
  int32_t arr[5];
  EXPECT_EQ(fox::ClassUtil::getTypeId(arr), "int32_t [5]");
}

TEST(ClassUtilTest, ClassType) {
  constexpr Dummy obj;
  EXPECT_EQ(fox::ClassUtil::getTypeId(obj), "struct gtest_case::Dummy");
}

TEST(ClassUtilTest, EnumType) {
  constexpr TestEnum val = VALUE;
  EXPECT_EQ(fox::ClassUtil::getTypeId(val), "enum gtest_case::TestEnum");
}

TEST(ClassUtilTest, FunctionPointerType) {
  int32_t (*funcPtr)(int32_t) = nullptr;
  EXPECT_EQ(fox::ClassUtil::getTypeId(funcPtr), "int32_t (__cdecl*)(int32_t)");
}

TEST(ClassUtilTest, TemplateInstanceType) {
  const std::vector<std::list<int32_t>> obj;
  EXPECT_EQ(fox::ClassUtil::getTypeId(obj),
            "class std::vector<class std::list<int32_t,class std::allocator<int32_t> >,class "
            "std::allocator<class std::list<int32_t,class std::allocator<int32_t> > > >");
}
}  // namespace gtest_case
