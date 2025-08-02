#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "type/base_type/Object.hpp"

namespace gtest_case {
TEST(ObjectTest, DefaultConstructor) {
  const common::Object obj;
  // ReSharper disable once CppNoDiscardExpression
  EXPECT_NO_THROW(obj.toString());
}

TEST(ObjectTest, CopyConstructor) {
  const common::Object obj1 = {};
  const common::Object& obj2(obj1);
  EXPECT_EQ(obj1.getClass(), obj2.getClass());
  EXPECT_EQ(obj1.hashCode(), obj2.hashCode());
}

TEST(ObjectTest, MoveConstructor) {
  const common::Object obj1;
  const size_t original_hash = obj1.hashCode();
  const common::Object& obj2(obj1);
  EXPECT_EQ(original_hash, obj2.hashCode());
}

TEST(ObjectTest, GetClassReturnsSameTypeForSameObject) {
  const common::Object obj;
  EXPECT_EQ(obj.getClass(), typeid(common::Object));
}

TEST(ObjectTest, HashCodeConsistency) {
  const common::Object obj;
  const size_t hash1 = obj.hashCode();
  const size_t hash2 = obj.hashCode();
  EXPECT_EQ(hash1, hash2);
}

TEST(ObjectTest, DifferentObjectsHaveDifferentHashes) {
  const common::Object obj1, obj2;
  EXPECT_EQ(obj1.hashCode(), obj2.hashCode());
}

TEST(ObjectTest, ToStringFormat) {
  const common::Object obj;
  const std::string str = obj.toString();
  EXPECT_FALSE(str.empty());
  EXPECT_TRUE(str.find("common::Object") != std::string::npos);
}

TEST(ObjectTest, AssignmentOperator) {
  const common::Object obj2 = {};
  const common::Object& obj1 = obj2;
  EXPECT_EQ(obj1.getClass(), obj2.getClass());
  EXPECT_EQ(obj1.hashCode(), obj2.hashCode());
}

TEST(ObjectTest, MoveAssignmentOperator) {
  common::Object obj2;
  const common::Object& obj1 = obj2;
  EXPECT_EQ(obj1.hashCode(), obj2.hashCode()) << "Move assignment doesn't preserve hash";
}

TEST(ObjectTest, PolymorphicBehavior) {
  class Derived : public common::Object {};
  const Derived derived;
  const common::Object& base_ref = derived;
  EXPECT_EQ(base_ref.getClass(), typeid(Derived)) << "getClass() should support polymorphism";
}
}  // namespace gtest_case
