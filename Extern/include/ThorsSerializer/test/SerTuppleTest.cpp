#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <algorithm>

namespace TS = ThorsAnvil::Serialize;

TEST(SerTuppleTest, Jsonserialize)
{
    std::tuple<int, double>  data {56, 78.901};

    std::stringstream       stream;
    stream << TS::jsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"([56,78.901])");
}

TEST(SerTuppleTest, JsondeSerialize)
{
    std::stringstream   stream(R"([59,22.801])");
    std::tuple<int, double>  data {56, 78.925};

    stream >> TS::jsonImporter(data, false);
    EXPECT_EQ(59,     std::get<0>(data));
    EXPECT_EQ(22.801, std::get<1>(data));
}

TEST(SerTuppleTest, Bsonserialize)
{
    std::tuple<int, double>  data {56, 78.901};

    std::stringstream       stream;
    stream << TS::bsonExporter(data, false);
    std::string result = stream.str();

    static const char expectedRaw[]
                = "\x17\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x01" "1\x00" "\x8b\x6c\xe7\xfb\xa9\xb9\x53\x40"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(result, expected);
    //EXPECT_EQ(result, R"([56,78.901])");
}

TEST(SerTuppleTest, BsondeSerialize)
{
    //std::stringstream   stream(R"([59,22.801])");
    static const char inputRaw[]
                = "\x17\x00\x00\x00"
                  "\x10" "0\x00"    "\x3B\x00\x00\x00"
                  "\x01" "1\x00"    "\x93\x18\x04\x56\x0e\xcd\x36\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) + 1);
    std::stringstream stream(input);
    std::tuple<int, double>  data {56, 78.925};

    stream >> TS::bsonImporter(data, false);
    EXPECT_EQ(59,     std::get<0>(data));
    EXPECT_EQ(22.801, std::get<1>(data));
}

