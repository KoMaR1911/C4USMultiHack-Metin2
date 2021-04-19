#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "UnicodeIterator.h"
#include <algorithm>

using namespace ThorsAnvil::Serialize;

TEST(UnicodeIteratorTest, NormalCharacters)
{
    std::string     input(R"("This is a normal string that should not change")");
    std::string     output(make_UnicodeWrapperIterator(std::begin(input)), make_EndUnicodeWrapperIterator(std::end(input)));
    EXPECT_EQ("This is a normal string that should not change", output);
}
TEST(UnicodeIteratorTest, StandardEscape)
{
    std::string     input(R"("\"\\\b\f\n\r\t")");
    std::string     output(make_UnicodeWrapperIterator(std::begin(input)), make_EndUnicodeWrapperIterator(std::end(input)));
    EXPECT_EQ("\"\\\b\f\n\r\t", output);
}
TEST(UnicodeIteratorTest, Unicode1Byte)
{
    std::string     input(R"("\u006f\u004E")");
    std::string     output(make_UnicodeWrapperIterator(std::begin(input)), make_EndUnicodeWrapperIterator(std::end(input)));
    EXPECT_EQ("oN", output);
}
TEST(UnicodeIteratorTest, Unicode2Byte)
{
    std::string     input(R"("\u0102\u011D\u013d")");
    std::string     output(make_UnicodeWrapperIterator(std::begin(input)), make_EndUnicodeWrapperIterator(std::end(input)));
    EXPECT_EQ("ĂĝĽ", output);
}
TEST(UnicodeIteratorTest, Unicode3Byte)
{
    std::string     input(R"("\u0967\u0995\u097f")");
    std::string     output(make_UnicodeWrapperIterator(std::begin(input)), make_EndUnicodeWrapperIterator(std::end(input)));
    EXPECT_EQ("१কॿ", output);
}
TEST(UnicodeIteratorTest, UnicodeSurrogatePairs)
{
    std::string     input(R"("\uD80C\uDC00")");
    std::string     output(make_UnicodeWrapperIterator(std::begin(input)), make_EndUnicodeWrapperIterator(std::end(input)));
    // 0xF0 0x93 0x80 0x80  (UTF-8) => 0x00013000 (UTF-32) => 0xD80C 0xDC00 (UTF-16)
    // http://www.fileformat.info/info/unicode/char/13000/index.htm
    EXPECT_EQ("\xF0\x93\x80\x80", output);
}

TEST(UnicodeIteratorTest, PushNormalCharacters)
{
    std::string     input("This is a normal string that should not change");
    std::string     output;
    std::copy(std::begin(input), std::end(input), make_UnicodePushBackIterator(output));
    EXPECT_EQ(input, output);
}
TEST(UnicodeIteratorTest, PushStandardEscape)
{
    std::string     input(R"(\"\\\b\f\n\r\t)");
    std::string     output;
    std::copy(std::begin(input), std::end(input), make_UnicodePushBackIterator(output));
    EXPECT_EQ("\"\\\b\f\n\r\t", output);
}
TEST(UnicodeIteratorTest, PushUnicode1Byte)
{
    std::string     input(R"(\u006f\u004E)");
    std::string     output;
    std::copy(std::begin(input), std::end(input), make_UnicodePushBackIterator(output));
    EXPECT_EQ("oN", output);
}
TEST(UnicodeIteratorTest, PushUnicode2Byte)
{
    std::string     input(R"(\u0102\u011D\u013d)");
    std::string     output;
    std::copy(std::begin(input), std::end(input), make_UnicodePushBackIterator(output));
    EXPECT_EQ("ĂĝĽ", output);
}
TEST(UnicodeIteratorTest, PushUnicode3Byte)
{
    std::string     input(R"(\u0967\u0995\u097f)");
    std::string     output;
    std::copy(std::begin(input), std::end(input), make_UnicodePushBackIterator(output));
    EXPECT_EQ("१কॿ", output);
}
TEST(UnicodeIteratorTest, PushUnicodeSurrogatePairs)
{
    std::string     input(R"(\uD80C\uDC00)");
    std::string     output;
    std::copy(std::begin(input), std::end(input), make_UnicodePushBackIterator(output));
    // 0xF0 0x93 0x80 0x80  (UTF-8) => 0x00013000 (UTF-32) => 0xD80C 0xDC00 (UTF-16)
    // http://www.fileformat.info/info/unicode/char/13000/index.htm
    EXPECT_EQ("\xF0\x93\x80\x80", output);
}

