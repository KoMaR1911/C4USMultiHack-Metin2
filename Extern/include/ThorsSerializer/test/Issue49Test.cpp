#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Traits.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <memory>
#include <iostream>


using namespace std::string_literals;
using namespace ThorsAnvil::Serialize;
using namespace std;

namespace Issue49
{
    enum class FloatFormat {scientific = 1,fixed = 2,hex = 4,general = fixed | scientific};
}
ThorsAnvil_MakeEnum(Issue49::FloatFormat, scientific, fixed, hex, general);

TEST(Issue49Test, JsonStreamScientific)
{
    std::stringstream stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::scientific;
    stream << ThorsAnvil::Serialize::jsonExporter(testData, false);

    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ("\"scientific\"", result);
}
TEST(Issue49Test, JsonStreamFixed)
{
    std::stringstream stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::fixed;
    stream << ThorsAnvil::Serialize::jsonExporter(testData, false);

    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ("\"fixed\"", result);
}
TEST(Issue49Test, JsonStreamHex)
{
    std::stringstream stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::hex;
    stream << ThorsAnvil::Serialize::jsonExporter(testData, false);

    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ("\"hex\"", result);
}
TEST(Issue49Test, JsonStreamGeneral)
{
    std::stringstream stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream << ThorsAnvil::Serialize::jsonExporter(testData, false);

    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ("\"general\"", result);
}
TEST(Issue49Test, JsonImportScientific)
{
    std::string input = R"("scientific")";
    std::stringstream stream(input);

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream >> ThorsAnvil::Serialize::jsonImporter(testData, false);

    EXPECT_EQ(Issue49::FloatFormat::scientific, testData);
}
TEST(Issue49Test, JsonImportFixed)
{
    std::string input = R"("fixed")";
    std::stringstream stream(input);

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream >> ThorsAnvil::Serialize::jsonImporter(testData, false);

    EXPECT_EQ(Issue49::FloatFormat::fixed, testData);
}
TEST(Issue49Test, JsonImportHex)
{
    std::string input = R"("hex")";
    std::stringstream stream(input);

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream >> ThorsAnvil::Serialize::jsonImporter(testData, false);

    EXPECT_EQ(Issue49::FloatFormat::hex, testData);
}
TEST(Issue49Test, JsonImportGeneral)
{
    std::string input = R"("general")";
    std::stringstream stream(input);

    Issue49::FloatFormat    testData = Issue49::FloatFormat::scientific;
    stream >> ThorsAnvil::Serialize::jsonImporter(testData, false);

    EXPECT_EQ(Issue49::FloatFormat::general, testData);
}

TEST(Issue49Test, BsonStreamScientific)
{
    std::stringstream stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::scientific;
    stream << ThorsAnvil::Serialize::bsonExporter(testData, false);

    std::string result = stream.str();

    EXPECT_EQ(result, "\x17\x00\x00\x00"
                      "\x02" "0\x00" "\x0B\x00\x00\x00" "scientific\x00"
                      "\x00"s);
    //EXPECT_EQ("\"scientific\"", result);
}
TEST(Issue49Test, BsonStreamFixed)
{
    std::stringstream stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::fixed;
    stream << ThorsAnvil::Serialize::bsonExporter(testData, false);

    std::string result = stream.str();

    EXPECT_EQ(result, "\x12\x00\x00\x00"
                      "\x02" "0\x00" "\x06\x00\x00\x00" "fixed\x00"
                      "\x00"s);
    //EXPECT_EQ("\"fixed\"", result);
}
TEST(Issue49Test, BsonStreamHex)
{
    std::stringstream stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::hex;
    stream << ThorsAnvil::Serialize::bsonExporter(testData, false);

    std::string result = stream.str();

    EXPECT_EQ(result, "\x10\x00\x00\x00"
                      "\x02" "0\x00" "\x04\x00\x00\x00" "hex\x00"
                      "\x00"s);
    //EXPECT_EQ("\"hex\"", result);
}
TEST(Issue49Test, BsonStreamGeneral)
{
    std::stringstream stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream << ThorsAnvil::Serialize::bsonExporter(testData, false);

    std::string result = stream.str();

    EXPECT_EQ(result, "\x14\x00\x00\x00"
                      "\x02" "0\x00" "\x08\x00\x00\x00" "general\x00"
                      "\x00"s);
    //EXPECT_EQ("\"general\"", result);
}
TEST(Issue49Test, BsonImportScientific)
{
    //std::string input = R"("scientific")";
    std::string input = "\x17\x00\x00\x00"
                        "\x02" "0\x00" "\x0B\x00\x00\x00" "scientific\x00"
                        "\x00"s;
    std::stringstream stream(input);

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream >> ThorsAnvil::Serialize::bsonImporter(testData, false);

    EXPECT_EQ(Issue49::FloatFormat::scientific, testData);
}
TEST(Issue49Test, BsonImportFixed)
{
    //std::string input = R"("fixed")";
    std::string input = "\x12\x00\x00\x00"
                        "\x02" "0\x00" "\x06\x00\x00\x00" "fixed\x00"
                        "\x00"s;
    std::stringstream stream(input);

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream >> ThorsAnvil::Serialize::bsonImporter(testData, false);

    EXPECT_EQ(Issue49::FloatFormat::fixed, testData);
}
TEST(Issue49Test, BsonImportHex)
{
    //std::string input = R"("hex")";
    std::string input = "\x10\x00\x00\x00"
                        "\x02" "0\x00" "\x04\x00\x00\x00" "hex\x00"
                        "\x00"s;
    std::stringstream stream(input);

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream >> ThorsAnvil::Serialize::bsonImporter(testData, false);

    EXPECT_EQ(Issue49::FloatFormat::hex, testData);
}
TEST(Issue49Test, BsonImportGeneral)
{
    //std::string input = R"("general")";
    std::string input = "\x14\x00\x00\x00"
                        "\x02" "0\x00" "\x08\x00\x00\x00" "general\x00"
                        "\x00"s;
    std::stringstream stream(input);

    Issue49::FloatFormat    testData = Issue49::FloatFormat::scientific;
    stream >> ThorsAnvil::Serialize::bsonImporter(testData, false);

    EXPECT_EQ(Issue49::FloatFormat::general, testData);
}




