#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <algorithm>

using namespace ThorsAnvil::Serialize;

TEST(SerDequeTest, JsonArrayEmpty)
{
    std::stringstream   stream("[]");
    std::deque<int>    data;

    stream >> jsonImporter(data, false);

    EXPECT_EQ(data.empty(), true);
}

TEST(SerDequeTest, JsonDequeOfIntSerialize)
{
    std::deque<int>    data{1,2,3,4,5,6,7,8,101,102,9,10};

    std::stringstream   stream;
    stream << jsonExporter(data, false);

    std::string result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"([1,2,3,4,5,6,7,8,101,102,9,10])");
}
TEST(SerDequeTest, JsonDequeOfIntDeSerialize)
{
    std::deque<int>    data;
    std::stringstream   stream("[1,2,3,4,5,6,7,8,101,102,9,10]");

    stream >> jsonImporter(data, false);
    auto loop = data.begin();

    EXPECT_EQ(*loop++, 1);
    EXPECT_EQ(*loop++, 2);
    EXPECT_EQ(*loop++, 3);
    EXPECT_EQ(*loop++, 4);
    EXPECT_EQ(*loop++, 5);
    EXPECT_EQ(*loop++, 6);
    EXPECT_EQ(*loop++, 7);
    EXPECT_EQ(*loop++, 8);
    EXPECT_EQ(*loop++, 101);
    EXPECT_EQ(*loop++, 102);
    EXPECT_EQ(*loop++, 9);
    EXPECT_EQ(*loop++, 10);
}

TEST(SerDequeTest, BsonArrayEmpty)
{
    //std::stringstream   stream("[]");
    static const char expectedRaw[]
            = "\x05\x00\x00\x00"
              "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    std::stringstream stream(expected);
    std::deque<int>    data;

    stream >> bsonImporter(data, false);

    EXPECT_EQ(data.empty(), true);
}

TEST(SerDequeTest, BsonDequeOfIntSerialize)
{
    std::deque<int>    data{1,2,3,4,5,6,7,8,101,102,9,10};

    std::stringstream   stream;
    stream << bsonExporter(data, false);

    std::string result  = stream.str();

    static const char expectedRaw[]
                    = "\x5B\x00\x00\x00"
                      "\x10" "0\x00"  "\x01\x00\x00\x00"
                      "\x10" "1\x00"  "\x02\x00\x00\x00"
                      "\x10" "2\x00"  "\x03\x00\x00\x00"
                      "\x10" "3\x00"  "\x04\x00\x00\x00"
                      "\x10" "4\x00"  "\x05\x00\x00\x00"
                      "\x10" "5\x00"  "\x06\x00\x00\x00"
                      "\x10" "6\x00"  "\x07\x00\x00\x00"
                      "\x10" "7\x00"  "\x08\x00\x00\x00"
                      "\x10" "8\x00"  "\x65\x00\x00\x00"
                      "\x10" "9\x00"  "\x66\x00\x00\x00"
                      "\x10" "10\x00" "\x09\x00\x00\x00"
                      "\x10" "11\x00" "\x0A\x00\x00\x00"
                      "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(result, expected);
}
TEST(SerDequeTest, BsonDequeOfIntDeSerialize)
{
    std::deque<int>    data;
    //std::stringstream   stream("[1,2,3,4,5,6,7,8,101,102,9,10]");
    static const char expectedRaw[]
                    = "\x5B\x00\x00\x00"
                      "\x10" "0\x00"  "\x01\x00\x00\x00"
                      "\x10" "1\x00"  "\x02\x00\x00\x00"
                      "\x10" "2\x00"  "\x03\x00\x00\x00"
                      "\x10" "3\x00"  "\x04\x00\x00\x00"
                      "\x10" "4\x00"  "\x05\x00\x00\x00"
                      "\x10" "5\x00"  "\x06\x00\x00\x00"
                      "\x10" "6\x00"  "\x07\x00\x00\x00"
                      "\x10" "7\x00"  "\x08\x00\x00\x00"
                      "\x10" "8\x00"  "\x65\x00\x00\x00"
                      "\x10" "9\x00"  "\x66\x00\x00\x00"
                      "\x10" "10\x00" "\x09\x00\x00\x00"
                      "\x10" "11\x00" "\x0A\x00\x00\x00"
                      "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    std::stringstream   stream(expected);

    stream >> bsonImporter(data, false);
    auto loop = data.begin();

    EXPECT_EQ(*loop++, 1);
    EXPECT_EQ(*loop++, 2);
    EXPECT_EQ(*loop++, 3);
    EXPECT_EQ(*loop++, 4);
    EXPECT_EQ(*loop++, 5);
    EXPECT_EQ(*loop++, 6);
    EXPECT_EQ(*loop++, 7);
    EXPECT_EQ(*loop++, 8);
    EXPECT_EQ(*loop++, 101);
    EXPECT_EQ(*loop++, 102);
    EXPECT_EQ(*loop++, 9);
    EXPECT_EQ(*loop++, 10);
}

