#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "Serialize.h"
#include "test/SerializeTest.h"
#include <algorithm>

std::string stripspace(std::string const& value)
{
    std::string  result(value);
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return std::isspace(x);}), std::end(result));
    return result;
}

TEST(SerializeEnumTest, JsonRedGreenBlueAtRed)
{
    SerializeTest::RGB      enumHolder {SerializeTest::Red};
    std::stringstream   str;
    str << ThorsAnvil::Serialize::jsonExporter(enumHolder, false);

    EXPECT_EQ(R"("Red")", stripspace(str.str()));
}
TEST(SerializeEnumTest, JsonRedGreenBlueAtGreen)
{
    SerializeTest::RGB      enumHolder {SerializeTest::Green};
    std::stringstream   str;
    str << ThorsAnvil::Serialize::jsonExporter(enumHolder, false);

    EXPECT_EQ(R"("Green")", stripspace(str.str()));
}
TEST(SerializeEnumTest, JsonRedGreenBlueAtBlue)
{
    SerializeTest::RGB      enumHolder {SerializeTest::Blue};
    std::stringstream   str;
    str << ThorsAnvil::Serialize::jsonExporter(enumHolder, false);

    EXPECT_EQ(R"("Blue")", stripspace(str.str()));
}
TEST(DeSerializeEnumTest, JsonRefGreenBlueFromRed)
{
    std::stringstream   str(R"("Red")");
    SerializeTest::RGB     enumHolder {SerializeTest::Green};

    str >> ThorsAnvil::Serialize::jsonImporter(enumHolder, false);
    EXPECT_EQ(SerializeTest::Red, enumHolder);
}
TEST(DeSerializeEnumTest, JsonRefGreenBlueFromGreen)
{
    std::stringstream   str(R"("Green")");
    SerializeTest::RGB     enumHolder {SerializeTest::Red};

    str >> ThorsAnvil::Serialize::jsonImporter(enumHolder, false);
    EXPECT_EQ(SerializeTest::Green, enumHolder);
}
TEST(DeSerializeEnumTest, JsonRefGreenBlueFromBlue)
{
    std::stringstream   str(R"("Blue")");
    SerializeTest::RGB     enumHolder {SerializeTest::Green};

    str >> ThorsAnvil::Serialize::jsonImporter(enumHolder, false);
    EXPECT_EQ(SerializeTest::Blue, enumHolder);
}
TEST(SerializeEnumTest, JsonSerEnumInContainer)
{
    SerializeTest::EumHolder  holder { SerializeTest::Red };

    std::stringstream   str;

    str << ThorsAnvil::Serialize::jsonExporter(holder, false);
    EXPECT_EQ(R"({"value":"Red"})", stripspace(str.str()));
}
TEST(SerializeEnumTest, JsonDeSerEnumInContainer)
{
    SerializeTest::EumHolder  holder { SerializeTest::Red };
    std::stringstream   str(R"({"value": "Green"})");

    str >> ThorsAnvil::Serialize::jsonImporter(holder, false);
    EXPECT_EQ(SerializeTest::Green, holder.value);
}


TEST(SerializeEnumTest, BsonRedGreenBlueAtRed)
{
    SerializeTest::RGB      enumHolder {SerializeTest::Red};
    std::stringstream   str;
    str << ThorsAnvil::Serialize::bsonExporter(enumHolder, false);

    static const char expectedRaw[]
                = "\x10\x00\x00\x00"
                  "\x02" "0\x00" "\x04\x00\x00\x00"  "Red\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, str.str());
    //EXPECT_EQ(R"("Red")", stripspace(str.str()));
}
TEST(SerializeEnumTest, BsonRedGreenBlueAtGreen)
{
    SerializeTest::RGB      enumHolder {SerializeTest::Green};
    std::stringstream   str;
    str << ThorsAnvil::Serialize::bsonExporter(enumHolder, false);

    static const char expectedRaw[]
                = "\x12\x00\x00\x00"
                  "\x02" "0\x00" "\x06\x00\x00\x00"  "Green\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, str.str());
    //EXPECT_EQ(R"("Green")", stripspace(str.str()));
}
TEST(SerializeEnumTest, BsonRedGreenBlueAtBlue)
{
    SerializeTest::RGB      enumHolder {SerializeTest::Blue};
    std::stringstream   str;
    str << ThorsAnvil::Serialize::bsonExporter(enumHolder, false);

    static const char expectedRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00"  "Blue\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, str.str());
    //EXPECT_EQ(R"("Blue")", stripspace(str.str()));
}
TEST(DeSerializeEnumTest, BsonRefGreenBlueFromRed)
{
    //std::stringstream   str(R"("Red")");
    static const char inputRaw[]
                = "\x10\x00\x00\x00"
                  "\x02" "0\x00" "\x04\x00\x00\x00"  "Red\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream str(input);
    SerializeTest::RGB     enumHolder {SerializeTest::Green};

    str >> ThorsAnvil::Serialize::bsonImporter(enumHolder, false);
    EXPECT_EQ(SerializeTest::Red, enumHolder);
}
TEST(DeSerializeEnumTest, BsonRefGreenBlueFromGreen)
{
    //std::stringstream   str(R"("Green")");
    static const char inputRaw[]
                = "\x12\x00\x00\x00"
                  "\x02" "0\x00" "\x06\x00\x00\x00"  "Green\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream str(input);
    SerializeTest::RGB     enumHolder {SerializeTest::Red};

    str >> ThorsAnvil::Serialize::bsonImporter(enumHolder, false);
    EXPECT_EQ(SerializeTest::Green, enumHolder);
}
TEST(DeSerializeEnumTest, BsonRefGreenBlueFromBlue)
{
    //std::stringstream   str(R"("Blue")");
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00"  "Blue\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream str(input);
    SerializeTest::RGB     enumHolder {SerializeTest::Green};

    str >> ThorsAnvil::Serialize::bsonImporter(enumHolder, false);
    EXPECT_EQ(SerializeTest::Blue, enumHolder);
}
TEST(SerializeEnumTest, BsonSerEnumInContainer)
{
    SerializeTest::EumHolder  holder { SerializeTest::Red };

    std::stringstream   str;

    str << ThorsAnvil::Serialize::bsonExporter(holder, false);
    static const char expectedRaw[]
                = "\x14\x00\x00\x00"
                  "\x02" "value\x00" "\x04\x00\x00\x00"  "Red\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, str.str());
    //EXPECT_EQ(R"({"value":"Red"})", stripspace(str.str()));
}
TEST(SerializeEnumTest, BsonDeSerEnumInContainer)
{
    SerializeTest::EumHolder  holder { SerializeTest::Red };
    //std::stringstream   str(R"({"value": "Green"})");
    static const char inputRaw[]
                = "\x16\x00\x00\x00"
                  "\x02" "value\x00" "\x06\x00\x00\x00"  "Green\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream str(input);

    str >> ThorsAnvil::Serialize::bsonImporter(holder, false);
    EXPECT_EQ(SerializeTest::Green, holder.value);
}

TEST(SerializeEnumTest, EnumFlagEmpty)
{
    SerializeTest::Flag     value = SerializeTest::Flag::empty;
    std::stringstream str;
    str << value;
    EXPECT_EQ("empty", str.str());
}
TEST(SerializeEnumTest, EnumFlagOne)
{
    SerializeTest::Flag     value = SerializeTest::Flag::One;
    std::stringstream str;
    str << value;
    EXPECT_EQ("One", str.str());
}
TEST(SerializeEnumTest, EnumFlagTwo)
{
    SerializeTest::Flag     value = SerializeTest::Flag::Two;
    std::stringstream str;
    str << value;
    EXPECT_EQ("Two", str.str());
}
TEST(SerializeEnumTest, EnumFlagThree)
{
    SerializeTest::Flag     value = SerializeTest::Flag::Three;
    std::stringstream str;
    str << value;
    EXPECT_EQ("Three", str.str());
}
TEST(SerializeEnumTest, EnumFlagOneThree)
{
    SerializeTest::Flag     value = SerializeTest::Flag::One | SerializeTest::Flag::Three;
    std::stringstream str;
    str << value;
    EXPECT_EQ("One | Three", str.str());
}




