#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonManualLexer.h"
#include "JsonLexemes.h"

using ThorsAnvil::Serialize::JsonManualLexer;

TEST(LexerTest, JsonArrayTokens)
{
    std::stringstream   stream("[],");
    JsonManualLexer     lexer(stream);

    EXPECT_EQ('[',   lexer.yylex());
    EXPECT_EQ(']',   lexer.yylex());
    EXPECT_EQ(',',   lexer.yylex());
}
TEST(LexerTest, JsonMapTokens)
{
    std::stringstream   stream("{}:,");
    JsonManualLexer     lexer(stream);

    EXPECT_EQ('{',   lexer.yylex());
    EXPECT_EQ('}',   lexer.yylex());
    EXPECT_EQ(':',   lexer.yylex());
    EXPECT_EQ(',',   lexer.yylex());
}
TEST(LexerTest, JsonValueTokens)
{
    std::stringstream   stream(R"("Test" 456 789.123 true false null)");
    JsonManualLexer     lexer(stream);

    EXPECT_EQ(ThorsAnvil::Serialize::JSON_STRING,  lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_NUMBER,  lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_NUMBER,  lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_TRUE,    lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_FALSE,   lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_NULL,    lexer.yylex());
    lexer.getRawString();
}

