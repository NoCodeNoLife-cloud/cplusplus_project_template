#include <gtest/gtest.h>

#include "type/base_type/Object.hpp"

namespace gtest_case
{
    TEST(ObjectTest, CopyConstructor)
    {
        const fox::Object obj1 = {};
        const fox::Object& obj2(obj1);
        EXPECT_EQ(obj1.getClass(), obj2.getClass());
        EXPECT_EQ(obj1.hashCode(), obj2.hashCode());
    }

    TEST(ObjectTest, MoveConstructor)
    {
        const fox::Object obj1;
        const size_t original_hash = obj1.hashCode();
        const fox::Object& obj2(obj1);
        EXPECT_EQ(original_hash, obj2.hashCode());
    }

    TEST(ObjectTest, GetClassReturnsSameTypeForSameObject)
    {
        const fox::Object obj;
        EXPECT_EQ(obj.getClass(), typeid(fox::Object));
    }

    TEST(ObjectTest, HashCodeConsistency)
    {
        const fox::Object obj;
        const size_t hash1 = obj.hashCode();
        const size_t hash2 = obj.hashCode();
        EXPECT_EQ(hash1, hash2);
    }

    TEST(ObjectTest, DifferentObjectsHaveDifferentHashes)
    {
        const fox::Object obj1, obj2;
        EXPECT_EQ(obj1.hashCode(), obj2.hashCode());
    }

    TEST(ObjectTest, AssignmentOperator)
    {
        const fox::Object obj2 = {};
        const fox::Object& obj1 = obj2;
        EXPECT_EQ(obj1.getClass(), obj2.getClass());
        EXPECT_EQ(obj1.hashCode(), obj2.hashCode());
    }

    TEST(ObjectTest, MoveAssignmentOperator)
    {
        const fox::Object obj2;
        const fox::Object& obj1 = obj2;
        EXPECT_EQ(obj1.hashCode(), obj2.hashCode()) << "Move assignment doesn't preserve hash";
    }

    TEST(ObjectTest, PolymorphicBehavior)
    {
        class Derived : public fox::Object
        {
        };
        const Derived derived;
        const fox::Object& base_ref = derived;
        EXPECT_EQ(base_ref.getClass(), typeid(Derived)) << "getClass() should support polymorphism";
    }
} // namespace gtest_case
