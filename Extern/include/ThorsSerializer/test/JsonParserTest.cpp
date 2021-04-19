#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonParser.h"

// enum class ParserToken {Error, DocStart, DocEnd, MapStart, MapEnd, ArrayStart, ArrayEnd, Key, Value};

namespace TA=ThorsAnvil::Serialize;
using TA::ParserInterface;

TEST(JsonParserTest, ArrayEmpty)
{
    std::stringstream   stream("[]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTest, ArrayOneValue)
{
    std::stringstream   stream("[12]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTest, ArrayTwoValue)
{
    std::stringstream   stream("[12,13]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTest, ArrayThreeValue)
{
    std::stringstream   stream("[12,13,14]");
    TA::JsonParser      parser(stream);

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
TEST(JsonParserTest, ArrayWithArray)
{
    std::stringstream   stream("[[]]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTest, ArrayWithTwoArray)
{
    std::stringstream   stream("[[],[]]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTest, ArrayWithMap)
{
    std::stringstream   stream("[{}]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTest, ArrayWithTwoMap)
{
    std::stringstream   stream("[{},{}]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTest, MapEmpty)
{
    std::stringstream   stream("{}");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTest, MapOneValue)
{
    std::stringstream   stream(R"({"One": 12})");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTest, MapTwoValue)
{
    std::stringstream   stream(R"({"one": 12, "two": 13})");
    TA::JsonParser      parser(stream);

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
TEST(JsonParserTest, MapThreeValue)
{
    std::stringstream   stream(R"({"one":12, "two": 13, "three": 14})");
    TA::JsonParser      parser(stream);

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
TEST(JsonParserTest, MapWithArray)
{
    std::stringstream   stream(R"({"one": []})");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTest, MapWithTwoArray)
{
    std::stringstream   stream(R"({"one": [], "two": []}])");
    TA::JsonParser      parser(stream);

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
TEST(JsonParserTest, MapWithMap)
{
    std::stringstream   stream(R"({"one": {}})");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTest, MapWithTwoMap)
{
    std::stringstream   stream(R"({"one": {}, "two": {}})");
    TA::JsonParser      parser(stream);

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
TEST(JsonParserTest, GetKeyValue)
{
    std::stringstream   stream(R"({"one": 15})");
    TA::JsonParser      parser(stream);

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
TEST(JsonParserTest, GetArrayValues)
{
    std::stringstream   stream(R"([true, false, 123, 123.4, "A String"])");
    TA::JsonParser      parser(stream);

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
TEST(JsonParserTest, CheckErrorDoesNotRead)
{
    std::stringstream   stream("][");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());

    // First Character is an error.
    EXPECT_EQ(ParserInterface::ParserToken::Error,      parser.getToken());

    // Subsequent read should also be an error.
    // But it should not read from the stream
    EXPECT_EQ(ParserInterface::ParserToken::Error,      parser.getToken());

    char  next;
    stream >> next;
    EXPECT_EQ('[', next);
}

TEST(JsonParserTest, getDataFromString_1)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_NO_THROW(
        parser.getValue(value1);
    );
    EXPECT_EQ("Test", value1);
}

TEST(JsonParserTest, getDataFromString_2)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    short             value2a;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
}

TEST(JsonParserTest, getDataFromString_3)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    int             value2b;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
}

TEST(JsonParserTest, getDataFromString_4)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long             value2c;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
}

TEST(JsonParserTest, getDataFromString_5)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long long             value2d;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );
}

TEST(JsonParserTest, getDataFromString_6)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    unsigned short             value2e;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
}

TEST(JsonParserTest, getDataFromString_7)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    unsigned int             value2f;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
}

TEST(JsonParserTest, getDataFromString_8)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    unsigned long             value2g;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
}

TEST(JsonParserTest, getDataFromString_9)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    unsigned long long             value2h;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );

}

TEST(JsonParserTest, getDataFromString_a)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    float          value3a;
    ASSERT_ANY_THROW(
        parser.getValue(value3a)
    );
}

TEST(JsonParserTest, getDataFromString_b)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    double          value3b;
    ASSERT_ANY_THROW(
        parser.getValue(value3b)
    );
}

TEST(JsonParserTest, getDataFromString_c)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
}

TEST(JsonParserTest, getDataFromString_d)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long double          value3c;
    ASSERT_ANY_THROW(
        parser.getValue(value3c)
    );

}

TEST(JsonParserTest, getDataFromString_e)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}

TEST(JsonParserTest, getDataFromInt_1)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(JsonParserTest, getDataFromInt_2)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    short             value2a;
    ASSERT_NO_THROW(
        parser.getValue(value2a)
    );
    EXPECT_EQ(56, value2a);
}

TEST(JsonParserTest, getDataFromInt_3)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    int             value2b;
    ASSERT_NO_THROW(
        parser.getValue(value2b)
    );
    EXPECT_EQ(56, value2b);
}

TEST(JsonParserTest, getDataFromInt_4)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long             value2c;
    ASSERT_NO_THROW(
        parser.getValue(value2c)
    );
    EXPECT_EQ(56, value2c);
}

TEST(JsonParserTest, getDataFromInt_5)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long long             value2d;
    ASSERT_NO_THROW(
        parser.getValue(value2d)
    );
    EXPECT_EQ(56, value2d);
}

TEST(JsonParserTest, getDataFromInt_6)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    short             value2e;
    ASSERT_NO_THROW(
        parser.getValue(value2e)
    );
    EXPECT_EQ(56, value2e);
}

TEST(JsonParserTest, getDataFromInt_7)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    int             value2f;
    ASSERT_NO_THROW(
        parser.getValue(value2f)
    );
    EXPECT_EQ(56, value2f);
}

TEST(JsonParserTest, getDataFromInt_8)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long             value2g;
    ASSERT_NO_THROW(
        parser.getValue(value2g)
    );
    EXPECT_EQ(56, value2g);
}

TEST(JsonParserTest, getDataFromInt_9)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long long             value2h;
    ASSERT_NO_THROW(
        parser.getValue(value2h)
    );
    EXPECT_EQ(56, value2h);
}

TEST(JsonParserTest, getDataFromInt_a)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    float          value3a;
    ASSERT_NO_THROW(
        parser.getValue(value3a)
    );
    EXPECT_EQ(56, value3a);
}

TEST(JsonParserTest, getDataFromInt_b)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    double          value3b;
    ASSERT_NO_THROW(
        parser.getValue(value3b)
    );
    EXPECT_EQ(56, value3b);
}

TEST(JsonParserTest, getDataFromInt_c)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long double          value3c;
    ASSERT_NO_THROW(
        parser.getValue(value3c)
    );
    EXPECT_EQ(56, value3c);
}

TEST(JsonParserTest, getDataFromInt_d)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}

TEST(JsonParserTest, getDataFromFloat_1)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(JsonParserTest, getDataFromFloat_2)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    short             value2a;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
}

TEST(JsonParserTest, getDataFromFloat_3)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    int             value2b;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
}

TEST(JsonParserTest, getDataFromFloat_4)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long             value2c;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
}

TEST(JsonParserTest, getDataFromFloat_5)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long long             value2d;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );
}

TEST(JsonParserTest, getDataFromFloat_6)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned short             value2e;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
}

TEST(JsonParserTest, getDataFromFloat_7)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned int             value2f;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
}

TEST(JsonParserTest, getDataFromFloat_8)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned long             value2g;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
}

TEST(JsonParserTest, getDataFromFloat_9)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned long long             value2h;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );
}

TEST(JsonParserTest, getDataFromFloat_a)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    float          value3a;
    ASSERT_NO_THROW(
        parser.getValue(value3a)
    );
    EXPECT_EQ(12356, static_cast<int>(value3a * 100 + .5));
}

TEST(JsonParserTest, getDataFromFloat_b)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    double          value3b;
    ASSERT_NO_THROW(
        parser.getValue(value3b)
    );
    EXPECT_EQ(12356, static_cast<int>(value3b * 100 + .5));
}

TEST(JsonParserTest, getDataFromFloat_c)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long double          value3c;
    ASSERT_NO_THROW(
        parser.getValue(value3c)
    );
    EXPECT_EQ(12356, static_cast<int>(value3c * 100 + .5));

}

TEST(JsonParserTest, getDataFromFloat_d)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}
TEST(JsonParserTest, getDataFromBool_1)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(JsonParserTest, getDataFromBool_2)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(JsonParserTest, getDataFromBool_3)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    short             value2a;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
}

TEST(JsonParserTest, getDataFromBool_4)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    int             value2b;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
}

TEST(JsonParserTest, getDataFromBool_5)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long             value2c;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
}

TEST(JsonParserTest, getDataFromBool_6)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long long             value2d;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );
}

TEST(JsonParserTest, getDataFromBool_7)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned short             value2e;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
}

TEST(JsonParserTest, getDataFromBool_8)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned int             value2f;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
}

TEST(JsonParserTest, getDataFromBool_9)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned long             value2g;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
}

TEST(JsonParserTest, getDataFromBool_a)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned long long             value2h;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );
}

TEST(JsonParserTest, getDataFromBool_b)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    float          value3a;
    ASSERT_ANY_THROW(
        parser.getValue(value3a)
    );
}

TEST(JsonParserTest, getDataFromBool_c)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    double          value3b;
    ASSERT_ANY_THROW(
        parser.getValue(value3b)
    );
}

TEST(JsonParserTest, getDataFromBool_d)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long double          value3c;
    ASSERT_ANY_THROW(
        parser.getValue(value3c)
    );
}

TEST(JsonParserTest, getDataFromBool_e)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

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
TEST(JsonParserTest, getRawValue)
{
    std::stringstream   stream(R"([true, false, 0, 15.4, "The Best"])");
    TA::JsonParser      parser(stream);
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
    EXPECT_EQ(std::string("15.4"), value);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    value = parser.getRawValue();
    EXPECT_EQ(std::string("\"The Best\""), value);
}



