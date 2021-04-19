#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "YamlPrinter.h"
#include <algorithm>

TEST(YamlPrinterTest, NullValue)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream);

    printer.openDoc();
    printer.addNull();
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ("---null...", result);
}
TEST(YamlPrinterTest, ArrayTokens)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream);

    printer.openDoc();
    printer.openMap(-1);
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ("---{}...", result);
}
TEST(YamlPrinterTest, MapTokens)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream);

    printer.openDoc();
    printer.openArray(-1);
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ("---[]...", result);
}
TEST(YamlPrinterTest, ArrayValues)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

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
    EXPECT_EQ(R"(---[true,false,55,56,78.89,57,58,Astring]...)", result);
}
TEST(YamlPrinterTest, MapValues)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

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
    EXPECT_EQ(R"(---{K1:true,K2:false,K3:56,K4:78.89,K6:Astring}...)", result);
}
TEST(YamlPrinterTest, MapWithMapValues)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

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
    EXPECT_EQ(R"(---{K1:{K1:true,K2:false},K3:56,K4:{K4:78.89},K6:Astring}...)", result);
}
TEST(YamlPrinterTest, MapWithArrayValues)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

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
    EXPECT_EQ(R"(---{K1:[true,false,55,56,57,58,60,61],K3:56,K4:[78.89],K6:Astring}...)", result);
}
TEST(YamlPrinterTest, ArrayWithMapValues)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

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
    EXPECT_EQ(R"(---[{K1:true,K2:false},56,{K4:78.89},Astring]...)", result);
}
TEST(YamlPrinterTest, ArrayWithArrayValues)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

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
    EXPECT_EQ(R"(---[[true,false],56,[78.89],Astring]...)", result);
}
TEST(YamlPrinterTest, CloseMapWithArray)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    printer.openDoc();
    printer.openMap(-1);
    ASSERT_ANY_THROW(
        printer.closeArray();
    );
}
TEST(YamlPrinterTest, CloseArrayWithMap)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    printer.openDoc();
    printer.openArray(-1);
    ASSERT_ANY_THROW(
        printer.closeMap();
    );
}
TEST(YamlPrinterTest, PuttingKeyInArray)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    printer.openDoc();
    printer.openArray(-1);
    ASSERT_ANY_THROW(
        printer.addKey("This old house");
    );
}
