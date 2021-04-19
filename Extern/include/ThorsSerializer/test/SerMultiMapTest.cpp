#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <algorithm>

namespace TS = ThorsAnvil::Serialize;

TEST(SerMultiMapTest, Jsonserialize)
{
    std::multimap<int, double>  data;
    data.insert(std::make_pair(56, 78.901));
    data.insert(std::make_pair(56, 901));

    std::stringstream       stream;
    stream << TS::jsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"([{"first":56,"second":78.901},{"first":56,"second":901}])");
}

TEST(SerMultiMapTest, JsondeSerialize)
{
    std::multimap<int, double>  data;

    std::stringstream       stream(R"([{"first":64,"second":12}, {"first":118,"second":14}, {"first":118,"second": 112}])");
    stream >> TS::jsonImporter(data, false);

    EXPECT_TRUE(data.find(64) != data.end());
    EXPECT_TRUE(data.find(118) != data.end());
    EXPECT_EQ(data.count(118), 2);
}

TEST(SerMultiMapTest, JsonserializeStringKey)
{
    std::multimap<std::string, double>  data;
    data.insert(std::make_pair("AStringKey", 78.902));
    data.insert(std::make_pair("TestValue",  22.903));
    data.insert(std::make_pair("TestValue",  903));

    std::stringstream       stream;
    stream << TS::jsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"({"AStringKey":78.902,"TestValue":22.903,"TestValue":903})");
}

TEST(SerMultiMapTest, JsondeSerializeStringKey)
{
    std::multimap<std::string, bool>  data;

    std::stringstream       stream(R"({"OneFileDay":true, "TheLastStand":false, "OfMiceAndMen":true, "1":true, "1":false})");
    stream >> TS::jsonImporter(data, false);

    EXPECT_TRUE(data.find("OneFileDay") != data.end());
    EXPECT_TRUE(data.find("TheLastStand") != data.end());
    EXPECT_TRUE(data.find("OfMiceAndMen") != data.end());
    EXPECT_TRUE(data.find("1") != data.end());
    EXPECT_EQ(data.count("1"), 2);
}

TEST(SerMultiMapTest, Bsonserialize)
{
    std::multimap<int, double>  data;
    data.insert(std::make_pair(56, 78.901));
    data.insert(std::make_pair(56, 901));

    std::stringstream       stream;
    stream << TS::bsonExporter(data, false);
    std::string result = stream.str();

    static const char expectedRaw[]
                = "\x4b\x00\x00\x00"
                  "\x03" "0\x00"
                        "\x20\x00\x00\x00"
                            "\x10" "first\x00"  "\x38\x00\x00\x00"
                            "\x01" "second\x00" "\x8b\x6c\xe7\xfb\xa9\xb9\x53\x40"
                        "\x00"
                  "\x03" "1\x00"
                        "\x20\x00\x00\x00"
                            "\x10" "first\x00"  "\x38\x00\x00\x00"
                            "\x01" "second\x00" "\x00\x00\x00\x00\x00\x28\x8c\x40"
                        "\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(result, expected);
    //EXPECT_EQ(result, R"([{"first":56,"second":78.901},{"first":56,"second":901}])");
}

TEST(SerMultiMapTest, BsondeSerialize)
{
    std::multimap<int, double>  data;

    //std::stringstream       stream(R"([{"first":64,"second":12}, {"first":118,"second":14}, {"first":118,"second": 112}])");
    static const char inputRaw[]
                = "\x6E\x00\x00\x00"
                  "\x03" "0\x00"
                        "\x20\x00\x00\x00"
                            "\x10" "first\x00"  "\x40\x00\x00\x00"
                            "\x01" "second\x00" "\x00\x00\x00\x00\x00\x00\x28\x40"
                        "\x00"
                  "\x03" "1\x00"
                        "\x20\x00\x00\x00"
                            "\x10" "first\x00"  "\x76\x00\x00\x00"
                            "\x01" "second\x00" "\x00\x00\x00\x00\x00\x00\x2C\x40"
                        "\x00"
                  "\x03" "2\x00"
                        "\x20\x00\x00\x00"
                            "\x10" "first\x00"  "\x76\x00\x00\x00"
                            "\x01" "second\x00" "\x00\x00\x00\x00\x00\x00\x5C\x40"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream stream(input);
    stream >> TS::bsonImporter(data, false);

    EXPECT_TRUE(data.find(64) != data.end());
    EXPECT_TRUE(data.find(118) != data.end());
    EXPECT_EQ(data.count(118), 2);
}

TEST(SerMultiMapTest, BsonserializeStringKey)
{
    std::multimap<std::string, double>  data;
    data.insert(std::make_pair("AStringKey", 78.902));
    data.insert(std::make_pair("TestValue",  22.903));
    data.insert(std::make_pair("TestValue",  903));

    std::stringstream       stream;
    stream << TS::bsonExporter(data, false);
    std::string result = stream.str();

    static const char expectedRaw[]
                = "\x3F\x00\x00\x00"
                  "\x01" "AStringKey\x00" "\x7d\x3f\x35\x5e\xba\xb9\x53\x40"
                  "\x01" "TestValue\x00"  "\xba\x49\x0c\x02\x2b\xe7\x36\x40"
                  "\x01" "TestValue\x00"  "\x00\x00\x00\x00\x00\x38\x8c\x40"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(result, expected);
    //EXPECT_EQ(result, R"({"AStringKey":78.902,"TestValue":22.903,"TestValue":903})");
}

TEST(SerMultiMapTest, BsondeSerializeStringKey)
{
    std::multimap<std::string, bool>  data;

    //std::stringstream       stream(R"({"OneFileDay":true, "TheLastStand":false, "OfMiceAndMen":true, "1":true, "1":false})");
    static const char inputRaw[]
                = "\x38\x00\x00\x00"
                  "\x08" "OneFileDay\x00"   "\x01"
                  "\x08" "TheLastStand\x00" "\x00"
                  "\x08" "OfMiceAndMen\x00" "\x01"
                  "\x08" "1\x00"            "\x01"
                  "\x08" "1\x00"            "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream stream(input);
    stream >> TS::bsonImporter(data, false);

    EXPECT_TRUE(data.find("OneFileDay") != data.end());
    EXPECT_TRUE(data.find("TheLastStand") != data.end());
    EXPECT_TRUE(data.find("OfMiceAndMen") != data.end());
    EXPECT_TRUE(data.find("1") != data.end());
    EXPECT_EQ(data.count("1"), 2);
}

