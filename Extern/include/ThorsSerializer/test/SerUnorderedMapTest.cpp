#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <algorithm>

namespace TS = ThorsAnvil::Serialize;

TEST(SerUnorderedMapTest, Jsonserialize)
{
    std::unordered_map<int, double>  data;
    data[56]    = 78.901;

    std::stringstream       stream;
    stream << TS::jsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"([{"first":56,"second":78.901}])");
}

TEST(SerUnorderedMapTest, JsondeSerialize)
{
    std::unordered_map<int, double>  data;

    std::stringstream       stream(R"([{"first":64,"second":12}, {"first":118,"second":14}])");
    stream >> TS::jsonImporter(data, false);

    EXPECT_EQ(data[64],  12);
    EXPECT_EQ(data[118], 14);
}

TEST(SerUnorderedMapTest, JsonserializeStringKey)
{
    std::unordered_map<std::string, double>  data;
    data["AStringKey"]      = 78.902;
    data["TestValue"]       = 22.903;

    std::stringstream       stream;
    stream << TS::jsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    bool test = result == R"({"AStringKey":78.902,"TestValue":22.903})"
             || result == R"({"TestValue":22.903,"AStringKey":78.902})";
    EXPECT_TRUE(test);
}

TEST(SerUnorderedMapTest, JsondeSerializeStringKey)
{
    std::unordered_map<std::string, bool>  data;

    std::stringstream       stream(R"({"OneFileDay":true, "TheLastStand":false, "OfMiceAndMen":true})");
    stream >> TS::jsonImporter(data, false);

    EXPECT_EQ(data["OneFileDay"],   true);
    EXPECT_EQ(data["TheLastStand"], false);
    EXPECT_EQ(data["OfMiceAndMen"], true);
}

TEST(SerUnorderedMapTest, Bsonserialize)
{
    std::unordered_map<int, double>  data;
    data[56]    = 78.901;

    std::stringstream       stream;
    stream << TS::bsonExporter(data, false);
    std::string result = stream.str();

    static const char expectedRaw[]
                = "\x28\x00\x00\x00"
                  "\x03" "0\x00"
                        "\x20\x00\x00\x00"
                        "\x10" "first\x00"  "\x38\x00\x00\x00"
                        "\x01" "second\x00" "\x8b\x6c\xe7\xfb\xa9\xb9\x53\x40"
                        "\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(result, expected);
    //EXPECT_EQ(result, R"([{"first":56,"second":78.901}])");
}

TEST(SerUnorderedMapTest, BsondeSerialize)
{
    std::unordered_map<int, double>  data;

    //std::stringstream       stream(R"([{"first":64,"second":12}, {"first":118,"second":14}])");
    static const char inputRaw[]
                = "\x43\x00\x00\x00"
                  "\x03" "0\x00"
                        "\x1C\x00\x00\x00"
                            "\x10" "first\x00"  "\x40\x00\x00\x00"
                            "\x10" "second\x00" "\x0C\x00\x00\x00"
                        "\x00"
                  "\x03" "0\x00"
                        "\x1C\x00\x00\x00"
                            "\x10" "first\x00"  "\x76\x00\x00\x00"
                            "\x10" "second\x00" "\x0E\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream stream(input);
    stream >> TS::bsonImporter(data, false);

    EXPECT_EQ(data[64],  12);
    EXPECT_EQ(data[118], 14);
}

TEST(SerUnorderedMapTest, BsonserializeStringKey)
{
    std::unordered_map<std::string, double>  data;
    data["AStringKey"]      = 78.902;
    data["TestValue"]       = 22.903;

    std::stringstream       stream;
    stream << TS::bsonExporter(data, false);
    std::string result = stream.str();

    static const char expectedRaw1[]
                = "\x2C\x00\x00\x00"
                  "\x01" "TestValue\x00"    "\xba\x49\x0c\x02\x2b\xe7\x36\x40"
                  "\x01" "AStringKey\x00"   "\x7d\x3f\x35\x5e\xba\xb9\x53\x40"
                  "\x00";
    static const char expectedRaw2[]
                = "\x2C\x00\x00\x00"
                  "\x01" "AStringKey\x00"   "\x7d\x3f\x35\x5e\xba\xb9\x53\x40"
                  "\x01" "TestValue\x00"    "\xba\x49\x0c\x02\x2b\xe7\x36\x40"
                  "\x00";
    std::string expected1(std::begin(expectedRaw1), std::end(expectedRaw1) - 1);
    std::string expected2(std::begin(expectedRaw2), std::end(expectedRaw2) - 1);

    bool test = result == expected1
             || result == expected2;
    //bool test = result == R"({"AStringKey":78.902,"TestValue":22.903})"
    //         || result == R"({"TestValue":22.903,"AStringKey":78.902})";
    EXPECT_TRUE(test);
}

TEST(SerUnorderedMapTest, BsondeSerializeStringKey)
{
    std::unordered_map<std::string, bool>  data;

    //std::stringstream       stream(R"({"OneFileDay":true, "TheLastStand":false, "OfMiceAndMen":true})");
    static const char inputRaw[]
                = "\x30\x00\x00\x00"
                  "\x08" "OneFileDay\x00"   "\x01"
                  "\x08" "TheLastStand\x00" "\x00"
                  "\x08" "OfMiceAndMen\x00" "\x01"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream stream(input);
    stream >> TS::bsonImporter(data, false);

    EXPECT_EQ(data["OneFileDay"],   true);
    EXPECT_EQ(data["TheLastStand"], false);
    EXPECT_EQ(data["OfMiceAndMen"], true);
}

