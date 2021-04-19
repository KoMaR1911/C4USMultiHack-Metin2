#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "YamlParser.h"

// enum class ParserToken {Error, DocStart, DocEnd, MapStart, MapEnd, ArrayStart, ArrayEnd, Key, Value};

namespace TA=ThorsAnvil::Serialize;
using TA::ParserInterface;

TEST(YamlParserTest, isNullNullString)
{
    std::stringstream   stream("null");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(true,                                     parser.isValueNull());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, isNullTilda)
{
    std::stringstream   stream("~");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(true,                                     parser.isValueNull());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, ArrayEmpty)
{
    std::stringstream   stream("[]");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, ArrayOneValue)
{
    std::stringstream   stream("[12]");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, ArrayTwoValue)
{
    std::stringstream   stream("[12,13]");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, ArrayThreeValue)
{
    std::stringstream   stream("[12,13,14]");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, ArrayWithArray)
{
    std::stringstream   stream("[[]]");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, ArrayWithTwoArray)
{
    std::stringstream   stream("[[],[]]");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, ArrayWithMap)
{
    std::stringstream   stream("[{}]");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, ArrayWithTwoMap)
{
    std::stringstream   stream("[{},{}]");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, MapEmpty)
{
    std::stringstream   stream("{}");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, MapOneValue)
{
    std::stringstream   stream(R"({"One": 12})");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, MapTwoValue)
{
    std::stringstream   stream(R"({"one": 12, "two": 13})");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, MapThreeValue)
{
    std::stringstream   stream(R"({"one":12, "two": 13, "three": 14})");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, MapWithArray)
{
    std::stringstream   stream(R"({"one": []})");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, MapWithTwoArray)
{
    std::stringstream   stream(R"({"one": [], "two": []}])");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, MapWithMap)
{
    std::stringstream   stream(R"({"one": {}})");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, MapWithTwoMap)
{
    std::stringstream   stream(R"({"one": {}, "two": {}})");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, GetKeyValue)
{
    std::stringstream   stream(R"({"one": 15})");
    TA::YamlParser      parser(stream);

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
TEST(YamlParserTest, GetArrayValues)
{
    std::stringstream   stream(R"([true, false, 123, 123.4, "A String"])");
    TA::YamlParser      parser(stream);

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
TEST(YamlParserTest, CheckErrorDoesNotRead)
{
    std::stringstream   stream("][");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());

    // First Character is an error.
    EXPECT_EQ(ParserInterface::ParserToken::Error,      parser.getToken());

    // Subsequent read should also be an error.
    // But it should not read from the stream
    EXPECT_EQ(ParserInterface::ParserToken::Error,      parser.getToken());
}

TEST(YamlParserTest, getDataFromString)
{
    std::stringstream   stream(R"(["Test"])");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_NO_THROW(
        parser.getValue(value1);
    );
    EXPECT_EQ("Test", value1);

    short             value2a;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
    int             value2b;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
    long             value2c;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
    long long             value2d;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );


    unsigned short             value2e;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
    unsigned int             value2f;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
    unsigned long             value2g;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
    unsigned long long             value2h;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );

    float          value3a;
    ASSERT_ANY_THROW(
        parser.getValue(value3a)
    );
    double          value3b;
    ASSERT_ANY_THROW(
        parser.getValue(value3b)
    );
    long double          value3c;
    ASSERT_ANY_THROW(
        parser.getValue(value3c)
    );

    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}
TEST(YamlParserTest, getDataFromInt)
{
    std::stringstream   stream(R"([56])");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_NO_THROW(
        parser.getValue(value1)
    );
    EXPECT_EQ("56", value1);

    short             value2a;
    ASSERT_NO_THROW(
        parser.getValue(value2a)
    );
    EXPECT_EQ(56, value2a);
    int             value2b;
    ASSERT_NO_THROW(
        parser.getValue(value2b)
    );
    EXPECT_EQ(56, value2b);
    long             value2c;
    ASSERT_NO_THROW(
        parser.getValue(value2c)
    );
    EXPECT_EQ(56, value2c);
    long long             value2d;
    ASSERT_NO_THROW(
        parser.getValue(value2d)
    );
    EXPECT_EQ(56, value2d);
    short             value2e;
    ASSERT_NO_THROW(
        parser.getValue(value2e)
    );
    EXPECT_EQ(56, value2e);
    int             value2f;
    ASSERT_NO_THROW(
        parser.getValue(value2f)
    );
    EXPECT_EQ(56, value2f);
    long             value2g;
    ASSERT_NO_THROW(
        parser.getValue(value2g)
    );
    EXPECT_EQ(56, value2g);
    long long             value2h;
    ASSERT_NO_THROW(
        parser.getValue(value2h)
    );
    EXPECT_EQ(56, value2h);

    float          value3a;
    ASSERT_NO_THROW(
        parser.getValue(value3a)
    );
    EXPECT_EQ(56, value3a);
    double          value3b;
    ASSERT_NO_THROW(
        parser.getValue(value3b)
    );
    EXPECT_EQ(56, value3b);
    long double          value3c;
    ASSERT_NO_THROW(
        parser.getValue(value3c)
    );
    EXPECT_EQ(56, value3c);

    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}
TEST(YamlParserTest, getDataFromFloat)
{
    std::stringstream   stream(R"([123.56])");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_NO_THROW(
        parser.getValue(value1)
    );
    EXPECT_EQ("123.56", value1);

    short             value2a;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
    int             value2b;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
    long             value2c;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
    long long             value2d;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );
    unsigned short             value2e;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
    unsigned int             value2f;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
    unsigned long             value2g;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
    unsigned long long             value2h;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );

    float          value3a;
    ASSERT_NO_THROW(
        parser.getValue(value3a)
    );
    EXPECT_EQ(12356, static_cast<int>(value3a * 100 + .5));
    double          value3b;
    ASSERT_NO_THROW(
        parser.getValue(value3b)
    );
    EXPECT_EQ(12356, static_cast<int>(value3b * 100 + .5));
    long double          value3c;
    ASSERT_NO_THROW(
        parser.getValue(value3c)
    );
    EXPECT_EQ(12356, static_cast<int>(value3c * 100 + .5));

    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}
TEST(YamlParserTest, getDataFromBool)
{
    std::stringstream   stream(R"([true, false])");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_NO_THROW(
        parser.getValue(value1)
    );
    EXPECT_EQ("true", value1);

    short             value2a;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
    int             value2b;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
    long             value2c;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
    long long             value2d;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );
    unsigned short             value2e;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
    unsigned int             value2f;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
    unsigned long             value2g;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
    unsigned long long             value2h;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );

    float          value3a;
    ASSERT_ANY_THROW(
        parser.getValue(value3a)
    );
    double          value3b;
    ASSERT_ANY_THROW(
        parser.getValue(value3b)
    );
    long double          value3c;
    ASSERT_ANY_THROW(
        parser.getValue(value3c)
    );

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
TEST(YamlParserTest, getRawValue)
{
    std::stringstream   stream(R"([true, false, 0, 15.4, "The Best"])");
    TA::YamlParser      parser(stream);
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
    EXPECT_EQ(std::string("The Best"), value);
}

