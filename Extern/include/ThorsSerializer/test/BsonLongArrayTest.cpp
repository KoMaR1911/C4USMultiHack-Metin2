#include "gtest/gtest.h"
#include "BsonThor.h"
#include "SerUtil.h"

TEST(BsonLongArrayTest, ArrayWith110Elements)
{
    std::vector<int>    data;
    for(int loop=0;loop < 110;++loop) {
        data.emplace_back(56234 + loop);
    }

    std::stringstream stream;
    stream << ThorsAnvil::Serialize::bsonExporter(data);

    std::vector<int>    output;
    stream >> ThorsAnvil::Serialize::bsonImporter(output);

    EXPECT_EQ(data, output);
}

