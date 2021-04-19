#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "Serialize.h"
#include "Serialize.tpp"
#include "Traits.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <iostream>

namespace PolyMorphicSerializerUniquePointerTest
{
struct Quantities
{
    std::vector<int>* quantities;

    ~Quantities()
    {
        delete quantities;
    }
};

struct AbstractTourResult
{
    std::unique_ptr<Quantities> maxQuantities { nullptr };
    virtual ~AbstractTourResult() = default;
    ThorsAnvil_PolyMorphicSerializer(AbstractTourResult);
};

struct TourResult : public AbstractTourResult
{
    ~TourResult() override                      = default;
    ThorsAnvil_PolyMorphicSerializer(TourResult);
};

struct Tour
{
    std::unique_ptr<TourResult> result { nullptr };
};
}

ThorsAnvil_MakeTrait(PolyMorphicSerializerUniquePointerTest::Quantities, quantities);
ThorsAnvil_MakeTrait(PolyMorphicSerializerUniquePointerTest::AbstractTourResult, maxQuantities);
ThorsAnvil_ExpandTrait(PolyMorphicSerializerUniquePointerTest::AbstractTourResult, PolyMorphicSerializerUniquePointerTest::TourResult);
ThorsAnvil_MakeTrait(PolyMorphicSerializerUniquePointerTest::Tour, result);

TEST(PolyMorphicSerializerUniquePointerTest, JsonQuantitiesEmpty)
{
    PolyMorphicSerializerUniquePointerTest::Quantities                  t{};
    std::string                 str = R"({})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_EQ(nullptr, t.quantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, JsonQuantities)
{
    PolyMorphicSerializerUniquePointerTest::Quantities                  t{};
    std::string                 str = R"({"quantities":[15,23]})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_NE(nullptr, t.quantities);
    EXPECT_EQ(15, (*t.quantities)[0]);
    EXPECT_EQ(23, (*t.quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTest, JsonAbstractTourResultEmpty)
{
    PolyMorphicSerializerUniquePointerTest::AbstractTourResult          t{};
    std::string                 str = R"({})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_EQ(nullptr, t.maxQuantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, JsonAbstractTourResult)
{
    PolyMorphicSerializerUniquePointerTest::AbstractTourResult          t{};
    std::string                 str = R"({"maxQuantities":{}})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_EQ(nullptr, t.maxQuantities->quantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, JsonAbstractTourResultWithQuantities)
{
    PolyMorphicSerializerUniquePointerTest::AbstractTourResult          t{};
    std::string                 str = R"({"maxQuantities":{"quantities":[34,56]}})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_NE(nullptr, t.maxQuantities->quantities);
    EXPECT_EQ(34, (*t.maxQuantities->quantities)[0]);
    EXPECT_EQ(56, (*t.maxQuantities->quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTest, JsonTourResultEmpty)
{
    PolyMorphicSerializerUniquePointerTest::TourResult                  t{};
    std::string                 str = R"({})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_EQ(nullptr, t.maxQuantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, JsonTourResult)
{
    PolyMorphicSerializerUniquePointerTest::TourResult                  t{};
    std::string                 str = R"({"maxQuantities":{}})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_EQ(nullptr, t.maxQuantities->quantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, JsonTourResultWithQuantities)
{
    PolyMorphicSerializerUniquePointerTest::TourResult                  t{};
    std::string                 str = R"({"maxQuantities":{"quantities":[34,56]}})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_NE(nullptr, t.maxQuantities->quantities);
    EXPECT_EQ(34, (*t.maxQuantities->quantities)[0]);
    EXPECT_EQ(56, (*t.maxQuantities->quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTest, JsonTourEmpty)
{
    PolyMorphicSerializerUniquePointerTest::Tour                        t{};
    std::string                 str = R"({})";;
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::jsonImporter(t, false);
    EXPECT_EQ(nullptr, t.result);
}

TEST(PolyMorphicSerializerUniquePointerTest, BsonQuantitiesEmpty)
{
    PolyMorphicSerializerUniquePointerTest::Quantities                  t{};
    //std::string                 str = R"({})";;
    static const char strRaw[]
                    = "\x05\x00\x00\x00"
                      "\x00";
    std::string                 str(std::begin(strRaw), std::end(strRaw) - 1);
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_EQ(nullptr, t.quantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, BsonQuantities)
{
    PolyMorphicSerializerUniquePointerTest::Quantities                  t{};
    //std::string                 str = R"({"quantities":[15,23]})";;
    static const char strRaw[]
                    = "\x24\x00\x00\x00"
                      "\x04" "quantities\x00"
                            "\x13\x00\x00\x00"
                                "\x10" "0\x00" "\x0F\x00\x00\x00"
                                "\x10" "1\x00" "\x17\x00\x00\x00"
                            "\x00"
                      "\x00";
    std::string                 str(std::begin(strRaw), std::end(strRaw) - 1);
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_NE(nullptr, t.quantities);
    EXPECT_EQ(15, (*t.quantities)[0]);
    EXPECT_EQ(23, (*t.quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTest, BsonAbstractTourResultEmpty)
{
    PolyMorphicSerializerUniquePointerTest::AbstractTourResult          t{};
    //std::string                 str = R"({})";;
    static const char strRaw[]
                    = "\x05\x00\x00\x00"
                      "\x00";
    std::string                 str(std::begin(strRaw), std::end(strRaw) - 1);
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_EQ(nullptr, t.maxQuantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, BsonAbstractTourResult)
{
    PolyMorphicSerializerUniquePointerTest::AbstractTourResult          t{};
    //std::string                 str = R"({"maxQuantities":{}})";;
    static const char strRaw[]
                    = "\x19\x00\x00\x00"
                      "\x03" "maxQuantities\x00"
                            "\x05\x00\x00\x00"
                            "\x00"
                      "\x00";
    std::string                 str(std::begin(strRaw), std::end(strRaw) - 1);
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_EQ(nullptr, t.maxQuantities->quantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, BsonAbstractTourResultWithQuantities)
{
    PolyMorphicSerializerUniquePointerTest::AbstractTourResult          t{};
    //std::string                 str = R"({"maxQuantities":{"quantities":[34,56]}})";;
    static const char strRaw[]
                    = "\x38\x00\x00\x00"
                      "\x03" "maxQuantities\x00"
                            "\x24\x00\x00\x00"
                                "\x04" "quantities\x00"
                                    "\x13\x00\x00\x00"
                                        "\x10" "0\x00" "\x22\x00\x00\x00"
                                        "\x10" "1\x00" "\x38\x00\x00\x00"
                                    "\x00"
                            "\x00"
                      "\x00";
    std::string                 str(std::begin(strRaw), std::end(strRaw) - 1);
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_NE(nullptr, t.maxQuantities->quantities);
    EXPECT_EQ(34, (*t.maxQuantities->quantities)[0]);
    EXPECT_EQ(56, (*t.maxQuantities->quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTest, BsonTourResultEmpty)
{
    PolyMorphicSerializerUniquePointerTest::TourResult                  t{};
    //std::string                 str = R"({})";;
    static const char strRaw[]
                    = "\x05\x00\x00\x00"
                      "\x00";
    std::string                 str(std::begin(strRaw), std::end(strRaw) - 1);
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_EQ(nullptr, t.maxQuantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, BsonTourResult)
{
    PolyMorphicSerializerUniquePointerTest::TourResult                  t{};
    //std::string                 str = R"({"maxQuantities":{}})";;
    static const char strRaw[]
                    = "\x19\x00\x00\x00"
                      "\x03" "maxQuantities\x00"
                            "\x05\x00\x00\x00"
                            "\x00"
                      "\x00";
    std::string                 str(std::begin(strRaw), std::end(strRaw) - 1);
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_EQ(nullptr, t.maxQuantities->quantities);
}
TEST(PolyMorphicSerializerUniquePointerTest, BsonTourResultWithQuantities)
{
    PolyMorphicSerializerUniquePointerTest::TourResult                  t{};
    //std::string                 str = R"({"maxQuantities":{"quantities":[34,56]}})";;
    static const char strRaw[]
                    = "\x38\x00\x00\x00"
                      "\x03" "maxQuantities\x00"
                            "\x24\x00\x00\x00"
                                "\x04" "quantities\x00"
                                    "\x13\x00\x00\x00"
                                        "\x10" "0\x00" "\x22\x00\x00\x00"
                                        "\x10" "1\x00" "\x38\x00\x00\x00"
                                    "\x00"
                            "\x00"
                      "\x00";
    std::string                 str(std::begin(strRaw), std::end(strRaw) - 1);
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_NE(nullptr, t.maxQuantities);
    EXPECT_NE(nullptr, t.maxQuantities->quantities);
    EXPECT_EQ(34, (*t.maxQuantities->quantities)[0]);
    EXPECT_EQ(56, (*t.maxQuantities->quantities)[1]);
}
TEST(PolyMorphicSerializerUniquePointerTest, BsonTourEmpty)
{
    PolyMorphicSerializerUniquePointerTest::Tour                        t{};
    //std::string                 str = R"({})";;
    static const char strRaw[]
                    = "\x05\x00\x00\x00"
                      "\x00";
    std::string                 str(std::begin(strRaw), std::end(strRaw) - 1);
    std::istringstream          stream(str);
    stream >> ThorsAnvil::Serialize::bsonImporter(t, false);
    EXPECT_EQ(nullptr, t.result);
}


