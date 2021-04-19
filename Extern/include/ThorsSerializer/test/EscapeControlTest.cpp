#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include <sstream>
#include <string>
#include <string_view>


TEST(EscapeControlTest, JsonNormalInput)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream   input("\"String With no special characters\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParserInterface::ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, true);
}
TEST(EscapeControlTest, JsonInputContainsTab)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream   input("\"\t A string with A tab\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParserInterface::ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(EscapeControlTest, JsonInputContainsBS)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream   input("\"\b A string with A Back Space\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParserInterface::ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(EscapeControlTest, JsonInputContainsNL)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream   input("\"\n A string with A New Line\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParserInterface::ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(EscapeControlTest, JsonInputContainsFF)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream   input("\"\f A string with A Form Feed\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParserInterface::ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(EscapeControlTest, JsonInputContainsCR)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream   input("\"\r A string with A Carridge Return\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParserInterface::ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(EscapeControlTest, JsonOutputContainsTab)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         value("\t A string with A tab");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExporter(value, PrinterInterface::OutputType::Default)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(output.str().find('\t'), std::string::npos);
    auto find = output.str().find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(output.str()[find+1], 't');
}
TEST(EscapeControlTest, JsonOutputContainsBS)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         value("\b A string with A Back Space");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExporter(value, PrinterInterface::OutputType::Default)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(output.str().find('\t'), std::string::npos);
    auto find = output.str().find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(output.str()[find+1], 'b');
}
TEST(EscapeControlTest, JsonOutputContainsNL)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         value("\n A string with A New Line");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExporter(value, PrinterInterface::OutputType::Default)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(output.str().find('\t'), std::string::npos);
    auto find = output.str().find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(output.str()[find+1], 'n');
}
TEST(EscapeControlTest, JsonOutputContainsFF)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         value("\f A string with A Form Feed");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExporter(value, PrinterInterface::OutputType::Default)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(output.str().find('\t'), std::string::npos);
    auto find = output.str().find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(output.str()[find+1], 'f');
}
TEST(EscapeControlTest, JsonOutputContainsCR)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         value("\r A string with A Carridge Return");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExporter(value, PrinterInterface::OutputType::Default)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(output.str().find('\t'), std::string::npos);
    auto find = output.str().find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(output.str()[find+1], 'r');
}

TEST(EscapeControlTest, BsonNormalInput)
{
    using ThorsAnvil::Serialize::ParserInterface;
    //std::stringstream   input("\"String With no special characters\"");
    static const char inputRaw[]
                = "\x2E\x00\x00\x00"
                  "\x02" "0\x00" "\x22\x00\x00\x00" "String With no special characters\x00"
                  "\x00";
    std::string inputString(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream input(inputString);
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::bsonImporter(value, ParserInterface::ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, true);
}
TEST(EscapeControlTest, BsonOutputContainsTab)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         value("\t A string with A tab");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::bsonExporter(value, PrinterInterface::OutputType::Default)) {
        exportDone = true;
    }
    std::string_view outputView((&*output.str().begin()) + 11 , std::size(value));
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(outputView.find('\t'), std::string::npos);
    auto find = outputView.find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(outputView[find+1], 't');
}
TEST(EscapeControlTest, BsonOutputContainsBS)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         value("\b A string with A Back Space");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::bsonExporter(value, PrinterInterface::OutputType::Default)) {
        exportDone = true;
    }
    std::string_view outputView((&*output.str().begin()) + 11 , std::size(value));
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(outputView.find('\t'), std::string::npos);
    auto find = outputView.find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(outputView[find+1], 'b');
}
TEST(EscapeControlTest, BsonOutputContainsNL)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         value("\n A string with A New Line");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::bsonExporter(value, PrinterInterface::OutputType::Default)) {
        exportDone = true;
    }
    std::string_view outputView((&*output.str().begin()) + 11 , std::size(value));
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(outputView.find('\t'), std::string::npos);
    auto find = outputView.find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(outputView[find+1], 'n');
}
TEST(EscapeControlTest, BsonOutputContainsFF)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         value("\f A string with A Form Feed");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::bsonExporter(value, PrinterInterface::OutputType::Default)) {
        exportDone = true;
    }
    std::string_view outputView((&*output.str().begin()) + 11 , std::size(value));
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(outputView.find('\t'), std::string::npos);
    auto find = outputView.find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(outputView[find+1], 'f');
}
TEST(EscapeControlTest, BsonOutputContainsCR)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         value("\r A string with A Carridge Return");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::bsonExporter(value, PrinterInterface::OutputType::Default)) {
        exportDone = true;
    }
    std::string_view outputView((&*output.str().begin()) + 11 , std::size(value));
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(outputView.find('\t'), std::string::npos);
    auto find = outputView.find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(outputView[find+1], 'r');
}


