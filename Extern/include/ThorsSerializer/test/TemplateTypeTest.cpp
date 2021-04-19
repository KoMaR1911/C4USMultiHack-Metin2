#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Serialize.tpp"
#include "SerUtil.h"
#include "Traits.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include <string>
#include <sstream>

using namespace std::string_literals;

namespace TemplateTypeTest
{

template<typename T>
struct TemplateType
{
    std::vector<T>   templateMember;
};

struct NormalInheritFromTemplate: public TemplateType<int>
{
    std::string      normalName;
};

template<typename T>
struct TemplateInheritFromTemplate: public TemplateType<T>
{
    std::vector<T>   alternative;
};

}


ThorsAnvil_Template_MakeTrait(1, TemplateTypeTest::TemplateType, templateMember); 
ThorsAnvil_ExpandTrait(TemplateTypeTest::TemplateType<int>, TemplateTypeTest::NormalInheritFromTemplate, normalName);
ThorsAnvil_Template_ExpandTrait(1, TemplateTypeTest::TemplateType<T1>, TemplateTypeTest::TemplateInheritFromTemplate, alternative);

TEST(TemplateTypeTest, JsontemplateTest)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         inputStr(R"({"templateMember":[1,2,3,4]})");
    std::stringstream   input(inputStr);
    std::stringstream   output;
    TemplateTypeTest::TemplateType<int>   data;

    input  >> ThorsAnvil::Serialize::jsonImporter(data, false);
    output << ThorsAnvil::Serialize::jsonExporter(data, PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
}

TEST(TemplateTypeTest, JsonnormalInheritingFromtemplateTest)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         inputStr(R"({"templateMember":[1,2,3,4],"normalName":"A name"})");
    std::stringstream   input(inputStr);
    std::stringstream   output;
    TemplateTypeTest::NormalInheritFromTemplate   data;

    input  >> ThorsAnvil::Serialize::jsonImporter(data, false);
    output << ThorsAnvil::Serialize::jsonExporter(data, PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
}

TEST(TemplateTypeTest, JsontemplateInheritingFromtemplateTest)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         inputStr(R"({"templateMember":[1,2,3,4],"alternative":[5,6,7,8]})");
    std::stringstream   input(inputStr);
    std::stringstream   output;
    TemplateTypeTest::TemplateInheritFromTemplate<int>   data;

    input  >> ThorsAnvil::Serialize::jsonImporter(data, false);
    output << ThorsAnvil::Serialize::jsonExporter(data, PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
}

TEST(TemplateTypeTest, BsontemplateTest)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    //std::string         inputStr(R"({"templateMember":[1,2,3,4]})");
    std::string         inputStr("\x36\x00\x00\x00"
                                 "\x04" "templateMember\x00"
                                        "\x21\x00\x00\x00"
                                        "\x10" "0\x00" "\x01\x00\x00\x00"
                                        "\x10" "1\x00" "\x02\x00\x00\x00"
                                        "\x10" "2\x00" "\x03\x00\x00\x00"
                                        "\x10" "3\x00" "\x04\x00\x00\x00"
                                        "\x00"
                                 "\x00"s);
    std::stringstream   input(inputStr);
    std::stringstream   output;
    TemplateTypeTest::TemplateType<int>   data;

    input  >> ThorsAnvil::Serialize::bsonImporter(data, false);
    output << ThorsAnvil::Serialize::bsonExporter(data, PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
}

TEST(TemplateTypeTest, BsonnormalInheritingFromtemplateTest)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    //std::string         inputStr(R"({"templateMember":[1,2,3,4],"normalName":"A name"})");
    std::string         inputStr("\x4D\x00\x00\x00"
                                 "\x04" "templateMember\x00"
                                        "\x21\x00\x00\x00"
                                        "\x10" "0\x00" "\x01\x00\x00\x00"
                                        "\x10" "1\x00" "\x02\x00\x00\x00"
                                        "\x10" "2\x00" "\x03\x00\x00\x00"
                                        "\x10" "3\x00" "\x04\x00\x00\x00"
                                        "\x00"
                                 "\x02" "normalName\x00"    "\x07\x00\x00\x00" "A name\x00"
                                 "\x00"s);
    std::stringstream   input(inputStr);
    std::stringstream   output;
    TemplateTypeTest::NormalInheritFromTemplate   data;

    input  >> ThorsAnvil::Serialize::bsonImporter(data, false);
    output << ThorsAnvil::Serialize::bsonExporter(data, PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
}

TEST(TemplateTypeTest, BsontemplateInheritingFromtemplateTest)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    //std::string         inputStr(R"({"templateMember":[1,2,3,4],"alternative":[5,6,7,8]})");
    std::string         inputStr("\x64\x00\x00\x00"
                                 "\x04" "templateMember\x00"
                                        "\x21\x00\x00\x00"
                                        "\x10" "0\x00" "\x01\x00\x00\x00"
                                        "\x10" "1\x00" "\x02\x00\x00\x00"
                                        "\x10" "2\x00" "\x03\x00\x00\x00"
                                        "\x10" "3\x00" "\x04\x00\x00\x00"
                                        "\x00"
                                 "\x04" "alternative\x00"
                                        "\x21\x00\x00\x00"
                                        "\x10" "0\x00" "\x05\x00\x00\x00"
                                        "\x10" "1\x00" "\x06\x00\x00\x00"
                                        "\x10" "2\x00" "\x07\x00\x00\x00"
                                        "\x10" "3\x00" "\x08\x00\x00\x00"
                                        "\x00"
                                 "\x00"s);
    std::stringstream   input(inputStr);
    std::stringstream   output;
    TemplateTypeTest::TemplateInheritFromTemplate<int>   data;

    input  >> ThorsAnvil::Serialize::bsonImporter(data, false);
    output << ThorsAnvil::Serialize::bsonExporter(data, PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
}


