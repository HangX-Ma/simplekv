#include "simplekv.h"
#include <gtest/gtest.h>

struct CustomType
{
    int num1;
    float num2;
    std::string status;
};
using CustomType_t = struct CustomType;

simple_kv::SimpleKV mgr;

TEST(BasicTest, BasicFunctionTest)
{
    mgr.add<int>("age", 99);
    EXPECT_EQ(mgr.get("age")->value<int>(), 99);

    mgr.put<int>("age", -1);
    EXPECT_EQ(mgr.get("age")->value<int>(), -1);
}

TEST(BasicTest, DifferentTypesTest)
{
    mgr.add<float>("float", 9.99);
    EXPECT_FLOAT_EQ(mgr.get("float")->value<float>(), 9.99);

    mgr.add<double>("double", 6.66);
    EXPECT_DOUBLE_EQ(mgr.get("double")->value<double>(), 6.66);

    uint16_t m_array[10] = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27};
    mgr.add("array", m_array);
    for (int i = 0; i < 10; i += 1) {
        EXPECT_EQ(mgr.get("array")->value<uint16_t *>()[i], m_array[i]);
    }

    CustomType_t tom{1, 1.11, "Tom"};
    CustomType_t jerry{2, 2.22, "Jerry"};
    CustomType_t custom_ret;
    mgr.add<CustomType_t>("Tom", tom);
    mgr.add<CustomType_t>("Jerry", jerry);
    custom_ret = mgr.get("Tom")->value<CustomType_t>();
    EXPECT_EQ(custom_ret.num1, tom.num1);
    EXPECT_EQ(custom_ret.num2, tom.num2);
    EXPECT_STREQ(custom_ret.status.c_str(), tom.status.c_str());
    custom_ret = mgr.get("Jerry")->value<CustomType_t>();
    EXPECT_EQ(custom_ret.num1, jerry.num1);
    EXPECT_EQ(custom_ret.num2, jerry.num2);
    EXPECT_STREQ(custom_ret.status.c_str(), jerry.status.c_str());
}

TEST(BasicTest, AddRemoveTest)
{
    // printf("manager has %ld elements\n", mgr.size());
    // printf("manager memory usage: %ld bytes\n", mgr.memoryUsage());
    EXPECT_EQ(mgr.size(), 6);
    EXPECT_EQ(mgr.memoryUsage(), 104);

    mgr.remove("Tom");
    EXPECT_EQ(mgr.size(), 5);
    EXPECT_EQ(mgr.memoryUsage(), 64);

    mgr.clear();
    EXPECT_EQ(mgr.size(), 0);
    EXPECT_EQ(mgr.memoryUsage(), 0);

    EXPECT_FALSE(mgr.exist("Jerry"));
}

TEST(BasicTest, STLContainerTest)
{
    std::string spike = "Spike";
    mgr.add<std::string *>("Spike", &spike);
    EXPECT_STREQ(mgr.get("Spike")->value<std::string *>()->c_str(), "Spike");
    spike = std::string("Spike's Tyke");
    EXPECT_STREQ(mgr.get("Spike")->value<std::string *>()->c_str(), "Spike's Tyke");

    std::vector<int> ducks{1, 2, 3, 4, 5, 6};
    mgr.add<std::vector<int> *>("Ducks", &ducks);
    auto my_ducks = mgr.get("Ducks")->value<std::vector<int> *>();
    for (int i = 0; i < 6; i += 1) {
        EXPECT_EQ(my_ducks->at(i), ducks.at(i));
        EXPECT_EQ((size_t) &my_ducks->at(i), (size_t) &ducks.at(i));
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}