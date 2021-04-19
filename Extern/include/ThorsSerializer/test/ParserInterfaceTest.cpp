#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonParser.h"
#include "BsonParser.h"

namespace TA=ThorsAnvil::Serialize;
using TA::JsonParser;
using TA::BsonParser;
using TA::ParserInterface;

TEST(ParserInterfaceTest, JsonNormalNoPushBack)
{
    std::stringstream   stream("[10,11,12]");
    JsonParser          parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd, parser.getToken());
}

TEST(ParserInterfaceTest, JsonPushBackValue)
{
    std::stringstream   stream("[10,11,12]");
    JsonParser          parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserInterface::ParserToken::Value);
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();

    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd, parser.getToken());
}

TEST(ParserInterfaceTest, JsonPushBackTwoValue)
{
    std::stringstream   stream("[10,11,12]");
    JsonParser          parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserInterface::ParserToken::Value);
    ASSERT_ANY_THROW(
        parser.pushBackToken(ParserInterface::ParserToken::Value)
    );
}

TEST(ParserInterfaceTest, JsonPushBackTwoValueWithReads)
{
    std::stringstream   stream("[10,11,12]");
    JsonParser          parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserInterface::ParserToken::Value);
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();

    parser.pushBackToken(ParserInterface::ParserToken::Value);
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd, parser.getToken());
}

TEST(ParserInterfaceTest, BsonNormalNoPushBack)
{
    //std::stringstream   stream("[10,11,12]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x1A\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0A\x00\x00\x00"
                  "\x10"  "1\x00"  "\x0B\x00\x00\x00"
                  "\x10"  "2\x00"  "\x0C\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    BsonParser          parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd, parser.getToken());
}

TEST(ParserInterfaceTest, BsonPushBackValue)
{
    //std::stringstream   stream("[10,11,12]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x1A\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0A\x00\x00\x00"
                  "\x10"  "1\x00"  "\x0B\x00\x00\x00"
                  "\x10"  "2\x00"  "\x0C\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    BsonParser          parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserInterface::ParserToken::Value);
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();

    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd, parser.getToken());
}

TEST(ParserInterfaceTest, BsonPushBackTwoValue)
{
    //std::stringstream   stream("[10,11,12]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x1A\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0A\x00\x00\x00"
                  "\x10"  "1\x00"  "\x0B\x00\x00\x00"
                  "\x10"  "2\x00"  "\x0C\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    BsonParser          parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserInterface::ParserToken::Value);
    ASSERT_ANY_THROW(
        parser.pushBackToken(ParserInterface::ParserToken::Value)
    );
}

TEST(ParserInterfaceTest, BsonPushBackTwoValueWithReads)
{
    //std::stringstream   stream("[10,11,12]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x1A\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0A\x00\x00\x00"
                  "\x10"  "1\x00"  "\x0B\x00\x00\x00"
                  "\x10"  "2\x00"  "\x0C\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    BsonParser          parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserInterface::ParserToken::Value);
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();

    parser.pushBackToken(ParserInterface::ParserToken::Value);
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd, parser.getToken());
}


