#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Traits.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <memory>
#include <iostream>


using namespace std::string_literals;
using namespace ThorsAnvil::Serialize;
using namespace std;

namespace Issue38
{

struct Connection
{
    bool    active;
};

struct IPConnection: public Connection
{
    int     port;
};

struct IPv4Connection: public IPConnection
{
    std::string     v4Name;
};

struct IPv6Connection: public IPConnection
{
    std::string     v6Name;
    double          cost;
};

struct TcpConnection
{
    int             blocks;
};

struct UdpConnection
{
    int             listeners;
};

struct Tcp4Connection : public IPv4Connection, public TcpConnection
{
    std::vector<int>    data;
};
struct Tcp6Connection : public IPv6Connection, public TcpConnection
{
    std::vector<int>    sync;
};
struct Udp4Connection : public IPv4Connection, public UdpConnection
{
    std::vector<double>    fly;
};
struct Udp6Connection : public IPv6Connection, public UdpConnection
{
    std::vector<std::string>    fancy;
};

using Tcp4ConnectionParent = ThorsAnvil::Serialize::Parents<IPv4Connection, TcpConnection>;
using Tcp6ConnectionParent = ThorsAnvil::Serialize::Parents<IPv6Connection, TcpConnection>;
using Udp4ConnectionParent = ThorsAnvil::Serialize::Parents<IPv4Connection, UdpConnection>;
using Udp6ConnectionParent = ThorsAnvil::Serialize::Parents<IPv6Connection, UdpConnection>;

}


ThorsAnvil_MakeTrait(Issue38::Connection, active);
ThorsAnvil_ExpandTrait(Issue38::Connection, Issue38::IPConnection, port);
ThorsAnvil_ExpandTrait(Issue38::IPConnection, Issue38::IPv4Connection, v4Name);
ThorsAnvil_ExpandTrait(Issue38::IPConnection, Issue38::IPv6Connection, v6Name, cost);
ThorsAnvil_MakeTrait(Issue38::TcpConnection, blocks);
ThorsAnvil_MakeTrait(Issue38::UdpConnection, listeners);


ThorsAnvil_ExpandTrait(Issue38::Tcp4ConnectionParent, Issue38::Tcp4Connection, data);
ThorsAnvil_ExpandTrait(Issue38::Tcp6ConnectionParent, Issue38::Tcp6Connection, sync);
ThorsAnvil_ExpandTrait(Issue38::Udp4ConnectionParent, Issue38::Udp4Connection, fly);
ThorsAnvil_ExpandTrait(Issue38::Udp6ConnectionParent, Issue38::Udp6Connection, fancy);

#include <iostream>

TEST(Issue38Test, JsonConnection)
{
    std::string input = R"(
    {
        "active": true
    })";
    std::stringstream stream(input);

    Issue38::Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, JsonIPConnection)
{
    std::string input = R"(
    {
        "active": true,
        "port":   22
    })";
    std::stringstream stream(input);

    Issue38::IPConnection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, JsonIPv4Connection)
{
    std::string input = R"(
    {
        "active": true,
        "port": 56,
        "v4Name": "LongPort"
    })";
    std::stringstream stream(input);

    Issue38::IPv4Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, JsonIPv6Connection)
{
    std::string input = R"(
    {
        "active": true,
        "port": 67,
        "v6Name": "ShortPort",
        "cost": 12.5
    })";
    std::stringstream stream(input);

    Issue38::IPv6Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, JsonTcpConnection)
{
    std::string input = R"(
    {
        "blocks": 8
    })";
    std::stringstream stream(input);

    Issue38::TcpConnection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, JsonUdpConnection)
{
    std::string input = R"(
    {
        "listeners": 12
    })";
    std::stringstream stream(input);

    Issue38::UdpConnection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, JsonTcp4Connection)
{
    std::string input = R"(
    {
        "active": true,
        "port": 56,
        "v4Name": "LongPort",
        "blocks": 8,
        "data": [15, 67]
    })";
    std::stringstream stream(input);

    Issue38::Tcp4Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, JsonTcp6Connection)
{
    std::string input = R"(
    {
        "active": true,
        "port": 56,
        "v6Name": "LongPort",
        "cost": 12,
        "blocks": 88,
        "sync": [15, 67]
    })";
    std::stringstream stream(input);

    Issue38::Tcp6Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, JsonUdp4Connection)
{
    std::string input = R"(
    {
        "active": true,
        "port": 67,
        "v4Name": "ShortPort",
        "listeners": 999,
        "fly": [13, 14, 12.5]
    })";
    std::stringstream stream(input);

    Issue38::Udp4Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, JsonUdp6Connection)
{
    std::string input = R"(
    {
        "active": true,
        "port": 56,
        "v6Name": "LongPort",
        "cost": 88,
        "listeners": 101,
        "fancy": ["long", "way", "down"]
    })";
    std::stringstream stream(input);

    Issue38::Udp6Connection  test;
    stream >> ThorsAnvil::Serialize::jsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::jsonExporter(test, false);

    std::string result  = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    input.erase(std::remove_if(std::begin(input),  std::end(input),  [](char x){return ::isspace(x);}), std::end(input));
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, BsonConnection)
{
    //std::string input = R"( { "active": true })";
    std::string input = "\x0E\x00\x00\x00"
                        "\x08" "active\x00" "\x01"
                        "\x00"s;
    std::stringstream stream(input);

    Issue38::Connection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output.str();
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, BsonIPConnection)
{
    //std::string input = R"({ "active": true, "port":   22 })";
    std::string input = "\x18\x00\x00\x00"
                        "\x08" "active\x00" "\x01"
                        "\x10" "port\x00"   "\x16\x00\x00\x00"
                        "\x00"s;
    std::stringstream stream(input);

    Issue38::IPConnection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output.str();
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, BsonIPv4Connection)
{
    //std::string input = R"( { "active": true, "port": 56, "v4Name": "LongPort" })";
    std::string input = "\x2D\x00\x00\x00"
                        "\x08" "active\x00" "\x01"
                        "\x10" "port\x00"   "\x38\x00\x00\x00"
                        "\x02" "v4Name\x00" "\x09\x00\x00\x00" "LongPort\x00"
                        "\x00"s;
    std::stringstream stream(input);

    Issue38::IPv4Connection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output.str();
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, BsonIPv6Connection)
{
    //std::string input = R"( { "active": true, "port": 67, "v6Name": "ShortPort", "cost": 12.5 })";
    std::string input = "\x3C\x00\x00\x00"
                        "\x08" "active\x00" "\x01"
                        "\x10" "port\x00"   "\x43\x00\x00\x00"
                        "\x02" "v6Name\x00" "\x0A\x00\x00\x00" "ShortPort\x00"
                        "\x01" "cost\x00"   "\x00\x00\x00\x00\x00\x00\x29\x40"
                        "\x00"s;
    std::stringstream stream(input);

    Issue38::IPv6Connection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output.str();
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, BsonTcpConnection)
{
    //std::string input = R"( { "blocks": 8 })";
    std::string input = "\x11\x00\x00\x00"
                        "\x10" "blocks\x00" "\x08\x00\x00\x00"
                        "\x00"s;
    std::stringstream stream(input);

    Issue38::TcpConnection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output.str();
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, BsonUdpConnection)
{
    //std::string input = R"( { "listeners": 12 })";
    std::string input = "\x14\x00\x00\x00"
                        "\x10" "listeners\x00"  "\x0C\x00\x00\x00"
                        "\x00"s;
    std::stringstream stream(input);

    Issue38::UdpConnection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output.str();
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, BsonTcp4Connection)
{
    //std::string input = R"( { "active": true, "port": 56, "v4Name": "LongPort", "blocks": 8, "data": [15, 67] })";
    std::string input = "\x52\x00\x00\x00"
                        "\x08" "active\x00" "\x01"
                        "\x10" "port\x00"   "\x38\x00\x00\x00"
                        "\x02" "v4Name\x00" "\x09\x00\x00\x00" "LongPort\x00"
                        "\x10" "blocks\x00" "\x08\x00\x00\x00"
                        "\x04" "data\x00"
                                "\x13\x00\x00\x00"
                                "\x10" "0\x00"  "\x0E\x00\x00\x00"
                                "\x10" "1\x00"  "\x43\x00\x00\x00"
                                "\x00"
                        "\x00"s;
    std::stringstream stream(input);

    Issue38::Tcp4Connection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output.str();
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, BsonTcp6Connection)
{
    //std::string input = R"( { "active": true, "port": 56, "v6Name": "LongPort", "cost": 12, "blocks": 88, "sync": [15, 67] })";
    std::string input = "\x60\x00\x00\x00"
                        "\x08" "active\x00" "\x01"
                        "\x10" "port\x00"   "\x38\x00\x00\x00"
                        "\x02" "v6Name\x00" "\x09\x00\x00\x00" "LongPort\x00"
                        "\x01" "cost\x00"   "\x00\x00\x00\x00\x00\x00\x28\x40"
                        "\x10" "blocks\x00" "\x58\x00\x00\x00"
                        "\x04" "sync\x00"
                                "\x13\x00\x00\x00"
                                "\x10" "0\x00"  "\x0E\x00\x00\x00"
                                "\x10" "1\x00"  "\x43\x00\x00\x00"
                                "\x00"
                        "\x00"s;
    std::stringstream stream(input);

    Issue38::Tcp6Connection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output.str();
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, BsonUdp4Connection)
{
    //std::string input = R"( { "active": true, "port": 67, "v4Name": "ShortPort", "listeners": 999, "fly": [13, 14, 12.5] })";
    std::string input = "\x68\x00\x00\x00"
                        "\x08" "active\x00" "\x01"
                        "\x10" "port\x00"   "\x43\x00\x00\x00"
                        "\x02" "v4Name\x00" "\x0A\x00\x00\x00" "ShortPort\x00"
                        "\x10" "listeners\x00" "\x08\x00\x00\x00"
                        "\x04" "fly\x00"
                                "\x26\x00\x00\x00"
                                "\x01" "0\x00"  "\x00\x00\x00\x00\x00\x00\x2A\x40"
                                "\x01" "1\x00"  "\x00\x00\x00\x00\x00\x00\x2C\x40"
                                "\x01" "2\x00"  "\x00\x00\x00\x00\x00\x00\x29\x40"
                                "\x00"
                        "\x00"s;
    std::stringstream stream(input);

    Issue38::Udp4Connection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output.str();
    EXPECT_EQ(input, result);
}
TEST(Issue38Test, BsonUdp6Connection)
{
    //std::string input = R"( { "active": true, "port": 56, "v6Name": "LongPort", "cost": 88, "listeners": 101, "fancy": ["long", "way", "down"] })";
    std::string input = "\x79\x00\x00\x00"
                        "\x08" "active\x00" "\x01"
                        "\x10" "port\x00"   "\x38\x00\x00\x00"
                        "\x02" "v6Name\x00" "\x09\x00\x00\x00" "LongPort\x00"
                        "\x01" "cost\x00"   "\x00\x00\x00\x00\x00\x00\x56\x40"
                        "\x10" "listeners\x00" "\x65\x00\x00\x00"
                        "\x04" "fancy\x00"
                                "\x28\x00\x00\x00"
                                "\x02" "0\x00"  "\x05\x00\x00\x00" "long\x00"
                                "\x02" "1\x00"  "\x04\x00\x00\x00" "way\x00"
                                "\x02" "2\x00"  "\x05\x00\x00\x00" "down\x00"
                                "\x00"
                        "\x00"s;
    std::stringstream stream(input);

    Issue38::Udp6Connection  test;
    stream >> ThorsAnvil::Serialize::bsonImporter(test, false);

    std::stringstream output;
    output << ThorsAnvil::Serialize::bsonExporter(test, false);

    std::string result  = output.str();
    EXPECT_EQ(input, result);
}
