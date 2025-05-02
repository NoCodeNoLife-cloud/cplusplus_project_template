#include <memory>
#include <string>
#include <entity/base_type/Object.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(ObjectTest, ConstructorTest) {
    framework::entity::base_type::Object obj;
    EXPECT_TRUE(true);
  }

  TEST(ObjectTest, CloneReturnsNonNullPointer) {
    const framework::entity::base_type::Object obj;
    const auto clone = obj.clone();
    EXPECT_NE(clone, nullptr);
  }

  TEST(ObjectTest, CloneCreatesDifferentInstance) {
    framework::entity::base_type::Object obj;
    const auto clone = obj.clone();
    EXPECT_NE(&obj, clone.get());
  }

  TEST(ObjectTest, ClonePreservesType) {
    framework::entity::base_type::Object obj;
    const auto clone = obj.clone();
    EXPECT_EQ(typeid(*clone), typeid(obj));
  }

  TEST(ObjectTest, EqualsSameObjectReturnsTrue) {
    const framework::entity::base_type::Object obj;
    EXPECT_TRUE(obj.equals(obj));
  }

  TEST(ObjectTest, EqualsDifferentObjectsReturnFalse) {
    const framework::entity::base_type::Object obj1;
    const framework::entity::base_type::Object obj2;
    EXPECT_FALSE(obj1.equals(obj2));
  }

  TEST(ObjectTest, EqualsDifferentTypeReturnsFalse) {
    framework::entity::base_type::Object obj;

    struct DerivedTest : public framework::entity::base_type::Object {};
    const DerivedTest derived;

    EXPECT_FALSE(obj.equals(derived));
    EXPECT_FALSE(derived.equals(obj));
  }

  TEST(ObjectTest, GetClassReturnsCorrectType) {
    const framework::entity::base_type::Object obj;
    EXPECT_EQ(&obj.getClass(), &typeid(framework::entity::base_type::Object));
  }

  TEST(ObjectTest, HashCodeSameObjectConsistent) {
    const framework::entity::base_type::Object obj;
    const size_t hash = obj.hashCode();
    EXPECT_EQ(obj.hashCode(), hash);
  }

  TEST(ObjectTest, HashCodeDifferentObjectsUnique) {
    const framework::entity::base_type::Object obj1;
    const framework::entity::base_type::Object obj2;
    EXPECT_NE(obj1.hashCode(), obj2.hashCode());
  }

  TEST(ObjectTest, ToStringReturnsNonEmptyString) {
    const framework::entity::base_type::Object obj;
    const std::string str = obj.toString();
    EXPECT_FALSE(str.empty());
  }
} // namespace gtest_case
