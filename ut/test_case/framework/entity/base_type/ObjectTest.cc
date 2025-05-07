#include <memory>
#include <string>
#include <entity/base_type/Object.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(ObjectTest, ConstructorTest) {
    common::Object obj;
    EXPECT_TRUE(true);
  }

  TEST(ObjectTest, CloneReturnsNonNullPointer) {
    const common::Object obj;
    const auto clone = obj.clone();
    EXPECT_NE(clone, nullptr);
  }

  TEST(ObjectTest, CloneCreatesDifferentInstance) {
    common::Object obj;
    const auto clone = obj.clone();
    EXPECT_NE(&obj, clone.get());
  }

  TEST(ObjectTest, ClonePreservesType) {
    common::Object obj;
    const auto clone = obj.clone();
    EXPECT_EQ(typeid(*clone), typeid(obj));
  }

  TEST(ObjectTest, EqualsSameObjectReturnsTrue) {
    const common::Object obj;
    EXPECT_TRUE(obj.equals(obj));
  }

  TEST(ObjectTest, EqualsDifferentObjectsReturnFalse) {
    const common::Object obj1;
    const common::Object obj2;
    EXPECT_FALSE(obj1.equals(obj2));
  }

  TEST(ObjectTest, EqualsDifferentTypeReturnsFalse) {
    const common::Object obj;

    struct DerivedTest : common::Object {};
    const DerivedTest derived;

    EXPECT_FALSE(obj.equals(derived));
    EXPECT_FALSE(derived.equals(obj));
  }

  TEST(ObjectTest, GetClassReturnsCorrectType) {
    const common::Object obj;
    EXPECT_EQ(&obj.getClass(), &typeid(common::Object));
  }

  TEST(ObjectTest, HashCodeSameObjectConsistent) {
    const common::Object obj;
    const size_t hash = obj.hashCode();
    EXPECT_EQ(obj.hashCode(), hash);
  }

  TEST(ObjectTest, HashCodeDifferentObjectsUnique) {
    const common::Object obj1;
    const common::Object obj2;
    EXPECT_NE(obj1.hashCode(), obj2.hashCode());
  }

  TEST(ObjectTest, ToStringReturnsNonEmptyString) {
    const common::Object obj;
    const std::string str = obj.toString();
    EXPECT_FALSE(str.empty());
  }
}
