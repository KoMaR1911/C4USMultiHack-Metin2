#include "SerializeConfig.h"
#include "SerUtil.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "test/TwitterTest.h"
#include <fstream>

TEST(TwitterTest, ReadTwitterObject)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::ifstream           input("test/data/twitter.json");
    TwitterTest::Twitter    value;
    bool                    importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParserInterface::ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, true);
    EXPECT_EQ(value.statuses[0].user.screen_name, "ayuu0123");
}

