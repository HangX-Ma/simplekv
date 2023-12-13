#include "simplekv.h"
#include <gtest/gtest.h>

simple_kv::SimpleKV db;

TEST(BasicTest, BasicFunctionTest)
{
    db.add<int>("age", 99);
    EXPECT_EQ(db.get("age")->value<int>(), 99);

    db.put<int>("age", -1);
    EXPECT_EQ(db.get("age")->value<int>(), -1);
}

TEST(BasicTest, DifferentTypesTest)
{
    db.add<float>("float", 9.99);
    EXPECT_FLOAT_EQ(db.get("float")->value<float>(), 9.99);

    db.add<double>("double", 6.66);
    EXPECT_DOUBLE_EQ(db.get("double")->value<double>(), 6.66);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}