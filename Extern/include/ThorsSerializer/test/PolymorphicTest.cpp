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
#include <cctype>

namespace PolymorphicTest
{
struct Vehicle
{
    Vehicle(){}
    Vehicle(int speed)
        : speed(speed)
    {}
    int     speed;
    ThorsAnvil_PolyMorphicSerializer(PolymorphicTest::Vehicle);
};
struct Car: public Vehicle
{
    Car(){}
    Car(int speed, std::string const& make)
        : Vehicle(speed)
        , make(make)
    {}
    std::string     make;
    ThorsAnvil_PolyMorphicSerializer(PolymorphicTest::Car);
};
struct Bike: public Vehicle
{
    Bike(){}
    Bike(int speed, int stroke)
        : Vehicle(speed)
        , stroke(stroke)
    {}
    int     stroke;
    ThorsAnvil_PolyMorphicSerializer(PolymorphicTest::Bike);
};
struct User
{
    int         age;
    Vehicle*    transport;
};
}

ThorsAnvil_MakeTrait(PolymorphicTest::Vehicle, speed);
ThorsAnvil_ExpandTrait(PolymorphicTest::Vehicle, PolymorphicTest::Car, make);
ThorsAnvil_ExpandTrait(PolymorphicTest::Vehicle, PolymorphicTest::Bike, stroke);
ThorsAnvil_MakeTrait(PolymorphicTest::User, age, transport);

TEST(PolymorphicTest, JsonNullPointer)
{
    PolymorphicTest::User    user1{10, nullptr};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExporter(user1, false);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":null})");
}
TEST(PolymorphicTest, JsonVehiclePointer)
{
    PolymorphicTest::User    user1{10, new PolymorphicTest::Vehicle(12)};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExporter(user1, false);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"__type":"PolymorphicTest::Vehicle","speed":12}})");
}
TEST(PolymorphicTest, JsonCarPointer)
{
    PolymorphicTest::User    user1{10, new PolymorphicTest::Car(16, "Turbo")};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExporter(user1, false);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"__type":"PolymorphicTest::Car","speed":16,"make":"Turbo"}})");
}

TEST(PolymorphicTest, JsonBikePointer)
{
    PolymorphicTest::User    user1{10, new PolymorphicTest::Bike(18, 7)};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExporter(user1, false);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"__type":"PolymorphicTest::Bike","speed":18,"stroke":7}})");
}

TEST(PolymorphicTest, JsonReadNull)
{
    std::stringstream   stream(R"({"age":10,"transport":null})");
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(12)};

    stream >> ThorsAnvil::Serialize::jsonImporter(user1, false);
    EXPECT_EQ(user1.age, 10);
    EXPECT_EQ(user1.transport, nullptr);
}

TEST(PolymorphicTest, JsonReadVehicle)
{
    std::stringstream   stream(R"({"age":10,"transport":{"__type":"PolymorphicTest::Vehicle","speed":12}})");
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(13)};

    stream >> ThorsAnvil::Serialize::jsonImporter(user1, false);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 12);
}

TEST(PolymorphicTest, JsonReadCar)
{
    std::stringstream   stream(R"({"age":10,"transport":{"__type":"PolymorphicTest::Car","speed":16,"make":"Turbo"}})");
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(14)};

    stream >> ThorsAnvil::Serialize::jsonImporter(user1, false);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 16);

    PolymorphicTest::Car* car = dynamic_cast<PolymorphicTest::Car*>(user1.transport);
    ASSERT_NE(car, nullptr);
    EXPECT_EQ(car->make, "Turbo");
}

TEST(PolymorphicTest, JsonReadBike)
{
    std::stringstream   stream(R"({"age":10,"transport":{"__type":"PolymorphicTest::Bike","speed":18,"stroke":7}})");
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(15)};

    stream >> ThorsAnvil::Serialize::jsonImporter(user1, false);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 18);

    PolymorphicTest::Bike* bike = dynamic_cast<PolymorphicTest::Bike*>(user1.transport);
    ASSERT_NE(bike, nullptr);
    EXPECT_EQ(bike->stroke, 7);
}

TEST(PolymorphicTest, BsonNullPointer)
{
    PolymorphicTest::User    user1{10, nullptr};

    std::stringstream   data(std::ios_base::out | std::ios_base::binary);;
    data << ThorsAnvil::Serialize::bsonExporter(user1, false);
    std::string result = data.str();

    static const char expectedRaw[]
                    = "\x19\x00\x00\x00"
                      "\x10" "age\x00" "\x0A\x00\x00\x00"
                      "\x0A" "transport\x00"
                      "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(result, expected);
    // R"({"age":10,"transport":null})");
}
TEST(PolymorphicTest, BsonVehiclePointer)
{
    PolymorphicTest::User    user1{10, new PolymorphicTest::Vehicle(12)};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::bsonExporter(user1, false);
    std::string result = data.str();

    static const char expectedRaw[]
                    = "\x4E\x00\x00\x00"
                      "\x10" "age\x00" "\x0A\x00\x00\x00"
                      "\x03" "transport\x00"
                            "\x35\x00\x00\x00"
                            "\x02" "__type\x00" "\x19\x00\x00\x00" "PolymorphicTest::Vehicle\x00"
                            "\x10" "speed\x00"  "\x0C\x00\x00\x00"
                            "\x00"
                      "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(result, expected);
    //EXPECT_EQ(result, R"({"age":10,"transport":{"__type":"PolymorphicTest::Vehicle","speed":12}})");
}
TEST(PolymorphicTest, BsonCarPointer)
{
    PolymorphicTest::User    user1{10, new PolymorphicTest::Car(16, "Turbo")};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::bsonExporter(user1, false);
    std::string result = data.str();

    static const char expectedRaw[]
                    = "\x5A\x00\x00\x00"
                      "\x10" "age\x00" "\x0A\x00\x00\x00"
                      "\x03" "transport\x00"
                            "\x41\x00\x00\x00"
                            "\x02" "__type\x00" "\x15\x00\x00\x00" "PolymorphicTest::Car\x00"
                            "\x10" "speed\x00"  "\x10\x00\x00\x00"
                            "\x02" "make\x00"   "\x06\x00\x00\x00" "Turbo\x00"
                            "\x00"
                      "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(result, expected);
    //EXPECT_EQ(result, R"({"age":10,"transport":{"__type":"PolymorphicTest::Car","speed":16,"make":"Turbo"}})");
}

TEST(PolymorphicTest, BsonBikePointer)
{
    PolymorphicTest::User    user1{10, new PolymorphicTest::Bike(18, 7)};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::bsonExporter(user1, false);
    std::string result = data.str();

    static const char expectedRaw[]
                    = "\x57\x00\x00\x00"
                      "\x10" "age\x00" "\x0A\x00\x00\x00"
                      "\x03" "transport\x00"
                            "\x3E\x00\x00\x00"
                            "\x02" "__type\x00" "\x16\x00\x00\x00" "PolymorphicTest::Bike\x00"
                            "\x10" "speed\x00"  "\x12\x00\x00\x00"
                            "\x10" "stroke\x00" "\x07\x00\x00\x00"
                            "\x00"
                      "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(result, expected);
    //EXPECT_EQ(result, R"({"age":10,"transport":{"__type":"PolymorphicTest::Bike","speed":18,"stroke":7}})");
}

TEST(PolymorphicTest, BsonReadNull)
{
    static const char inputRaw[]
                    = "\x19\x00\x00\x00"
                      "\x10" "age\x00" "\x0A\x00\x00\x00"
                      "\x0A" "transport\x00"
                      "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    //std::stringstream   stream(R"({"age":10,"transport":null})");
    std::stringstream stream(input);
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(12)};

    stream >> ThorsAnvil::Serialize::bsonImporter(user1, false);
    EXPECT_EQ(user1.age, 10);
    EXPECT_EQ(user1.transport, nullptr);
}

TEST(PolymorphicTest, BsonReadVehicle)
{
    static const char inputRaw[]
                    = "\x4E\x00\x00\x00"
                      "\x10" "age\x00" "\x0A\x00\x00\x00"
                      "\x03" "transport\x00"
                            "\x35\x00\x00\x00"
                            "\x02" "__type\x00" "\x19\x00\x00\x00" "PolymorphicTest::Vehicle\x00"
                            "\x10" "speed\x00"  "\x0C\x00\x00\x00"
                            "\x00"
                      "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    //std::stringstream   stream(R"({"age":10,"transport":{"__type":"PolymorphicTest::Vehicle","speed":12}})");
    std::stringstream stream(input);
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(13)};

    stream >> ThorsAnvil::Serialize::bsonImporter(user1, false);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 12);
}

TEST(PolymorphicTest, BsonReadCar)
{
    static const char inputRaw[]
                    = "\x5A\x00\x00\x00"
                      "\x10" "age\x00" "\x0A\x00\x00\x00"
                      "\x03" "transport\x00"
                            "\x41\x00\x00\x00"
                            "\x02" "__type\x00" "\x15\x00\x00\x00" "PolymorphicTest::Car\x00"
                            "\x10" "speed\x00"  "\x10\x00\x00\x00"
                            "\x02" "make\x00"   "\x06\x00\x00\x00" "Turbo\x00"
                            "\x00"
                      "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    //std::stringstream   stream(R"({"age":10,"transport":{"__type":"PolymorphicTest::Car","speed":16,"make":"Turbo"}})");
    std::stringstream stream(input);
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(14)};

    stream >> ThorsAnvil::Serialize::bsonImporter(user1, false);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 16);

    PolymorphicTest::Car* car = dynamic_cast<PolymorphicTest::Car*>(user1.transport);
    ASSERT_NE(car, nullptr);
    EXPECT_EQ(car->make, "Turbo");
}

TEST(PolymorphicTest, BsonReadBike)
{
    static const char inputRaw[]
                    = "\x57\x00\x00\x00"
                      "\x10" "age\x00" "\x0A\x00\x00\x00"
                      "\x03" "transport\x00"
                            "\x3E\x00\x00\x00"
                            "\x02" "__type\x00" "\x16\x00\x00\x00" "PolymorphicTest::Bike\x00"
                            "\x10" "speed\x00"  "\x12\x00\x00\x00"
                            "\x10" "stroke\x00" "\x07\x00\x00\x00"
                            "\x00"
                      "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    //std::stringstream   stream(R"({"age":10,"transport":{"__type":"PolymorphicTest::Bike","speed":18,"stroke":7}})");
    std::stringstream stream(input);
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(15)};

    stream >> ThorsAnvil::Serialize::bsonImporter(user1, false);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 18);

    PolymorphicTest::Bike* bike = dynamic_cast<PolymorphicTest::Bike*>(user1.transport);
    ASSERT_NE(bike, nullptr);
    EXPECT_EQ(bike->stroke, 7);
}


