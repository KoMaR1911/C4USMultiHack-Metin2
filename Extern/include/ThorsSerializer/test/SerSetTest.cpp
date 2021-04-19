#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <algorithm>

namespace TS = ThorsAnvil::Serialize;

TEST(SerSetTest, Jsonserialize)
{
    std::set<int>  data{34,24,8,11,2};

    std::stringstream       stream;
    stream << TS::jsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"([2,8,11,24,34])");
}

TEST(SerSetTest, JsonbeSerialize)
{
    std::set<int>  data;

    std::stringstream       stream(R"([5,6,8,101,123])");
    stream >> TS::jsonImporter(data, false);

    EXPECT_TRUE(data.find(5) != data.end());
    EXPECT_TRUE(data.find(6) != data.end());
    EXPECT_TRUE(data.find(8) != data.end());
    EXPECT_TRUE(data.find(101) != data.end());
    EXPECT_TRUE(data.find(123) != data.end());
}

TEST(SerSetTest, Bsonserialize)
{
    std::set<int>  data{34,24,8,11,2};

    std::stringstream       stream;
    stream << TS::bsonExporter(data, false);
    std::string result = stream.str();

    static const char expectedRaw[]
                = "\x28\x00\x00\x00"
                  "\x10" "0\x00" "\x02\x00\x00\x00"
                  "\x10" "1\x00" "\x08\x00\x00\x00"
                  "\x10" "2\x00" "\x0B\x00\x00\x00"
                  "\x10" "3\x00" "\x18\x00\x00\x00"
                  "\x10" "4\x00" "\x22\x00\x00\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(result, expected);
    //EXPECT_EQ(result, R"([2,8,11,24,34])");
}

TEST(SerSetTest, BsonbeSerialize)
{
    std::set<int>  data;

    //std::stringstream       stream(R"([5,6,8,101,123])");
    static const char inputRaw[]
                = "\x28\x00\x00\x00"
                  "\x10" "0\x00" "\x05\x00\x00\x00"
                  "\x10" "1\x00" "\x06\x00\x00\x00"
                  "\x10" "2\x00" "\x08\x00\x00\x00"
                  "\x10" "3\x00" "\x65\x00\x00\x00"
                  "\x10" "4\x00" "\x7B\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream stream(input);
    stream >> TS::bsonImporter(data, false);

    EXPECT_TRUE(data.find(5) != data.end());
    EXPECT_TRUE(data.find(6) != data.end());
    EXPECT_TRUE(data.find(8) != data.end());
    EXPECT_TRUE(data.find(101) != data.end());
    EXPECT_TRUE(data.find(123) != data.end());
}

