#include "SerializeConfig.h"
#include "IgnoreUneededDataTest.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"

TEST(IgnoreUneededDataTest, JsonArrayEmpty)
{
    IgnoreUneededDataTest::Thing obj;
    obj.name = "Test";

    std::stringstream data;
    data << TA::jsonExporter(obj, false);

    IgnoreUneededDataTest::ThingVersion objver;
    data >> TA::jsonImporter(objver, false);
/*
    EXPECT_EQ(3, objver.version);
*/
}
TEST(IgnoreUneededDataTest, BsonArrayEmpty)
{
    IgnoreUneededDataTest::Thing obj;
    obj.name = "Test";

    std::stringstream data;
    data << TA::bsonExporter(obj, false);

    IgnoreUneededDataTest::ThingVersion objver;
    data >> TA::bsonImporter(objver, false);
/*
    EXPECT_EQ(3, objver.version);
*/
}

