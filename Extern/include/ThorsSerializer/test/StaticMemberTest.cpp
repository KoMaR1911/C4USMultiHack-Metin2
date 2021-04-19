#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Serialize.tpp"
#include "Traits.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include <string>
#include <sstream>

using namespace std::string_literals;

namespace StaticMemberTest
{

struct StaticMember
{
    static int staticMember;
           int normalMember;
};

int StaticMember::staticMember = 8;
}

ThorsAnvil_MakeTrait(StaticMemberTest::StaticMember, normalMember, staticMember); 

TEST(StaticMemberTest, JsonserializeStaticMember)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         inputStr(R"({"normalMember":7,"staticMember":14})");
    std::stringstream   input(inputStr);
    std::stringstream   output;
    StaticMemberTest::StaticMember        data;

    input  >> ThorsAnvil::Serialize::jsonImporter(data, false);
    output << ThorsAnvil::Serialize::jsonExporter(data, PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
}

TEST(StaticMemberTest, BsonserializeStaticMember)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    //std::string         inputStr(R"({"normalMember":7,"staticMember":14})");
    std::string           inputStr("\x29\x00\x00\x00"
                              "\x10" "normalMember\x00" "\x07\x00\x00\x00"
                              "\x10" "staticMember\x00" "\x0E\x00\x00\x00"
                              "\x00"s);
    std::stringstream   input(inputStr);
    std::stringstream   output;
    StaticMemberTest::StaticMember        data;

    input  >> ThorsAnvil::Serialize::bsonImporter(data, false);
    output << ThorsAnvil::Serialize::bsonExporter(data, PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
}

