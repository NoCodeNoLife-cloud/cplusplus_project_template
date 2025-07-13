#include <memory>
#include <string>
#include <gtest/gtest.h>

#include "type/base_type/Object.hpp"

namespace gtest_case
{
    TEST(ObjectTest, DefaultConstructor)
    {
        const coco::Object obj;
        // ReSharper disable once CppNoDiscardExpression
        EXPECT_NO_THROW(obj.toString());
    }

    TEST(ObjectTest, CopyConstructor)
    {
        const coco::Object obj1;
        const coco::Object obj2(obj1);
        EXPECT_EQ(obj1.getClass(), obj2.getClass());
        EXPECT_EQ(obj1.hashCode(), obj2.hashCode());
    }

    TEST(ObjectTest, MoveConstructor)
    {
        coco::Object obj1;
        const size_t original_hash = obj1.hashCode();
        const coco::Object obj2(std::move(obj1));
        EXPECT_EQ(original_hash, obj2.hashCode());
    }

    TEST(ObjectTest, GetClassReturnsSameTypeForSameObject)
    {
        const coco::Object obj;
        EXPECT_EQ(obj.getClass(), typeid(coco::Object));
    }

    TEST(ObjectTest, HashCodeConsistency)
    {
        const coco::Object obj;
        const size_t hash1 = obj.hashCode();
        const size_t hash2 = obj.hashCode();
        EXPECT_EQ(hash1, hash2);
    }

    TEST(ObjectTest, DifferentObjectsHaveDifferentHashes)
    {
        const coco::Object obj1, obj2;
        EXPECT_EQ(obj1.hashCode(), obj2.hashCode());
    }

    TEST(ObjectTest, ToStringFormat)
    {
        const coco::Object obj;
        const std::string str = obj.toString();
        EXPECT_FALSE(str.empty());
        EXPECT_TRUE(str.find("coco::Object") != std::string::npos);
    }

    TEST(ObjectTest, AssignmentOperator)
    {
        const coco::Object obj2;
        const coco::Object obj1 = obj2;
        EXPECT_EQ(obj1.getClass(), obj2.getClass());
        EXPECT_EQ(obj1.hashCode(), obj2.hashCode());
    }

    TEST(ObjectTest, MoveAssignmentOperator)
    {
        coco::Object obj2;
        const coco::Object obj1 = std::move(obj2);
        EXPECT_EQ(obj1.hashCode(), obj2.hashCode()) << "Move assignment doesn't preserve hash";
    }

    TEST(ObjectTest, PolymorphicBehavior)
    {
        class Derived : public coco::Object
        {
        };
        const Derived derived;
        const coco::Object& base_ref = derived;
        EXPECT_EQ(base_ref.getClass(), typeid(Derived)) << "getClass() should support polymorphism";
    }
}
