#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "BsonParser.h"

// enum class ParserToken {Error, DocStart, DocEnd, MapStart, MapEnd, ArrayStart, ArrayEnd, Key, Value};

namespace TA=ThorsAnvil::Serialize;
using TA::ParserInterface;

TEST(BsonParserTest, ArrayEmpty)
{
    //std::stringstream   stream("[]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x05\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser          parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BsonParserTest, ArrayOneValue)
{
    //std::stringstream   stream("[12]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0C\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BsonParserTest, ArrayTwoValue)
{
    //std::stringstream   stream("[12,13]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x13\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0C\x00\x00\x00"
                  "\x10"  "1\x00"  "\x0D\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BsonParserTest, ArrayThreeValue)
{
    //std::stringstream   stream("[12,13,14]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x1A\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0C\x00\x00\x00"
                  "\x10"  "1\x00"  "\x0D\x00\x00\x00"
                  "\x10"  "2\x00"  "\x0E\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BsonParserTest, ArrayWithArray)
{
    //std::stringstream   stream("[[]]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x04"  "0\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BsonParserTest, ArrayWithTwoArray)
{
    //std::stringstream   stream("[[],[]]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x15\x00\x00\x00"
                  "\x04"  "0\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x04"  "1\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BsonParserTest, ArrayWithMap)
{
    //std::stringstream   stream("[{}]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x03"  "0\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BsonParserTest, ArrayWithTwoMap)
{
    //std::stringstream   stream("[{},{}]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x15\x00\x00\x00"
                  "\x03"  "0\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x03"  "1\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BsonParserTest, MapEmpty)
{
    //std::stringstream   stream("{}");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x05\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BsonParserTest, MapOneValue)
{
    //std::stringstream   stream(R"({"One": 12})");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0E\x00\x00\x00"
                  "\x10" "One\x00" "\x0C\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BsonParserTest, MapTwoValue)
{
    //std::stringstream   stream(R"({"one": 12, "two": 13})");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x17\x00\x00\x00"
                  "\x10" "One\x00" "\x0C\x00\x00\x00"
                  "\x10" "Two\x00" "\x0D\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BsonParserTest, MapThreeValue)
{
    //std::stringstream   stream(R"({"one":12, "two": 13, "three": 14})");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x22\x00\x00\x00"
                  "\x10" "One\x00" "\x0C\x00\x00\x00"
                  "\x10" "Two\x00" "\x0D\x00\x00\x00"
                  "\x10" "Three\x00" "\x0E\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BsonParserTest, MapWithArray)
{
    //std::stringstream   stream(R"({"one": []})");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0F\x00\x00\x00"
                  "\x04" "one\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BsonParserTest, MapWithTwoArray)
{
    //std::stringstream   stream(R"({"one": [], "two": []}])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x19\x00\x00\x00"
                  "\x04" "one\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x04" "two\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BsonParserTest, MapWithMap)
{
    //std::stringstream   stream(R"({"one": {}})");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0F\x00\x00\x00"
                  "\x03" "one\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BsonParserTest, MapWithTwoMap)
{
    //std::stringstream   stream(R"({"one": {}, "two": {}})");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x19\x00\x00\x00"
                  "\x03" "one\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x03" "two\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BsonParserTest, GetKeyValue)
{
    //std::stringstream   stream(R"({"one": 15})");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0E\x00\x00\x00"
                  "\x10" "one\x00" "\x0F\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());

    std::string key     = parser.getKey();
    EXPECT_EQ("one", key);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    int value;
    parser.getValue(value);
    EXPECT_EQ(15, value);

    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BsonParserTest, GetArrayValues)
{
    //std::stringstream   stream(R"([true, false, 123, 123.4, "A String"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x2F\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x00"
                  "\x10" "2\x00" "\x7B\x00\x00\x00"
                  "\x01" "3\x00" "\x9A\x99\x99\x99\x99\xD9\x5E\x40"
                  "\x02" "4\x00" "\x09\x00\x00\x00" "A String\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    bool    test1   = false;
    parser.getValue(test1);
    EXPECT_EQ(true, test1);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    bool    test2   = true;
    parser.getValue(test2);
    EXPECT_EQ(false, test2);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    int    test3   = 0;
    parser.getValue(test3);
    EXPECT_EQ(123, test3);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    double test4   = 80;
    parser.getValue(test4);
    EXPECT_EQ(1234, (int)(test4*10));

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string    test5;
    parser.getValue(test5);
    EXPECT_EQ("A String", test5);


    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}

TEST(BsonParserTest, getDataFromString_1)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_NO_THROW(
        parser.getValue(value1);
    );
    EXPECT_EQ("Test", value1);
}

TEST(BsonParserTest, getDataFromString_2)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x13\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    short             value2a;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
}

TEST(BsonParserTest, getDataFromString_3)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    int             value2b;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
}

TEST(BsonParserTest, getDataFromString_4)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long             value2c;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
}

TEST(BsonParserTest, getDataFromString_5)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long long             value2d;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );
}

TEST(BsonParserTest, getDataFromString_6)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    unsigned short             value2e;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
}

TEST(BsonParserTest, getDataFromString_7)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    unsigned int             value2f;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
}

TEST(BsonParserTest, getDataFromString_8)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    unsigned long             value2g;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
}

TEST(BsonParserTest, getDataFromString_9)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    unsigned long long             value2h;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );

}

TEST(BsonParserTest, getDataFromString_a)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    float          value3a;
    ASSERT_ANY_THROW(
        parser.getValue(value3a)
    );
}

TEST(BsonParserTest, getDataFromString_b)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    double          value3b;
    ASSERT_ANY_THROW(
        parser.getValue(value3b)
    );
}

TEST(BsonParserTest, getDataFromString_c)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
}

TEST(BsonParserTest, getDataFromString_d)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long double          value3c;
    ASSERT_ANY_THROW(
        parser.getValue(value3c)
    );

}

TEST(BsonParserTest, getDataFromString_e)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}

TEST(BsonParserTest, getDataFromInt_1)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(BsonParserTest, getDataFromInt_2)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    short             value2a;
    ASSERT_NO_THROW(
        parser.getValue(value2a)
    );
    EXPECT_EQ(56, value2a);
}

TEST(BsonParserTest, getDataFromInt_3)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    int             value2b;
    ASSERT_NO_THROW(
        parser.getValue(value2b)
    );
    EXPECT_EQ(56, value2b);
}

TEST(BsonParserTest, getDataFromInt_4)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long             value2c;
    ASSERT_NO_THROW(
        parser.getValue(value2c)
    );
    EXPECT_EQ(56, value2c);
}

TEST(BsonParserTest, getDataFromInt_5)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long long             value2d;
    ASSERT_NO_THROW(
        parser.getValue(value2d)
    );
    EXPECT_EQ(56, value2d);
}

TEST(BsonParserTest, getDataFromInt_6)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    short             value2e;
    ASSERT_NO_THROW(
        parser.getValue(value2e)
    );
    EXPECT_EQ(56, value2e);
}

TEST(BsonParserTest, getDataFromInt_7)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    int             value2f;
    ASSERT_NO_THROW(
        parser.getValue(value2f)
    );
    EXPECT_EQ(56, value2f);
}

TEST(BsonParserTest, getDataFromInt_8)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long             value2g;
    ASSERT_NO_THROW(
        parser.getValue(value2g)
    );
    EXPECT_EQ(56, value2g);
}

TEST(BsonParserTest, getDataFromInt_9)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long long             value2h;
    ASSERT_NO_THROW(
        parser.getValue(value2h)
    );
    EXPECT_EQ(56, value2h);
}

TEST(BsonParserTest, getDataFromInt_a)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    float          value3a;
    ASSERT_NO_THROW(
        parser.getValue(value3a)
    );
    EXPECT_EQ(56, value3a);
}

TEST(BsonParserTest, getDataFromInt_b)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    double          value3b;
    ASSERT_NO_THROW(
        parser.getValue(value3b)
    );
    EXPECT_EQ(56, value3b);
}

TEST(BsonParserTest, getDataFromInt_c)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long double          value3c;
    ASSERT_NO_THROW(
        parser.getValue(value3c)
    );
    EXPECT_EQ(56, value3c);
}

TEST(BsonParserTest, getDataFromInt_d)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}

TEST(BsonParserTest, getDataFromFloat_1)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(BsonParserTest, getDataFromFloat_2)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    short             value2a;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
}

TEST(BsonParserTest, getDataFromFloat_3)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    int             value2b;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
}

TEST(BsonParserTest, getDataFromFloat_4)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long             value2c;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
}

TEST(BsonParserTest, getDataFromFloat_5)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long long             value2d;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );
}

TEST(BsonParserTest, getDataFromFloat_6)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned short             value2e;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
}

TEST(BsonParserTest, getDataFromFloat_7)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned int             value2f;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
}

TEST(BsonParserTest, getDataFromFloat_8)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned long             value2g;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
}

TEST(BsonParserTest, getDataFromFloat_9)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned long long             value2h;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );
}

TEST(BsonParserTest, getDataFromFloat_a)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    float          value3a;
    ASSERT_NO_THROW(
        parser.getValue(value3a)
    );
    EXPECT_EQ(12356, static_cast<int>(value3a * 100 + .5));
}

TEST(BsonParserTest, getDataFromFloat_b)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    double          value3b;
    ASSERT_NO_THROW(
        parser.getValue(value3b)
    );
    EXPECT_EQ(12356, static_cast<int>(value3b * 100 + .5));
}

TEST(BsonParserTest, getDataFromFloat_c)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long double          value3c;
    ASSERT_NO_THROW(
        parser.getValue(value3c)
    );
    EXPECT_EQ(12356, static_cast<int>(value3c * 100 + .5));

}

TEST(BsonParserTest, getDataFromFloat_d)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}
TEST(BsonParserTest, getDataFromBool_1)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(BsonParserTest, getDataFromBool_2)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(BsonParserTest, getDataFromBool_3)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    short             value2a;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
}

TEST(BsonParserTest, getDataFromBool_4)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    int             value2b;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
}

TEST(BsonParserTest, getDataFromBool_5)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long             value2c;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
}

TEST(BsonParserTest, getDataFromBool_6)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long long             value2d;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );
}

TEST(BsonParserTest, getDataFromBool_7)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned short             value2e;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
}

TEST(BsonParserTest, getDataFromBool_8)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned int             value2f;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
}

TEST(BsonParserTest, getDataFromBool_9)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned long             value2g;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
}

TEST(BsonParserTest, getDataFromBool_a)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned long long             value2h;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );
}

TEST(BsonParserTest, getDataFromBool_b)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    float          value3a;
    ASSERT_ANY_THROW(
        parser.getValue(value3a)
    );
}

TEST(BsonParserTest, getDataFromBool_c)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    double          value3b;
    ASSERT_ANY_THROW(
        parser.getValue(value3b)
    );
}

TEST(BsonParserTest, getDataFromBool_d)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long double          value3c;
    ASSERT_ANY_THROW(
        parser.getValue(value3c)
    );
}

TEST(BsonParserTest, getDataFromBool_e)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    bool            value4 = false;
    ASSERT_NO_THROW(
        parser.getValue(value4)
    );
    EXPECT_EQ(true, value4);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    ASSERT_NO_THROW(
        parser.getValue(value4)
    );
    EXPECT_EQ(false, value4);
}
TEST(BsonParserTest, getRawValue)
{
    //std::stringstream   stream(R"([true, false, 0, 15.4, "The Best"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x2F\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x00"
                  "\x10" "2\x00" "\x00\x00\x00\x00"
                  "\x01" "3\x00" "\xCD\xCC\xCC\xCC\xCC\xCC\x2E\x40"
                  "\x02" "4\x00" "\x09\x00\x00\x00" "The Best\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);
    std::string         value;

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    value = parser.getRawValue();
    EXPECT_EQ(std::string("true"), value);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    value = parser.getRawValue();
    EXPECT_EQ(std::string("false"), value);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    value = parser.getRawValue();
    EXPECT_EQ(std::string("0"), value);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    value = parser.getRawValue();
    EXPECT_EQ(std::string("15.4"), value.substr(0,4));

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    value = parser.getRawValue();
    EXPECT_EQ(std::string("\"The Best\""), value);
}


