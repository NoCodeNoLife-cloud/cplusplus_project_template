#include <memory>
#include <string>
#include <entity/base_type/Object.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(ObjectTest, ConstructorTest) {
    common::Object obj;
    EXPECT_TRUE(true);
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
}
