#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include <sstream>
#include "test/ExceptionTest.h"


TEST(ExceptionWhilePrintingTest, JsonNormalPrint)
{
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(false, 15);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::jsonExporter(obj, false);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::goodbit);
    EXPECT_EQ(stream.str(), " 15");
}


TEST(ExceptionWhilePrintingTest, JsonNormalPrintCatchEnabled)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(false, 16);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::jsonExporter(obj, PrinterInterface::OutputType::Default);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::goodbit);
    EXPECT_EQ(stream.str(), " 16");
}

TEST(ExceptionWhilePrintingTest, JsonThrowPrint)
{
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(true, 17);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::jsonExporter(obj, false);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, true);
    EXPECT_EQ(state, std::ios::failbit);
}


TEST(ExceptionWhilePrintingTest, JsonThrowPrintCatchEnabled)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(true, 18);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::jsonExporter(obj, PrinterInterface::OutputType::Default);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::failbit);
}


TEST(ExceptionWhilePrintingTest, JsonNormalStream)
{
    std::stringstream   stream(R"(19 "Data")");
    ExceptionTest::ThrowablePrint      obj(false,1);
    bool                thrown = false;

    try
    {
        stream >> ThorsAnvil::Serialize::jsonImporter(obj, false);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::goodbit);
    EXPECT_EQ(obj.val, 19);
}


TEST(ExceptionWhilePrintingTest, JsonNormalStreamCatchEnabled)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream   stream(R"(20 "Data")");
    ExceptionTest::ThrowablePrint      obj(false, 2);
    bool                thrown = false;

    try
    {
        stream >> ThorsAnvil::Serialize::jsonImporter(obj, ParserInterface::ParseType::Weak);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::goodbit);
    EXPECT_EQ(obj.val, 20);
}

TEST(ExceptionWhilePrintingTest, JsonThrowStream)
{
    std::stringstream   stream("21");
    ExceptionTest::ThrowablePrint      obj(true, 3);
    bool                thrown = false;

    try
    {
        stream >> ThorsAnvil::Serialize::jsonImporter(obj, false);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, true);
    EXPECT_EQ(state, std::ios::eofbit | std::ios::failbit);
}


TEST(ExceptionWhilePrintingTest, JsonThrowStreamCatchEnabled)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream   stream("22");
    ExceptionTest::ThrowablePrint      obj(true, 4);
    bool                thrown = false;

    try
    {
        stream >> ThorsAnvil::Serialize::jsonImporter(obj, ParserInterface::ParseType::Weak);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::eofbit | std::ios::failbit);
}


TEST(ExceptionWhilePrintingTest, BsonNormalPrint)
{
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(false, 15);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::bsonExporter(obj, false);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::goodbit);

    static const char expectedRaw[]
                = "\x0F\x00\x00\x00"
                  "\x05"  "0\x00"  "\x02\x00\x00\x00" "\x80" "15"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(stream.str(), expected);
}


TEST(ExceptionWhilePrintingTest, BsonNormalPrintCatchEnabled)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(false, 16);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::bsonExporter(obj, PrinterInterface::OutputType::Default);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::goodbit);
    static const char expectedRaw[]
                = "\x0F\x00\x00\x00"
                  "\x05"  "0\x00"  "\x02\x00\x00\x00" "\x80" "16"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(stream.str(), expected);
}

TEST(ExceptionWhilePrintingTest, BsonThrowPrint)
{
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(true, 17);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::bsonExporter(obj, false);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, true);
    EXPECT_EQ(state, std::ios::failbit);
}


TEST(ExceptionWhilePrintingTest, BsonThrowPrintCatchEnabled)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(true, 18);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::bsonExporter(obj, PrinterInterface::OutputType::Default);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::failbit);
}


TEST(ExceptionWhilePrintingTest, BsonNormalStream)
{
    static const char inputRaw[]
                = "\x16\x00\x00\x00"
                  "\x05"  "0\x00"  "\x09\x00\x00\x00" "\x80" "19 \"Data\""
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ExceptionTest::ThrowablePrint      obj(false,1);
    bool                thrown = false;

    try
    {
        stream >> ThorsAnvil::Serialize::bsonImporter(obj, false);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::goodbit);
    EXPECT_EQ(obj.val, 19);
}


TEST(ExceptionWhilePrintingTest, BsonNormalStreamCatchEnabled)
{
    using ThorsAnvil::Serialize::ParserInterface;
    static const char inputRaw[]
                = "\x16\x00\x00\x00"
                  "\x05"  "0\x00"  "\x09\x00\x00\x00" "\x80" "20 \"Done\""
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ExceptionTest::ThrowablePrint      obj(false, 2);
    bool                thrown = false;

    try
    {
        stream >> ThorsAnvil::Serialize::bsonImporter(obj, ParserInterface::ParseType::Weak);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::goodbit);
    EXPECT_EQ(obj.val, 20);
}

TEST(ExceptionWhilePrintingTest, BsonThrowStream)
{
    static const char inputRaw[]
                = "\x0F\x00\x00\x00"
                  "\x05"  "0\x00"  "\x02\x00\x00\x00" "\x80" "21"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ExceptionTest::ThrowablePrint      obj(true, 3);
    bool                thrown = false;

    try
    {
        stream >> ThorsAnvil::Serialize::bsonImporter(obj, false);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, true);
    EXPECT_EQ(state, std::ios::failbit);
}


TEST(ExceptionWhilePrintingTest, BsonThrowStreamCatchEnabled)
{
    using ThorsAnvil::Serialize::ParserInterface;
    static const char inputRaw[]
                = "\x0F\x00\x00\x00"
                  "\x05"  "0\x00"  "\x02\x00\x00\x00" "\x80" "22"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ExceptionTest::ThrowablePrint      obj(true, 4);
    bool                thrown = false;

    try
    {
        stream >> ThorsAnvil::Serialize::bsonImporter(obj, ParserInterface::ParseType::Weak);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::failbit);
}

