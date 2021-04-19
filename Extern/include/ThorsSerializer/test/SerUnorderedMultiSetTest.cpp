#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <algorithm>

namespace TS = ThorsAnvil::Serialize;

TEST(SerUnorderedMultiSetTest, Jsonserialize)
{
    std::unordered_multiset<int>  data{24,8,11,2,2,2};

    std::stringstream       stream;
    stream << TS::jsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    bool test = result == R"([2,2,2,8,11,24])"
             || result == R"([2,2,8,2,11,24])"
             || result == R"([2,2,8,11,2,24])"
             || result == R"([2,2,8,11,24,2])"
             || result == R"([2,8,2,11,24,2])"
             || result == R"([2,8,11,2,24,2])"
             || result == R"([2,8,11,24,2,2])"
             || result == R"([8,2,11,24,2,2])"
             || result == R"([8,11,2,24,2,2])"
             || result == R"([8,11,24,2,2,2])"
             || result == R"([8,2,2,2,11,24])"
             || result == R"([8,2,2,11,2,24])"
             || result == R"([8,2,2,11,24,2])"
             || result == R"([8,2,11,2,24,2])"
             || result == R"([8,11,2,2,2,24])"
             || result == R"([8,11,2,2,24,2])"

             || result == R"([2,2,2,8,24,11])"
             || result == R"([2,2,8,2,24,11])"
             || result == R"([2,2,8,24,2,11])"
             || result == R"([2,2,8,24,11,2])"
             || result == R"([2,8,2,24,11,2])"
             || result == R"([2,8,24,2,11,2])"
             || result == R"([2,8,24,11,2,2])"
             || result == R"([8,2,24,11,2,2])"
             || result == R"([8,24,2,11,2,2])"
             || result == R"([8,24,11,2,2,2])"
             || result == R"([8,2,2,2,24,11])"
             || result == R"([8,2,2,24,2,11])"
             || result == R"([8,2,2,24,11,2])"
             || result == R"([8,2,24,2,11,2])"
             || result == R"([8,24,2,2,2,11])"
             || result == R"([8,24,2,2,11,2])"

             || result == R"([2,2,2,11,8,24])"
             || result == R"([2,2,11,2,8,24])"
             || result == R"([2,2,11,8,2,24])"
             || result == R"([2,2,11,8,24,2])"
             || result == R"([2,11,2,8,24,2])"
             || result == R"([2,11,8,2,24,2])"
             || result == R"([2,11,8,24,2,2])"
             || result == R"([11,2,8,24,2,2])"
             || result == R"([11,8,2,24,2,2])"
             || result == R"([11,8,24,2,2,2])"
             || result == R"([11,2,2,2,8,24])"
             || result == R"([11,2,2,8,2,24])"
             || result == R"([11,2,2,8,24,2])"
             || result == R"([11,2,8,2,24,2])"
             || result == R"([11,8,2,2,2,24])"
             || result == R"([11,8,2,2,24,2])"

             || result == R"([2,2,2,24,11,8])"
             || result == R"([2,2,24,2,11,8])"
             || result == R"([2,2,24,11,2,8])"
             || result == R"([2,2,24,11,8,2])"
             || result == R"([2,24,2,11,8,2])"
             || result == R"([2,24,11,2,8,2])"
             || result == R"([2,24,11,8,2,2])"
             || result == R"([24,2,11,8,2,2])"
             || result == R"([24,11,2,8,2,2])"
             || result == R"([24,11,8,2,2,2])"
             || result == R"([24,2,2,2,11,8])"
             || result == R"([24,2,2,11,2,8])"
             || result == R"([24,2,2,11,8,2])"
             || result == R"([24,2,11,2,8,2])"
             || result == R"([24,11,2,2,2,8])"
             || result == R"([24,11,2,2,8,2])"

             || result == R"([2,2,2,11,24,8])"
             || result == R"([2,2,11,2,24,8])"
             || result == R"([2,2,11,24,2,8])"
             || result == R"([2,2,11,24,8,2])"
             || result == R"([2,11,2,24,8,2])"
             || result == R"([2,11,24,2,8,2])"
             || result == R"([2,11,24,8,2,2])"
             || result == R"([11,2,24,8,2,2])"
             || result == R"([11,24,2,8,2,2])"
             || result == R"([11,24,8,2,2,2])"
             || result == R"([11,2,2,2,24,8])"
             || result == R"([11,2,2,24,2,8])"
             || result == R"([11,2,2,24,8,2])"
             || result == R"([11,2,24,2,8,2])"
             || result == R"([11,24,2,2,2,8])"
             || result == R"([11,24,2,2,8,2])"

             || result == R"([2,2,2,24,8,11])"
             || result == R"([2,2,24,2,8,11])"
             || result == R"([2,2,24,8,2,11])"
             || result == R"([2,2,24,8,11,2])"
             || result == R"([2,24,2,8,11,2])"
             || result == R"([2,24,8,2,11,2])"
             || result == R"([2,24,8,11,2,2])"
             || result == R"([24,2,8,11,2,2])"
             || result == R"([24,8,2,11,2,2])"
             || result == R"([24,8,11,2,2,2])"
             || result == R"([24,2,2,2,8,11])"
             || result == R"([24,2,2,8,2,11])"
             || result == R"([24,2,2,8,11,2])"
             || result == R"([24,2,8,2,11,2])"
             || result == R"([24,8,2,2,2,11])"
             || result == R"([24,8,2,2,11,2])";
    EXPECT_TRUE(test);

}

TEST(SerUnorderedMultiSetTest, JsondeSerialize)
{
    std::unordered_multiset<int>  data;

    std::stringstream       stream(R"([5,6,8,8,101,123])");
    stream >> TS::jsonImporter(data, false);

    EXPECT_TRUE(data.find(5) != data.end());
    EXPECT_TRUE(data.find(6) != data.end());
    EXPECT_TRUE(data.find(8) != data.end());
    EXPECT_TRUE(data.find(101) != data.end());
    EXPECT_TRUE(data.find(123) != data.end());
    EXPECT_EQ(data.count(8), 2);
}

TEST(SerUnorderedMultiSetTest, Bsonserialize)
{
    std::unordered_multiset<int>  data{24,8,11};

    std::stringstream       stream;
    stream << TS::bsonExporter(data, false);
    std::string result = stream.str();

    static const char expectedRaw1[]
                = "\x1A\x00\x00\x00"
                  "\x10" "0\x00"    "\x18\x00\x00\x00"
                  "\x10" "1\x00"    "\x08\x00\x00\x00"
                  "\x10" "2\x00"    "\x0B\x00\x00\x00"
                  "\x00";
    static const char expectedRaw2[]
                = "\x1A\x00\x00\x00"
                  "\x10" "0\x00"    "\x18\x00\x00\x00"
                  "\x10" "1\x00"    "\x0B\x00\x00\x00"
                  "\x10" "2\x00"    "\x08\x00\x00\x00"
                  "\x00";
    static const char expectedRaw3[]
                = "\x1A\x00\x00\x00"
                  "\x10" "0\x00"    "\x08\x00\x00\x00"
                  "\x10" "1\x00"    "\x18\x00\x00\x00"
                  "\x10" "2\x00"    "\x0B\x00\x00\x00"
                  "\x00";
    static const char expectedRaw4[]
                = "\x1A\x00\x00\x00"
                  "\x10" "0\x00"    "\x08\x00\x00\x00"
                  "\x10" "1\x00"    "\x0B\x00\x00\x00"
                  "\x10" "2\x00"    "\x18\x00\x00\x00"
                  "\x00";
    static const char expectedRaw5[]
                = "\x1A\x00\x00\x00"
                  "\x10" "0\x00"    "\x0B\x00\x00\x00"
                  "\x10" "1\x00"    "\x18\x00\x00\x00"
                  "\x10" "2\x00"    "\x08\x00\x00\x00"
                  "\x00";
    static const char expectedRaw6[]
                = "\x1A\x00\x00\x00"
                  "\x10" "0\x00"    "\x0B\x00\x00\x00"
                  "\x10" "1\x00"    "\x08\x00\x00\x00"
                  "\x10" "2\x00"    "\x18\x00\x00\x00"
                  "\x00";
    std::string expected1(std::begin(expectedRaw1), std::end(expectedRaw1) - 1);
    std::string expected2(std::begin(expectedRaw2), std::end(expectedRaw2) - 1);
    std::string expected3(std::begin(expectedRaw3), std::end(expectedRaw3) - 1);
    std::string expected4(std::begin(expectedRaw4), std::end(expectedRaw4) - 1);
    std::string expected5(std::begin(expectedRaw5), std::end(expectedRaw5) - 1);
    std::string expected6(std::begin(expectedRaw6), std::end(expectedRaw6) - 1);

    bool test = result == expected1 || result == expected2 || result == expected3
             || result == expected4 || result == expected5 || result == expected6;

    EXPECT_TRUE(test);
}

TEST(SerUnorderedMultiSetTest, BsondeSerialize)
{
    std::unordered_multiset<int>  data;

    //std::stringstream       stream(R"([5,6,8,8,101,123])");
    static const char inputRaw[]
                = "\x2F\x00\x00\x00"
                  "\x10" "0\x00" "\x05\x00\x00\x00"
                  "\x10" "1\x00" "\x06\x00\x00\x00"
                  "\x10" "2\x00" "\x08\x00\x00\x00"
                  "\x10" "3\x00" "\x08\x00\x00\x00"
                  "\x10" "4\x00" "\x65\x00\x00\x00"
                  "\x10" "5\x00" "\x7b\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream stream(input);
    stream >> TS::bsonImporter(data, false);

    EXPECT_TRUE(data.find(5) != data.end());
    EXPECT_TRUE(data.find(6) != data.end());
    EXPECT_TRUE(data.find(8) != data.end());
    EXPECT_TRUE(data.find(101) != data.end());
    EXPECT_TRUE(data.find(123) != data.end());
    EXPECT_EQ(data.count(8), 2);
}

