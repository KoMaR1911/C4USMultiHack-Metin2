#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "SerUtil.h"
#include "UnicodeIterator.h"

namespace TA=ThorsAnvil::Serialize;
using TA::ParserInterface;
using TA::DeSerializer;
using TA::FormatType;

namespace CornerCaseTest
{

class ParserMock: public ParserInterface
{
    std::vector<ParserToken> const& tokens;
    std::vector<std::string> const& keys;
    std::vector<std::string> const& values;
    int nextToken;
    int nextKey;
    int nextValue;
    public:
        ParserMock(std::istream& input, std::vector<ParserToken> const& tokens,  std::vector<std::string> const& keys, std::vector<std::string> const& values)
            : ParserInterface(input, ParseType::Weak)
            , tokens(tokens)
            , keys(keys)
            , values(values)
            , nextToken(0)
            , nextKey(0)
            , nextValue(0)
        {}
        virtual FormatType formatType()                  override {return FormatType::Json;}

        virtual ParserToken     getNextToken()           override{return tokens[nextToken++];}
        virtual std::string     getKey()                 override{return keys[nextKey++];}

        virtual void    getValue(short int&)             override{}
        virtual void    getValue(int&)                   override{}
        virtual void    getValue(long int&)              override{}
        virtual void    getValue(long long int&)         override{}

        virtual void    getValue(unsigned short int&)    override{}
        virtual void    getValue(unsigned int&)          override{}
        virtual void    getValue(unsigned long int&)     override{}
        virtual void    getValue(unsigned long long int&)override{}

        virtual void    getValue(float&)                 override{}
        virtual void    getValue(double&)                override{}
        virtual void    getValue(long double&)           override{}

        virtual void    getValue(bool&)                  override{}

        virtual void    getValue(std::string& value)     override{value = values[nextValue++];}

        virtual bool    isValueNull()                    override{return false;}

        virtual std::string getRawValue()                override{return "";}
};

}

TEST(CornerCaseTest, IgnoreTheArrayUnexpectedKey)
{
    std::stringstream           stream;
    std::vector<std::string>    keys    {"Ignore"};
    std::vector<std::string>    values;
    std::vector<ParserInterface::ParserToken>    tokens
    {   ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
                ParserInterface::ParserToken::Key,  // Key
                    ParserInterface::ParserToken::ArrayStart,
                        ParserInterface::ParserToken::Key,   /* Don't expect a Key in Array */
                    ParserInterface::ParserToken::ArrayEnd,
            ParserInterface::ParserToken::MapEnd,
        ParserInterface::ParserToken::DocEnd
    };
    CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
    DeSerializer    deSerializer(parser);


    SerializeTest::CornerCaseClass     value;
    EXPECT_THROW(
        deSerializer.parse(value),
        std::runtime_error
    );
}
TEST(CornerCaseTest, IgnoreTheArrayUnexpectedMapEnd)
{
    std::stringstream           stream;
    std::vector<std::string>    keys    {"Ignore"};
    std::vector<std::string>    values;
    std::vector<ParserInterface::ParserToken>    tokens
    {   ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
                ParserInterface::ParserToken::Key,  // Key
                    ParserInterface::ParserToken::ArrayStart,
                        ParserInterface::ParserToken::MapEnd,   /* Don't expect a MapEnd in Array */
                    ParserInterface::ParserToken::ArrayEnd,
            ParserInterface::ParserToken::MapEnd,
        ParserInterface::ParserToken::DocEnd
    };
    CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
    DeSerializer    deSerializer(parser);


    SerializeTest::CornerCaseClass     value;
    EXPECT_THROW(
        deSerializer.parse(value),
        std::runtime_error
    );
}
TEST(CornerCaseTest, IgnoreTheArrayUnexpectedInvalidValue)
{
    std::stringstream           stream;
    std::vector<std::string>    keys    {"Ignore"};
    std::vector<std::string>    values;
    std::vector<ParserInterface::ParserToken>    tokens
    {   ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
                ParserInterface::ParserToken::Key,  // Key
                    ParserInterface::ParserToken::ArrayStart,
                        ((ParserInterface::ParserToken)32762),   /* Don't expect a Invalid in Array */
                    ParserInterface::ParserToken::ArrayEnd,
            ParserInterface::ParserToken::MapEnd,
        ParserInterface::ParserToken::DocEnd
    };
    CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
    DeSerializer    deSerializer(parser);


    SerializeTest::CornerCaseClass     value;
    EXPECT_THROW(
        deSerializer.parse(value),
        std::runtime_error
    );
}
TEST(CornerCaseTest, IgnoreTheValueUnexpectedKey)
{
    std::stringstream           stream;
    std::vector<std::string>    keys    {"Ignore"};
    std::vector<std::string>    values;
    std::vector<ParserInterface::ParserToken>    tokens
    {   ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
                ParserInterface::ParserToken::Key,  // Key
                ParserInterface::ParserToken::Key,  /* Don't expect a key after a key */
            ParserInterface::ParserToken::MapEnd,
        ParserInterface::ParserToken::DocEnd
    };
    CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
    DeSerializer    deSerializer(parser);


    SerializeTest::CornerCaseClass     value;
    EXPECT_THROW(
        deSerializer.parse(value),
        std::runtime_error
    );
}
TEST(CornerCaseTest, IgnoreTheValueUnexpectedMapEnd)
{
    std::stringstream           stream;
    std::vector<std::string>    keys    {"Ignore"};
    std::vector<std::string>    values;
    std::vector<ParserInterface::ParserToken>    tokens
    {   ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
                ParserInterface::ParserToken::Key,  // Key
                ParserInterface::ParserToken::MapEnd,  /* Don't expect a MapEnd after a key */
            ParserInterface::ParserToken::MapEnd,
        ParserInterface::ParserToken::DocEnd
    };
    CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
    DeSerializer    deSerializer(parser);


    SerializeTest::CornerCaseClass     value;
    EXPECT_THROW(
        deSerializer.parse(value),
        std::runtime_error
    );
}
TEST(CornerCaseTest, IgnoreTheValueUnexpectedArrayEnd)
{
    std::stringstream           stream;
    std::vector<std::string>    keys    {"Ignore"};
    std::vector<std::string>    values;
    std::vector<ParserInterface::ParserToken>    tokens
    {   ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
                ParserInterface::ParserToken::Key,  // Key
                ParserInterface::ParserToken::ArrayEnd,  /* Don't expect an ArrayEnd after a key */
            ParserInterface::ParserToken::MapEnd,
        ParserInterface::ParserToken::DocEnd
    };
    CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
    DeSerializer    deSerializer(parser);


    SerializeTest::CornerCaseClass     value;
    EXPECT_THROW(
        deSerializer.parse(value),
        std::runtime_error
    );
}
TEST(CornerCaseTest, IgnoreTheValueUnexpectedInvalidValue)
{
    std::stringstream           stream;
    std::vector<std::string>    keys    {"Ignore"};
    std::vector<std::string>    values;
    std::vector<ParserInterface::ParserToken>    tokens
    {   ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
                ParserInterface::ParserToken::Key,  // Key
                ((ParserInterface::ParserToken)32762),   /* Don't expect a Invalid after a Key */
            ParserInterface::ParserToken::MapEnd,
        ParserInterface::ParserToken::DocEnd
    };
    CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
    DeSerializer    deSerializer(parser);


    SerializeTest::CornerCaseClass     value;
    EXPECT_THROW(
        deSerializer.parse(value),
        std::runtime_error
    );
}
TEST(CornerCaseTest, DeSerializerNoDocStart)
{
    auto test = []()
    {
        std::stringstream           stream;
        std::vector<std::string>    keys;
        std::vector<std::string>    values;
        std::vector<ParserInterface::ParserToken>    tokens
        {
            // Missing DocStart
            ParserInterface::ParserToken::MapStart,
            ParserInterface::ParserToken::MapEnd,
            ParserInterface::ParserToken::DocEnd
        };
        CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
        DeSerializer    deSerializer(parser);

        SerializeTest::CornerCaseClass     value;
        deSerializer.parse(value);
    };

    EXPECT_THROW(
        test(),
        std::runtime_error
    );
}
TEST(CornerCaseTest, DeSerializerNoDocEnd)
{
    auto test = [](){
        std::stringstream           stream;
        std::vector<std::string>    keys;
        std::vector<std::string>    values;
        std::vector<ParserInterface::ParserToken>    tokens
        {
            ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
            ParserInterface::ParserToken::MapEnd,
            // Missing Doc End
        };
        CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
        DeSerializer    deSerializer(parser);

        SerializeTest::CornerCaseClass     value;
        deSerializer.parse(value);
    };
    EXPECT_THROW(
        test(),
        std::runtime_error
    );
}
TEST(CornerCaseTest, DeSerializationForBlock_Struct_Constructor)
{
    auto test = [](){
        std::stringstream           stream;
        std::vector<std::string>    keys;
        std::vector<std::string>    values;
        std::vector<ParserInterface::ParserToken>    tokens
        {
            ParserInterface::ParserToken::DocStart,
            // Missing MapStart
            ParserInterface::ParserToken::MapEnd,
            ParserInterface::ParserToken::DocEnd,
        };
        CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
        DeSerializer    deSerializer(parser);

        SerializeTest::CornerCaseClass     value;
        deSerializer.parse(value);
    };
    EXPECT_THROW(
        test(),
        std::runtime_error
    );
}
TEST(CornerCaseTest, DeSerializationForBlock_Struct_HasMoreValue)
{
    auto test = [](){
        std::stringstream           stream;
        std::vector<std::string>    keys;
        std::vector<std::string>    values;
        std::vector<ParserInterface::ParserToken>    tokens
        {
            ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
            ParserInterface::ParserToken::Value,    // Not a key
            ParserInterface::ParserToken::MapEnd,
            ParserInterface::ParserToken::DocEnd,
        };
        CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
        DeSerializer    deSerializer(parser);

        SerializeTest::CornerCaseClass     value;
        deSerializer.parse(value);
    };
    EXPECT_THROW(
        test(),
        std::runtime_error
    );
}
TEST(CornerCaseTest, DeSerializationForBlock_Value_ScanObject)
{
    auto test = [](){
        std::stringstream           stream;
        std::vector<std::string>    keys{"value"};
        std::vector<std::string>    values;
        std::vector<ParserInterface::ParserToken>    tokens
        {
            ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
            ParserInterface::ParserToken::Key,      // Key -> "value" Expecting an ParserToken::Value next
            ParserInterface::ParserToken::MapStart,
            ParserInterface::ParserToken::MapEnd,
            ParserInterface::ParserToken::MapEnd,
            ParserInterface::ParserToken::DocEnd,
        };
        CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
        DeSerializer    deSerializer(parser);

        SerializeTest::CornerCaseClass     value;
        deSerializer.parse(value);
    };
    EXPECT_THROW(
        test(),
        std::runtime_error
    );
}
TEST(CornerCaseTest, TryParsePolyMorphicObject_NotMap)
{
    auto test = [](){
        std::stringstream           stream;
        std::vector<std::string>    keys{"__type", "Type"};
        std::vector<std::string>    values{"CornerCaseClass", "15"};
        std::vector<ParserInterface::ParserToken>    tokens
        {
            ParserInterface::ParserToken::DocStart,
            // ParserInterface::ParserToken::MapStart,  // Missing Map Start
            ParserInterface::ParserToken::Key,
            ParserInterface::ParserToken::Value,
            ParserInterface::ParserToken::Key,
            ParserInterface::ParserToken::Value,
            ParserInterface::ParserToken::MapEnd,
            ParserInterface::ParserToken::DocEnd,
        };
        CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
        DeSerializer    deSerializer(parser);

        SerializeTest::CornerCaseClass*    value = nullptr;
        deSerializer.parse(value);
    };
    EXPECT_THROW(
        test(),
        std::runtime_error
    );
}
TEST(CornerCaseTest, TryParsePolyMorphicObject_MapNoKey)
{
    auto test = [](){
        std::stringstream           stream;
        std::vector<std::string>    keys{"__type", "Type"};
        std::vector<std::string>    values{"CornerCaseClass", "15"};
        std::vector<ParserInterface::ParserToken>    tokens
        {
            ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
            // ParserInterface::ParserToken::Key,   // Missing Key
            ParserInterface::ParserToken::Value,
            ParserInterface::ParserToken::Key,
            ParserInterface::ParserToken::Value,
            ParserInterface::ParserToken::MapEnd,
            ParserInterface::ParserToken::DocEnd,
        };
        CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
        DeSerializer    deSerializer(parser);

        SerializeTest::CornerCaseClass*    value = nullptr;
        deSerializer.parse(value);
    };
    EXPECT_THROW(
        test(),
        std::runtime_error
    );
}
TEST(CornerCaseTest, TryParsePolyMorphicObject_MapKeyNot_Type)
{
    auto test = [](){
        std::stringstream           stream;
        std::vector<std::string>    keys{"__typeXX", "Type"};   // Type incorrect
        std::vector<std::string>    values{"CornerCaseClass", "15"};
        std::vector<ParserInterface::ParserToken>    tokens
        {
            ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
            ParserInterface::ParserToken::Key,
            ParserInterface::ParserToken::Value,
            ParserInterface::ParserToken::Key,
            ParserInterface::ParserToken::Value,
            ParserInterface::ParserToken::MapEnd,
            ParserInterface::ParserToken::DocEnd,
        };
        CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
        DeSerializer    deSerializer(parser);

        SerializeTest::CornerCaseClass*    value = nullptr;
        deSerializer.parse(value);
    };
    EXPECT_THROW(
        test(),
        std::runtime_error
    );
}
TEST(CornerCaseTest, TryParsePolyMorphicObject_MapKeyNotValue)
{
    auto test = [](){
        std::stringstream           stream;
        std::vector<std::string>    keys{"__type", "Type"};
        std::vector<std::string>    values{"CornerCaseClass", "15"};
        std::vector<ParserInterface::ParserToken>    tokens
        {
            ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
            ParserInterface::ParserToken::Key,
            ParserInterface::ParserToken::MapStart, // Needs to be a value (to get string and type name)
            ParserInterface::ParserToken::MapEnd,
            ParserInterface::ParserToken::Key,
            ParserInterface::ParserToken::Value,
            ParserInterface::ParserToken::MapEnd,
            ParserInterface::ParserToken::DocEnd,
        };
        CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
        DeSerializer    deSerializer(parser);

        SerializeTest::CornerCaseClass*    value = nullptr;
        deSerializer.parse(value);
    };
    EXPECT_THROW(
        test(),
        std::runtime_error
    );
}
TEST(CornerCaseTest, TryParsePolyMorphicObject_MapKeyValueBadType)
{
    auto test = [](){
        std::stringstream           stream;
        std::vector<std::string>    keys{"__type", "Type"};
        std::vector<std::string>    values{"CornerCaseClass_XX", "15"}; // Bad Class Name
        std::vector<ParserInterface::ParserToken>    tokens
        {
            ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
            ParserInterface::ParserToken::Key,
            ParserInterface::ParserToken::Value,
            ParserInterface::ParserToken::Key,
            ParserInterface::ParserToken::Value,
            ParserInterface::ParserToken::MapEnd,
            ParserInterface::ParserToken::DocEnd,
        };
        CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
        DeSerializer    deSerializer(parser);

        SerializeTest::CornerCaseClass*    value = nullptr;
        deSerializer.parse(value);
    };
    EXPECT_THROW(
        test(),
        std::runtime_error
    );
}

namespace SerializeTest
{
enum    CornerCaseEnum {Enum1, Enum2, Enum3};
}
ThorsAnvil_MakeEnum(SerializeTest::CornerCaseEnum, Enum1, Enum2, Enum3);
TEST(CornerCaseTest, DeSerializationForBlock_Enum_Constructor)
{
    auto test = [](){
        std::stringstream           stream;
        std::vector<std::string>    keys;
        std::vector<std::string>    values;
        std::vector<ParserInterface::ParserToken>    tokens
        {
            ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart, // Should be Value for enum
            ParserInterface::ParserToken::MapEnd,
            ParserInterface::ParserToken::DocEnd,
        };
        CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
        DeSerializer    deSerializer(parser);

        SerializeTest::CornerCaseEnum     value;
        deSerializer.parse(value);
    };
    EXPECT_THROW(
        test(),
        std::runtime_error
    );
}

TEST(CornerCaseTest, DeSerializationForBlock_Array_Constructor)
{
    auto test = [](){
        std::stringstream           stream;
        std::vector<std::string>    keys;
        std::vector<std::string>    values;
        std::vector<ParserInterface::ParserToken>    tokens
        {
            ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::Value, // Should be ArrayStart for Array
            ParserInterface::ParserToken::DocEnd,
        };
        CornerCaseTest::ParserMock      parser(stream, tokens, keys, values);
        DeSerializer    deSerializer(parser);

        std::vector<int>     value;
        deSerializer.parse(value);
    };
    EXPECT_THROW(
        test(),
        std::runtime_error
    );
}

TEST(CornerCaseTest, ConvertHexToDec_InvalidCharacter)
{
    EXPECT_THROW(
        ThorsAnvil::Serialize::convertHexToDec('G'),
        std::runtime_error
    );
    EXPECT_THROW(
        ThorsAnvil::Serialize::convertHexToDec('g'),
        std::runtime_error
    );
    EXPECT_THROW(
        ThorsAnvil::Serialize::convertHexToDec('@'),
        std::runtime_error
    );
    EXPECT_THROW(
        ThorsAnvil::Serialize::convertHexToDec('`'),
        std::runtime_error
    );
    EXPECT_THROW(
        ThorsAnvil::Serialize::convertHexToDec('/'),
        std::runtime_error
    );
    EXPECT_THROW(
        ThorsAnvil::Serialize::convertHexToDec(':'),
        std::runtime_error
    );
}

TEST(CornerCaseTest, UnicodePushBackIterator_SlashSlash)
{
    using ThorsAnvil::Serialize::UnicodePushBackIterator;
    using ThorsAnvil::Serialize::make_UnicodePushBackIterator;

    std::string                 stream;
    auto                        iter = make_UnicodePushBackIterator(stream);

    iter    = '\\';     ++iter;
    iter    = '\\';     ++iter;

    EXPECT_EQ(stream, R"(\)");
}
TEST(CornerCaseTest, UnicodePushBackIterator_BackSlashBackSlash)
{
    using ThorsAnvil::Serialize::UnicodePushBackIterator;
    using ThorsAnvil::Serialize::make_UnicodePushBackIterator;

    std::string                 stream;
    auto                        iter = make_UnicodePushBackIterator(stream);

    iter    = '\\';     ++iter;
    iter    = '/';     ++iter;

    EXPECT_EQ(stream, R"(/)");
}

// https://www.charbase.com/1d11e-unicode-musical-symbol-g-clef
// Surrogate Pair:  d834 dd1e
// UTF-8:           f0 9d 84 9e
TEST(CornerCaseTest, UnicodePushBackIterator_SurogatePair)
{
    using ThorsAnvil::Serialize::UnicodePushBackIterator;
    using ThorsAnvil::Serialize::make_UnicodePushBackIterator;

    std::string                 stream;
    auto                        iter = make_UnicodePushBackIterator(stream);

    iter    = '\\';     ++iter;
    iter    = 'u';      ++iter;
    iter    = 'd';      ++iter;
    iter    = '8';      ++iter;
    iter    = '3';      ++iter;
    iter    = '4';      ++iter;

    iter    = '\\';     ++iter;
    iter    = 'u';      ++iter;
    iter    = 'd';      ++iter;
    iter    = 'd';      ++iter;
    iter    = '1';      ++iter;
    iter    = 'e';      ++iter;

    // Should now be UTF-8 encoded.
    ASSERT_EQ(4, stream.size());
    EXPECT_EQ('\xf0', stream[0]);
    EXPECT_EQ('\x9d', stream[1]);
    EXPECT_EQ('\x84', stream[2]);
    EXPECT_EQ('\x9e', stream[3]);
}
TEST(CornerCaseTest, UnicodePushBackIterator_SurogatePair_SecondNotValid)
{
    using ThorsAnvil::Serialize::UnicodePushBackIterator;
    using ThorsAnvil::Serialize::make_UnicodePushBackIterator;

    std::string                 stream;
    auto                        iter = make_UnicodePushBackIterator(stream);

    iter    = '\\';     ++iter;
    iter    = 'u';      ++iter;
    iter    = 'd';      ++iter;
    iter    = '8';      ++iter;
    iter    = '3';      ++iter;
    iter    = '4';      ++iter;

    // Should be R"(\udd1e)"
    EXPECT_THROW(
        iter    = 'a',
        std::runtime_error
    );
}
TEST(CornerCaseTest, UnicodePushBackIterator_SurogatePair_SecondNotValid_P2)
{
    using ThorsAnvil::Serialize::UnicodePushBackIterator;
    using ThorsAnvil::Serialize::make_UnicodePushBackIterator;

    std::string                 stream;
    auto                        iter = make_UnicodePushBackIterator(stream);

    iter    = '\\';     ++iter;
    iter    = 'u';      ++iter;
    iter    = 'd';      ++iter;
    iter    = '8';      ++iter;
    iter    = '3';      ++iter;
    iter    = '4';      ++iter;

    iter    = '\\';     ++iter;
    // Should be R"(\udd1e)"
    EXPECT_THROW(
        iter    = '\\',
        std::runtime_error
    );
}
TEST(CornerCaseTest, UnicodePushBackIterator_SurogatePair_SecondNotValid_P3)
{
    using ThorsAnvil::Serialize::UnicodePushBackIterator;
    using ThorsAnvil::Serialize::make_UnicodePushBackIterator;

    std::string                 stream;
    auto                        iter = make_UnicodePushBackIterator(stream);

    iter    = '\\';     ++iter;
    iter    = 'u';      ++iter;
    iter    = 'd';      ++iter;
    iter    = '8';      ++iter;
    iter    = '3';      ++iter;
    iter    = '4';      ++iter;

    // Should be R"(\udd1e)"
    iter    = '\\';     ++iter;
    iter    = 'u';      ++iter;
    iter    = '1';      ++iter; // 1 is not in the correct range
    iter    = 'd';      ++iter;
    iter    = '1';      ++iter;

    EXPECT_THROW(
        iter    = 'e',
        std::runtime_error
    );
}
// #####
TEST(CornerCaseTest, UnicodeWrapperIterator_SlashSlash)
{
    using ThorsAnvil::Serialize::UnicodeWrapperIterator;
    using ThorsAnvil::Serialize::make_UnicodeWrapperIterator;

    std::string                 stream(R"("\\")");;
    auto                        loop  = make_UnicodeWrapperIterator(std::begin(stream));

    char    value = *loop;
    EXPECT_EQ(value, '\\');
}
TEST(CornerCaseTest, UnicodeWrapperIterator_BackSlashBackSlash)
{
    using ThorsAnvil::Serialize::UnicodeWrapperIterator;
    using ThorsAnvil::Serialize::make_UnicodeWrapperIterator;

    std::string                 stream(R"("\/")");;
    auto                        loop  = make_UnicodeWrapperIterator(std::begin(stream));

    char    value = *loop;
    EXPECT_EQ(value, '/');
}
TEST(CornerCaseTest, UnicodeWrapperIterator_SlashK)
{
    using ThorsAnvil::Serialize::UnicodeWrapperIterator;
    using ThorsAnvil::Serialize::make_UnicodeWrapperIterator;

    std::string                 stream(R"("\k")");;
    auto                        loop  = make_UnicodeWrapperIterator(std::begin(stream));

    EXPECT_THROW(
        *loop,
        std::runtime_error
    );
}

// https://www.charbase.com/1d11e-unicode-musical-symbol-g-clef
// Surrogate Pair:  d834 dd1e
// UTF-8:           f0 9d 84 9e
TEST(CornerCaseTest, UnicodeWrapperIterator_SurogatePair)
{
    using ThorsAnvil::Serialize::UnicodeWrapperIterator;
    using ThorsAnvil::Serialize::make_UnicodeWrapperIterator;

    std::string                 stream(R"("\ud834\udd1e")");
    auto                        loop  = make_UnicodeWrapperIterator(std::begin(stream));

    EXPECT_EQ('\xf0', *loop);   ++loop;
    EXPECT_EQ('\x9d', *loop);   ++loop;
    EXPECT_EQ('\x84', *loop);   ++loop;
    EXPECT_EQ('\x9e', *loop);   ++loop;
}
TEST(CornerCaseTest, UnicodeWrapperIterator_SurogatePair_SecondNotValid)
{
    using ThorsAnvil::Serialize::UnicodeWrapperIterator;
    using ThorsAnvil::Serialize::make_UnicodeWrapperIterator;

    std::string                 stream(R"("\ud834a")");
    auto                        loop  = make_UnicodeWrapperIterator(std::begin(stream));

    // Should be R"(\udd1e)"
    //EXPECT_EQ('\xf0', *loop);   ++loop;
    //EXPECT_EQ('\x9d', *loop);   ++loop;
    //EXPECT_EQ('\x84', *loop);   ++loop;
    //EXPECT_EQ('\x9e', *loop);   ++loop;
    EXPECT_THROW(
        *loop,
        std::runtime_error
    );
}
TEST(CornerCaseTest, UnicodeWrapperIterator_SurogatePair_SecondNotValid_P2)
{
    using ThorsAnvil::Serialize::UnicodeWrapperIterator;
    using ThorsAnvil::Serialize::make_UnicodeWrapperIterator;

    std::string                 stream(R"("\ud834\\")");
    auto                        loop  = make_UnicodeWrapperIterator(std::begin(stream));

    //EXPECT_EQ('\xf0', *loop);   ++loop;
    //EXPECT_EQ('\x9d', *loop);   ++loop;
    //EXPECT_EQ('\x84', *loop);   ++loop;
    //EXPECT_EQ('\x9e', *loop);   ++loop;
    EXPECT_THROW(
        *loop,
        std::runtime_error
    );
}
TEST(CornerCaseTest, UnicodeWrapperIterator_SurogatePair_SecondNotValid_P3)
{
    using ThorsAnvil::Serialize::UnicodeWrapperIterator;
    using ThorsAnvil::Serialize::make_UnicodeWrapperIterator;

    std::string                 stream(R"("\ud834\u1d1e")");
    auto                        loop  = make_UnicodeWrapperIterator(std::begin(stream));

    //EXPECT_EQ('\xf0', *loop);   ++loop;
    //EXPECT_EQ('\x9d', *loop);   ++loop;
    //EXPECT_EQ('\x84', *loop);   ++loop;
    //EXPECT_EQ('\x9e', *loop);   ++loop;
    EXPECT_THROW(
        *loop,
        std::runtime_error
    );
}

