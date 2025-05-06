#include <memory>
#include <string>
#include <entity/base_type/Object.hpp>
#include <gtest/gtest.h>
using framework::Object;

namespace gtest_case {
  TEST(ObjectTest, ConstructorTest) {
    Object obj;
    EXPECT_TRUE(true);
  }

  TEST(ObjectTest, CloneReturnsNonNullPointer) {
    const Object obj;
    const auto clone = obj.clone();
    EXPECT_NE(clone, nullptr);
  }

  TEST(ObjectTest, CloneCreatesDifferentInstance) {
    Object obj;
    const auto clone = obj.clone();
    EXPECT_NE(&obj, clone.get());
  }

  TEST(ObjectTest, ClonePreservesType) {
    Object obj;
    const auto clone = obj.clone();
    EXPECT_EQ(typeid(*clone), typeid(obj));
  }

  TEST(ObjectTest, EqualsSameObjectReturnsTrue) {
    const Object obj;
    EXPECT_TRUE(obj.equals(obj));
  }

  TEST(ObjectTest, EqualsDifferentObjectsReturnFalse) {
    const Object obj1;
    const Object obj2;
    EXPECT_FALSE(obj1.equals(obj2));
  }

  TEST(ObjectTest, EqualsDifferentTypeReturnsFalse) {
    const Object obj;

    struct DerivedTest : Object {};
    const DerivedTest derived;

    EXPECT_FALSE(obj.equals(derived));
    EXPECT_FALSE(derived.equals(obj));
  }

  TEST(ObjectTest, GetClassReturnsCorrectType) {
    const Object obj;
    EXPECT_EQ(&obj.getClass(), &typeid(Object));
  }

  TEST(ObjectTest, HashCodeSameObjectConsistent) {
    const Object obj;
    const size_t hash = obj.hashCode();
    EXPECT_EQ(obj.hashCode(), hash);
  }

  TEST(ObjectTest, HashCodeDifferentObjectsUnique) {
    const Object obj1;
    const Object obj2;
    EXPECT_NE(obj1.hashCode(), obj2.hashCode());
  }

  TEST(ObjectTest, ToStringReturnsNonEmptyString) {
    const Object obj;
    const std::string str = obj.toString();
    EXPECT_FALSE(str.empty());
  }
}
