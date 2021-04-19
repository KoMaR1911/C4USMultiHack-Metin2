#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonPrinter.h"
#include <algorithm>

TEST(JsonPrinterTest, ArrayTokens)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream);

    printer.openDoc();
    printer.openMap(-1);
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ("{}", result);
}
TEST(JsonPrinterTest, MapTokens)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream);

    printer.openDoc();
    printer.openArray(-1);
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ("[]", result);
}
TEST(JsonPrinterTest, ArrayValues)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream);

    printer.openDoc();
    printer.openArray(-1);
    printer.addValue(true);
    printer.addValue(false);
    printer.addValue(static_cast<short>(55));
    printer.addValue(56);
    printer.addValue(78.89);
    printer.addValue(57l);
    printer.addValue(58ll);
    printer.addValue(std::string("Astring"));
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"([true,false,55,56,78.89,57,58,"Astring"])", result);
}
TEST(JsonPrinterTest, MapValues)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream);

    printer.openDoc();
    printer.openMap(-1);
    printer.addKey("K1");
    printer.addValue(true);
    printer.addKey("K2");
    printer.addValue(false);
    printer.addKey("K3");
    printer.addValue(56);
    printer.addKey("K4");
    printer.addValue(78.89);
    printer.addKey("K6");
    printer.addValue(std::string("Astring"));
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"({"K1":true,"K2":false,"K3":56,"K4":78.89,"K6":"Astring"})", result);
}
TEST(JsonPrinterTest, MapWithMapValues)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream);

    printer.openDoc();
    printer.openMap(-1);
    printer.addKey("K1");
    printer.openMap(-1);
    printer.addKey("K1");
    printer.addValue(true);
    printer.addKey("K2");
    printer.addValue(false);
    printer.closeMap();
    printer.addKey("K3");
    printer.addValue(56);
    printer.addKey("K4");
    printer.openMap(-1);
    printer.addKey("K4");
    printer.addValue(78.89);
    printer.closeMap();
    printer.addKey("K6");
    printer.addValue(std::string("Astring"));
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"({"K1":{"K1":true,"K2":false},"K3":56,"K4":{"K4":78.89},"K6":"Astring"})", result);
}
TEST(JsonPrinterTest, MapWithArrayValues)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream);

    printer.openDoc();
    printer.openMap(-1);
    printer.addKey("K1");
    printer.openArray(-1);
    printer.addValue(true);
    printer.addValue(false);
    printer.addValue(static_cast<unsigned short>(55));
    printer.addValue(56u);
    printer.addValue(57ul);
    printer.addValue(58ull);
    printer.addValue(60.f);
    printer.addValue(61.0L);
    printer.closeArray();
    printer.addKey("K3");
    printer.addValue(56);
    printer.addKey("K4");
    printer.openArray(-1);
    printer.addValue(78.89);
    printer.closeArray();
    printer.addKey("K6");
    printer.addValue(std::string("Astring"));
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"({"K1":[true,false,55,56,57,58,60,61],"K3":56,"K4":[78.89],"K6":"Astring"})", result);
}
TEST(JsonPrinterTest, ArrayWithMapValues)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream);

    printer.openDoc();
    printer.openArray(-1);
    printer.openMap(-1);
    printer.addKey("K1");
    printer.addValue(true);
    printer.addKey("K2");
    printer.addValue(false);
    printer.closeMap();
    printer.addValue(56);
    printer.openMap(-1);
    printer.addKey("K4");
    printer.addValue(78.89);
    printer.closeMap();
    printer.addValue(std::string("Astring"));
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"([{"K1":true,"K2":false},56,{"K4":78.89},"Astring"])", result);
}
TEST(JsonPrinterTest, ArrayWithArrayValues)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream);

    printer.openDoc();
    printer.openArray(-1);
    printer.openArray(-1);
    printer.addValue(true);
    printer.addValue(false);
    printer.closeArray();
    printer.addValue(56);
    printer.openArray(-1);
    printer.addValue(78.89);
    printer.closeArray();
    printer.addValue(std::string("Astring"));
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"([[true,false],56,[78.89],"Astring"])", result);
}
TEST(JsonPrinterTest, CheckStreeamIsCompressed)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    printer.openDoc();
    printer.openArray(-1);
    printer.openMap(-1);
    printer.addKey("K1");
    printer.addValue(true);
    printer.addKey("K2");
    printer.addValue(false);
    printer.closeMap();
    printer.addValue(56);
    printer.openMap(-1);
    printer.addKey("K4");
    printer.addValue(78.89);
    printer.closeMap();
    printer.addValue(std::string("Astring"));
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    int             space   = std::count_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);});
    EXPECT_EQ(0, space);
}
TEST(JsonPrinterTest, CloseMapWithArray)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    printer.openDoc();
    printer.openMap(-1);
    ASSERT_ANY_THROW(
        printer.closeArray();
    );
}
TEST(JsonPrinterTest, CloseArrayWithMap)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    printer.openDoc();
    printer.openArray(-1);
    ASSERT_ANY_THROW(
        printer.closeMap();
    );
}
TEST(JsonPrinterTest, PuttingKeyInArray)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    printer.openDoc();
    printer.openArray(-1);
    ASSERT_ANY_THROW(
        printer.addKey("This old house");
    );
}
TEST(JsonPrinterTest, AddRawValueTest)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    printer.openDoc();
    printer.openMap(-1);
    printer.addKey("K1");
    printer.addRawValue("12");
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"K1":12})");
}
TEST(JsonPrinterTest, DoubleZeroNeedsDot)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    printer.openDoc();
    printer.openArray(-1);
    printer.addValue(0.0);
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    auto find = result.find('.');
    EXPECT_NE(std::string::npos, find);
}

