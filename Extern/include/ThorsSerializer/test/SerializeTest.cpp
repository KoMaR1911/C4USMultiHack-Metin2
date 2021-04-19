#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Traits.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include <cstring>
#include <string>
#include <algorithm>


std::string const testData1 = R"({"theInteger":34,"aNonRealValue":56.78,"test":true,"normalString":"Done"})";
std::string const testData2 = R"({"theInteger":456,"aNonRealValue":89.101,"test":false,"normalString":"Akinkthatisnotstraight","data1":1,"data2":2})";
std::string const testData3 = R"({"member1":{"theInteger":234567,"aNonRealValue":123.45,"test":true,"normalString":"NotASquareAndOnlyOneSide"})"
                              R"(,"member2":{"theInteger":234567,"aNonRealValue":123.45,"test":true,"normalString":"NotASquareAndOnlyOneSide","data1":67,"data2":11}})";
// testData4 is identical to testData1 but with several ignored fields added.
std::string const testData4 = R"({"theInteger":34,"aNonRealValue":56.78,"test":true,"normalString":"Done","ShouldIgnore":true, "ignoreMap": {"Plop":true}, "ignoreArray":[true, false, [1,2,34], {"key":"value"}]})";
std::string const testData5 = R"({"theInteger":34,"aNonRealValue":56.78,"test":true,"normalString":"Done","anotherValue":14})";
std::string const testDataE1 = R"({"ignoreMap": {"Plop":true, ]}})";
std::string const testDataE2 = R"({"ignoreArray": [}]})";
std::string const testDataE3 = R"({"ignoreArray": [)";
std::string const testDataE4 = R"({"ignoreArray": )";
std::string const testDataE5 = R"({"ignoreArray": ])";
std::string const testDataE6 = R"({"ignoreArray": })";
std::string const testDataE7 = R"({"aNonRealValue":56.78,"test":true,"normalString":"Done", "anotherValue":13})";

TEST(SerializeTest, JsonSerializeStructureOfValue)
{
    SerializeTest::SerializeTestExtra        data(34,56.78, true, "Done");

    std::stringstream   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream);
    ThorsAnvil::Serialize::Serializer   serializer(printer);

    serializer.print(data);
    std::string result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(testData1, result);
}

TEST(SerializeTest, JsonDeSerializeStructureOfValue)
{
    SerializeTest::SerializeTestExtra      data;

    std::stringstream                   stream(testData1);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    deSerializer.parse(data);

    EXPECT_EQ(data.theInteger,      34);
    EXPECT_EQ(data.aNonRealValue,   56.78);
    EXPECT_EQ(data.test,            true);
    EXPECT_EQ(data.normalString,    "Done");
}

TEST(SerializeTest, JsonSerializeStructureOfValueAndParents)
{
    SerializeTest::SerializeTestChild     data(1, 2, 456, 89.101, false, "Akinkthatisnotstraight");

    std::stringstream   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream);
    ThorsAnvil::Serialize::Serializer   serializer(printer);

    serializer.print(data);
    std::string result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(testData2, result);
}

TEST(SerializeTest, JsonDeSerializeStructureOfValueAndParent)
{
    SerializeTest::SerializeTestChild      data;

    std::stringstream                   stream(testData2);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    deSerializer.parse(data);

    EXPECT_EQ(data.theInteger,      456);
    EXPECT_EQ(data.aNonRealValue,   89.101);
    EXPECT_EQ(data.test,            false);
    EXPECT_EQ(data.normalString,    "Akinkthatisnotstraight");
    EXPECT_EQ(data.data1,           1);
    EXPECT_EQ(data.data2,           2);
}

TEST(SerializeTest, JsonSerializeStructureMemberOfValue)
{
    SerializeTest::SerializeTestMembers        data(67, 11, 234567, 123.45, true, "NotASquareAndOnlyOneSide");

    std::stringstream   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream);
    ThorsAnvil::Serialize::Serializer   serializer(printer);

    serializer.print(data);
    std::string result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(testData3, result);
}

TEST(SerializeTest, JsonDeSerializeStructureMemberOfValue)
{
    SerializeTest::SerializeTestMembers        data;

    std::stringstream                   stream(testData3);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    deSerializer.parse(data);

    EXPECT_EQ(data.member1.theInteger,      234567);
    EXPECT_EQ(data.member1.aNonRealValue,   123.45);
    EXPECT_EQ(data.member1.test,            true);
    EXPECT_EQ(data.member1.normalString,    "NotASquareAndOnlyOneSide");
    EXPECT_EQ(data.member2.theInteger,      234567);
    EXPECT_EQ(data.member2.aNonRealValue,   123.45);
    EXPECT_EQ(data.member2.test,            true);
    EXPECT_EQ(data.member2.normalString,    "NotASquareAndOnlyOneSide");
    EXPECT_EQ(data.member2.data1,           67);
    EXPECT_EQ(data.member2.data2,           11);
}

TEST(SerializeTest, JsonStrictParserDoesNotIgnoreData)
{
    SerializeTest::SerializeTestExtra      data;

    std::stringstream                   stream(testData4);
    ThorsAnvil::Serialize::JsonParser   parser(stream, ThorsAnvil::Serialize::ParserInterface::ParseType::Strict);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, JsonExactParserDoesNotIgnoreData)
{
    SerializeTest::SerializeTestExtra      data;

    std::stringstream                   stream(testData4);
    ThorsAnvil::Serialize::JsonParser   parser(stream, ThorsAnvil::Serialize::ParserInterface::ParseType::Exact);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, JsonExactParserNeedsAllMembersFail)
{
    SerializeTest::SerializeExact      data;

    // testData1 has all the members of SerializeTestExtra (parent of SerializeExact)
    // but does not have anotherValue so should throw an exception
    std::stringstream                   stream(testData1);
    ThorsAnvil::Serialize::JsonParser   parser(stream, ThorsAnvil::Serialize::ParserInterface::ParseType::Exact);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, JsonExactParserNeedsAllMembersAndParentFail)
{
    SerializeTest::SerializeExact      data;

    // testData1 has all the members of SerializeTestExtra (parent of SerializeExact)
    // but does not have anotherValue so should throw an exception
    std::stringstream                   stream(testDataE7);
    ThorsAnvil::Serialize::JsonParser   parser(stream, ThorsAnvil::Serialize::ParserInterface::ParseType::Exact);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, JsonExactParserNeedsAllMembersGood)
{
    SerializeTest::SerializeExact      data;

    std::stringstream                   stream(testData5);
    ThorsAnvil::Serialize::JsonParser   parser(stream, ThorsAnvil::Serialize::ParserInterface::ParseType::Exact);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    deSerializer.parse(data);
}
TEST(SerializeTest, JsonIgnoreAllTheDataWeDontCareAbout)
{
    SerializeTest::SerializeTestExtra      data;

    std::stringstream                   stream(testData4);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    deSerializer.parse(data);

    EXPECT_EQ(data.theInteger,      34);
    EXPECT_EQ(data.aNonRealValue,   56.78);
    EXPECT_EQ(data.test,            true);
    EXPECT_EQ(data.normalString,    "Done");
}
TEST(SerializeTest, JsonIgnoreDataMapWithBadData1)
{
    SerializeTest::SerializeTestExtra      data;

    std::stringstream                   stream(testDataE1);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, JsonIgnoreDataArrayWithBadData2)
{
    SerializeTest::SerializeTestExtra      data;

    std::stringstream                   stream(testDataE2);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, JsonIgnoreDataArrayWithBadData3)
{
    SerializeTest::SerializeTestExtra      data;

    std::stringstream                   stream(testDataE3);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, JsonIgnoreDataArrayWithBadData4)
{
    SerializeTest::SerializeTestExtra      data;

    std::stringstream                   stream(testDataE4);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, JsonIgnoreDataArrayWithBadData5)
{
    SerializeTest::SerializeTestExtra      data;

    std::stringstream                   stream(testDataE5);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, JsonIgnoreDataArrayWithBadData6)
{
    SerializeTest::SerializeTestExtra      data;

    std::stringstream                   stream(testDataE6);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, JsonDerivedTypeNoNewMembers)
{
    SerializeTest::SerializeExactNoMembers        data(34,56.78, true, "Done");

    std::stringstream   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream);
    ThorsAnvil::Serialize::Serializer   serializer(printer);

    serializer.print(data);
    std::string result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(testData1, result);
}
TEST(SerializeTest, JsonDerivedTypeNoNewMembersPolyMorphic)
{
    SerializeTest::SerializeExactNoMembersPoly        data(34,56.78, true, "Done");

    std::stringstream   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream);
    ThorsAnvil::Serialize::Serializer   serializer(printer);

    serializer.print(data);
    std::string result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(testData1, result);
}

using namespace std::string_literals;
std::string const testData1Bson = "\x4a\x00\x00\x00"
                                  "\x10" "theInteger\x00"       "\x22\x00\x00\x00"
                                  "\x01" "aNonRealValue\x00"    "\xa4\x70\x3d\x0a\xd7\x63\x4c\x40"
                                  "\x08" "test\x00"             "\x01"
                                  "\x02" "normalString\x00"     "\x05\x00\x00\x00" "Done\x00"
                                  "\x00"s;
//R"({"theInteger":34,"aNonRealValue":56.78,"test":true,"normalString":"Done"})";
std::string const testData2Bson = "\x72\x00\x00\x00"
                                  "\x10" "theInteger\x00"       "\xC8\x01\x00\x00"
                                  "\x01" "aNonRealValue\x00"    "\x58\x39\xb4\xc8\x76\x46\x56\x40"
                                  "\x08" "test\x00"             "\x00"
                                  "\x02" "normalString\x00"     "\x17\x00\x00\x00" "Akinkthatisnotstraight\x00"
                                  "\x10" "data1\x00"            "\x01\x00\x00\x00"
                                  "\x10" "data2\x00"            "\x02\x00\x00\x00"
                                  "\x00"s;
//R"({"theInteger":456,"aNonRealValue":89.101,"test":false,"normalString":"Akinkthatisnotstraight","data1":1,"data2":2})";
std::string const testData3Bson = "\xE9\x00\x00\x00"
                                  "\x03" "member1\x00"
                                      "\x5E\x00\x00\x00"
                                      "\x10" "theInteger\x00"       "\x47\x94\x03\x00"
                                      "\x01" "aNonRealValue\x00"    "\xcd\xcc\xcc\xcc\xcc\xdc\x5e\x40"
                                      "\x08" "test\x00"             "\x01"
                                      "\x02" "normalString\x00"     "\x19\x00\x00\x00" "NotASquareAndOnlyOneSide\x00"
                                      "\x00"
                                  "\x03" "member2\x00"
                                      "\x74\x00\x00\x00"
                                      "\x10" "theInteger\x00"       "\x47\x94\x03\x00"
                                      "\x01" "aNonRealValue\x00"    "\xcd\xcc\xcc\xcc\xcc\xdc\x5e\x40"
                                      "\x08" "test\x00"             "\x01"
                                      "\x02" "normalString\x00"     "\x19\x00\x00\x00" "NotASquareAndOnlyOneSide\x00"
                                      "\x10" "data1\x00"            "\x43\x00\x00\x00"
                                      "\x10" "data2\x00"            "\x0B\x00\x00\x00"
                                      "\x00"
                                  "\x00"s;
//R"({"member1":{"theInteger":234567,"aNonRealValue":123.45,"test":true,"normalString":"NotASquareAndOnlyOneSide"})"
//R"(,"member2":{"theInteger":234567,"aNonRealValue":123.45,"test":true,"normalString":"NotASquareAndOnlyOneSide","data1":67,"data2":11}})";
// testData4 is identical to testData1 but with several ignored fields added.
std::string const testData4Bson = "\xbc\x00\x00\x00"
                                  "\x10" "theInteger\x00"       "\x22\x00\x00\x00"
                                  "\x01" "aNonRealValue\x00"    "\xa4\x70\x3d\x0a\xd7\x63\x4c\x40"
                                  "\x08" "test\x00"             "\x01"
                                  "\x02" "normalString\x00"     "\x05\x00\x00\x00" "Done\x00"
                                  "\x08" "ShouldIgnore\x00"     "\x01"
                                  "\x03" "ignoreMap\x00"
                                        "\x0C\x00\x00\x00"
                                        "\x08" "Plop\x00"  "\x01"
                                        "\x00"
                                  "\x04" "ignoreArr\x00"
                                        "\x41\x00\x00\x00"
                                        "\x08" "0\x00" "\x01"
                                        "\x08" "1\x00" "\x01"
                                        "\x04" "2\x00"
                                                "\x1A\x00\x00\x00"
                                                "\x10" "0\x00" "\x01\x00\x00\x00"
                                                "\x10" "1\x00" "\x02\x00\x00\x00"
                                                "\x10" "2\x00" "\x22\x00\x00\x00"
                                                "\x00"
                                        "\x03" "3\x00"
                                                "\x14\x00\x00\x00"
                                                "\x02" "key\x00" "\x06\x00\x00\x00"  "value\x00"
                                                "\x00"
                                        "\x00"
                                  "\x00"s;
//R"({"theInteger":34,"aNonRealValue":56.78,"test":true,"normalString":"Done","ShouldIgnore":true, "ignoreMap": {"Plop":true}, "ignoreArray":[true, false, [1,2,34], {"key":"value"}]})";
std::string const testData5Bson = "\x5c\x00\x00\x00"
                                  "\x10" "theInteger\x00"       "\x22\x00\x00\x00"
                                  "\x01" "aNonRealValue\x00"    "\xa4\x70\x3d\x0a\xd7\x63\x4c\x40"
                                  "\x08" "test\x00"             "\x01"
                                  "\x02" "normalString\x00"     "\x05\x00\x00\x00" "Done\x00"
                                  "\x10" "anotherValue\x00"     "\x0E\x00\x00\x00"
                                  "\x00"s;
//R"({"theInteger":34,"aNonRealValue":56.78,"test":true,"normalString":"Done","anotherValue":14})";
TEST(SerializeTest, BsonSerializeStructureOfValue)
{
    SerializeTest::SerializeTestExtra        data(34,56.78, true, "Done");

    std::stringstream   stream;
    ThorsAnvil::Serialize::PrinterInterface::PrinterConfig config;
    config.parserInfo = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Map);

    ThorsAnvil::Serialize::BsonPrinter  printer(stream, config);
    ThorsAnvil::Serialize::Serializer   serializer(printer);

    serializer.print(data);
    std::string result  = stream.str();

    EXPECT_EQ(testData1Bson, result);
}

TEST(SerializeTest, BsonDeSerializeStructureOfValue)
{
    SerializeTest::SerializeTestExtra      data;
    ThorsAnvil::Serialize::ParserInterface::ParserConfig config;
    config.parserInfo = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Map);

    std::stringstream                   stream(testData1Bson);
    ThorsAnvil::Serialize::BsonParser   parser(stream, config);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    deSerializer.parse(data);

    EXPECT_EQ(data.theInteger,      34);
    EXPECT_EQ(data.aNonRealValue,   56.78);
    EXPECT_EQ(data.test,            true);
    EXPECT_EQ(data.normalString,    "Done");
}

TEST(SerializeTest, BsonSerializeStructureOfValueAndParents)
{
    SerializeTest::SerializeTestChild     data(1, 2, 456, 89.101, false, "Akinkthatisnotstraight");
    ThorsAnvil::Serialize::PrinterInterface::PrinterConfig config;
    config.parserInfo = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Map);

    std::stringstream   stream;
    ThorsAnvil::Serialize::BsonPrinter  printer(stream, config);
    ThorsAnvil::Serialize::Serializer   serializer(printer);

    serializer.print(data);
    std::string result  = stream.str();

    EXPECT_EQ(testData2Bson, result);
}

TEST(SerializeTest, BsonDeSerializeStructureOfValueAndParent)
{
    SerializeTest::SerializeTestChild      data;

    std::stringstream                   stream(testData2Bson);
    ThorsAnvil::Serialize::BsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    deSerializer.parse(data);

    EXPECT_EQ(data.theInteger,      456);
    EXPECT_EQ(data.aNonRealValue,   89.101);
    EXPECT_EQ(data.test,            false);
    EXPECT_EQ(data.normalString,    "Akinkthatisnotstraight");
    EXPECT_EQ(data.data1,           1);
    EXPECT_EQ(data.data2,           2);
}

TEST(SerializeTest, BsonSerializeStructureMemberOfValue)
{
    SerializeTest::SerializeTestMembers        data(67, 11, 234567, 123.45, true, "NotASquareAndOnlyOneSide");
    ThorsAnvil::Serialize::PrinterInterface::PrinterConfig config;
    config.parserInfo = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Map);

    std::stringstream   stream;
    ThorsAnvil::Serialize::BsonPrinter  printer(stream, config);
    ThorsAnvil::Serialize::Serializer   serializer(printer);

    serializer.print(data);
    std::string result  = stream.str();

    EXPECT_EQ(testData3Bson, result);
}

TEST(SerializeTest, BsonDeSerializeStructureMemberOfValue)
{
    SerializeTest::SerializeTestMembers        data;
    ThorsAnvil::Serialize::ParserInterface::ParserConfig config;
    config.parserInfo = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Map);

    std::stringstream                   stream(testData3Bson);
    ThorsAnvil::Serialize::BsonParser   parser(stream, config);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    deSerializer.parse(data);

    EXPECT_EQ(data.member1.theInteger,      234567);
    EXPECT_EQ(data.member1.aNonRealValue,   123.45);
    EXPECT_EQ(data.member1.test,            true);
    EXPECT_EQ(data.member1.normalString,    "NotASquareAndOnlyOneSide");
    EXPECT_EQ(data.member2.theInteger,      234567);
    EXPECT_EQ(data.member2.aNonRealValue,   123.45);
    EXPECT_EQ(data.member2.test,            true);
    EXPECT_EQ(data.member2.normalString,    "NotASquareAndOnlyOneSide");
    EXPECT_EQ(data.member2.data1,           67);
    EXPECT_EQ(data.member2.data2,           11);
}

TEST(SerializeTest, BsonStrictParserDoesNotIgnoreData)
{
    SerializeTest::SerializeTestExtra      data;
    ThorsAnvil::Serialize::ParserInterface::ParserConfig config(ThorsAnvil::Serialize::ParserInterface::ParseType::Strict);
    config.parserInfo = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Map);

    std::stringstream                   stream(testData4Bson);
    ThorsAnvil::Serialize::BsonParser   parser(stream, config);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, BsonExactParserDoesNotIgnoreData)
{
    SerializeTest::SerializeTestExtra      data;
    ThorsAnvil::Serialize::ParserInterface::ParserConfig config(ThorsAnvil::Serialize::ParserInterface::ParseType::Exact);
    config.parserInfo = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Map);

    std::stringstream                   stream(testData4Bson);
    ThorsAnvil::Serialize::BsonParser   parser(stream, config);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, BsonExactParserNeedsAllMembersFail)
{
    SerializeTest::SerializeExact      data;

    // testData1 has all the members of SerializeTestExtra (parent of SerializeExact)
    // but does not have anotherValue so should throw an exception
    std::stringstream                   stream(testData1Bson);
    ThorsAnvil::Serialize::ParserInterface::ParserConfig config(ThorsAnvil::Serialize::ParserInterface::ParseType::Exact);
    config.parserInfo = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Map);
    ThorsAnvil::Serialize::BsonParser   parser(stream, config);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, BsonExactParserNeedsAllMembersGood)
{
    SerializeTest::SerializeExact      data;
    ThorsAnvil::Serialize::ParserInterface::ParserConfig config(ThorsAnvil::Serialize::ParserInterface::ParseType::Exact);
    config.parserInfo = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Map);

    std::stringstream                   stream(testData5Bson);
    ThorsAnvil::Serialize::BsonParser   parser(stream, config);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    deSerializer.parse(data);
}
TEST(SerializeTest, BsonIgnoreAllTheDataWeDontCareAbout)
{
    SerializeTest::SerializeTestExtra      data;
    ThorsAnvil::Serialize::PrinterInterface::PrinterConfig config;
    config.parserInfo = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Map);

    std::stringstream                   stream(testData4Bson);
    ThorsAnvil::Serialize::BsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    deSerializer.parse(data);

    EXPECT_EQ(data.theInteger,      34);
    EXPECT_EQ(data.aNonRealValue,   56.78);
    EXPECT_EQ(data.test,            true);
    EXPECT_EQ(data.normalString,    "Done");
}
TEST(SerializeTest, BsonDerivedTypeNoNewMembers)
{
    SerializeTest::SerializeExactNoMembers        data(34,56.78, true, "Done");
    ThorsAnvil::Serialize::PrinterInterface::PrinterConfig config;
    config.parserInfo = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Map);

    std::stringstream   stream;
    ThorsAnvil::Serialize::BsonPrinter  printer(stream, config);
    ThorsAnvil::Serialize::Serializer   serializer(printer);

    serializer.print(data);
    std::string result  = stream.str();

    EXPECT_EQ(testData1Bson, result);
}
TEST(SerializeTest, BsonDerivedTypeNoNewMembersPolyMorphic)
{
    SerializeTest::SerializeExactNoMembersPoly        data(34,56.78, true, "Done");
    ThorsAnvil::Serialize::PrinterInterface::PrinterConfig config;
    config.parserInfo = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Map);

    std::stringstream   stream;
    ThorsAnvil::Serialize::BsonPrinter  printer(stream, config);
    ThorsAnvil::Serialize::Serializer   serializer(printer);

    serializer.print(data);
    std::string result  = stream.str();

    EXPECT_EQ(testData1Bson, result);
}


