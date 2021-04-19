#include "SerializeConfig.h"
#include "DeprecatedTest.h"
#include "IgnoreUneededDataTest.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "YamlThor.h"
#include "BsonThor.h"
#include <algorithm>
#include <cctype>

TEST(DeprecatedTest, Json)
{
    IgnoreUneededDataTest::Thing obj;

    std::stringstream data;
    data << TA::jsonExport(obj);

    IgnoreUneededDataTest::Thing objver;
    data >> TA::jsonImport(objver);
}
TEST(DeprecatedTest, Yaml)
{
    IgnoreUneededDataTest::Thing obj;

    std::stringstream data;
    data << TA::yamlExport(obj);

    IgnoreUneededDataTest::Thing objver;
    data >> TA::yamlImport(objver);
}

TEST(DeprecatedTest, JsonMakeTraitCustom)
{
    DepricatedTypeSpace::NormalObject    data{"BillyTheKid", 12};

    std::stringstream stream;
    stream << ThorsAnvil::Serialize::jsonExporter(data);

    std::string       result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return std::isspace(x);}), std::end(result));;

    EXPECT_EQ(R"({"name":"BillyTheKid","value":12})", result);
}

TEST(DeprecatedTest, BsonMakeTraitCustom)
{
    DepricatedTypeSpace::NormalObject    data{"ShouldThrowAsCustomIsNotSupportedByBSON", 88};

    std::stringstream stream;
    EXPECT_ANY_THROW(
        stream << ThorsAnvil::Serialize::bsonExporter(data)
    );
}
