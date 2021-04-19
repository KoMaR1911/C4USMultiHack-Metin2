#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "HomeBrewTest.h"
#include <sstream>
#include <iostream>
#include <string>

TEST(HomeBrewTest, homeBrewTest)
{
    using ThorsAnvil::Serialize::jsonImporter;
    using ThorsAnvil::Serialize::jsonExporter;

    std::stringstream   inputData(R"({"key":"XYZ","code":37373})");

    HomeBrewBlock    object;
    inputData >> jsonImporter(object);

    if (object.key != "XYZ" || object.code != 37373) {
        std::cerr << "Fail";
    }
    std::cerr << "OK";
}
