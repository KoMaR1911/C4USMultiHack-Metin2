#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "BsonPrinter.h"
#include <algorithm>

class BsonTestPrinter: public ThorsAnvil::Serialize::BsonPrinter
{
    public:
        using BsonPrinter::BsonPrinter;
        std::size_t getSizeMapTest(std::size_t count)               {return getSizeMap(count);}
        std::size_t getSizeArrayTest(std::size_t count)             {return getSizeArray(count);}
        std::size_t getSizeNullTest()                               {return getSizeNull();}
        std::size_t getSizeValueTest(short value)                   {return getSizeValue(value);}
        std::size_t getSizeValueTest(int value)                     {return getSizeValue(value);}
        std::size_t getSizeValueTest(long int value)                {return getSizeValue(value);}
        std::size_t getSizeValueTest(long long int value)           {return getSizeValue(value);}
        std::size_t getSizeValueTest(unsigned short value)          {return getSizeValue(value);}
        std::size_t getSizeValueTest(unsigned int value)            {return getSizeValue(value);}
        std::size_t getSizeValueTest(unsigned long int value)       {return getSizeValue(value);}
        std::size_t getSizeValueTest(unsigned long long int value)  {return getSizeValue(value);}
        std::size_t getSizeValueTest(float value)                   {return getSizeValue(value);}
        std::size_t getSizeValueTest(double value)                  {return getSizeValue(value);}
        std::size_t getSizeValueTest(long double value)             {return getSizeValue(value);}
        std::size_t getSizeValueTest(bool value)                    {return getSizeValue(value);}
        std::size_t getSizeValueTest(std::string const& value)      {return getSizeValue(value);}
        std::size_t getSizeRawTest(std::size_t size)                {return getSizeRaw(size);}
};

TEST(BsonPrinterTest, ArrayTokens)
{
    std::stringstream                   stream;
    BsonTestPrinter                     printer(stream);

    printer.openDoc();
    printer.openMap(printer.getSizeMapTest(0));
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    static const char expectedRaw[]
                = "\x05\x00\x00\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, result);
    //EXPECT_EQ("{}", result);
}
TEST(BsonPrinterTest, MapTokens)
{
    std::stringstream                   stream;
    BsonTestPrinter                     printer(stream);

    printer.openDoc();
    printer.openArray(printer.getSizeArrayTest(0));
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    static const char expectedRaw[]
                = "\x05\x00\x00\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, result);
    //EXPECT_EQ("[]", result);
}
TEST(BsonPrinterTest, ArrayValues)
{
    std::stringstream                   stream;
    BsonTestPrinter                     printer(stream);

    printer.openDoc();
    printer.openArray(printer.getSizeArrayTest(8)
                        + printer.getSizeValueTest(true)
                        + printer.getSizeValueTest(false)
                        + printer.getSizeValueTest(static_cast<short>(55))
                        + printer.getSizeValueTest(56)
                        + printer.getSizeValueTest(78.89)
                        + printer.getSizeValueTest(57l)
                        + printer.getSizeValueTest(58ll)
                        + printer.getSizeValueTest(std::string("Astring")));
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
    static const char expectedRaw[]
                = "\x4B\x00\x00\x00"
                    "\x08" "0\x00" "\x01"
                    "\x08" "1\x00" "\x00"
                    "\x10" "2\x00" "\x37\x00\x00\x00"
                    "\x10" "3\x00" "\x38\x00\x00\x00"
                    "\x01" "4\x00" "\x29\x5c\x8f\xc2\xf5\xb8\x53\x40"
                    "\x12" "5\x00" "\x39\x00\x00\x00\x00\x00\x00\x00"
                    "\x12" "6\x00" "\x3A\x00\x00\x00\x00\x00\x00\x00"
                    "\x02" "7\x00" "\x08\x00\x00\x00" "Astring\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, result);
    //EXPECT_EQ(R"([true,false,55,56,78.89,57,58,"Astring"])", result);
}
TEST(BsonPrinterTest, MapValues)
{
    std::stringstream                   stream;
    BsonTestPrinter                     printer(stream);

    printer.openDoc();
    printer.openMap(printer.getSizeMapTest(8)
                        + 2 + printer.getSizeValueTest(true)
                        + 2 + printer.getSizeValueTest(false)
                        + 2 + printer.getSizeValueTest(static_cast<short>(55))
                        + 2 + printer.getSizeValueTest(56)
                        + 2 + printer.getSizeValueTest(78.89)
                        + 2 + printer.getSizeValueTest(57l)
                        + 2 + printer.getSizeValueTest(58ll)
                        + 2 + printer.getSizeValueTest(std::string("Astring")));
    printer.addKey("K0");
    printer.addValue(true);
    printer.addKey("K1");
    printer.addValue(false);
    printer.addKey("K2");
    printer.addValue(static_cast<short>(55));
    printer.addKey("K3");
    printer.addValue(56);
    printer.addKey("K4");
    printer.addValue(78.89);
    printer.addKey("K5");
    printer.addValue(57l);
    printer.addKey("K6");
    printer.addValue(58ll);
    printer.addKey("K7");
    printer.addValue(std::string("Astring"));
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    static const char expectedRaw[]
                = "\x53\x00\x00\x00"
                    "\x08" "K0\x00" "\x01"
                    "\x08" "K1\x00" "\x00"
                    "\x10" "K2\x00" "\x37\x00\x00\x00"
                    "\x10" "K3\x00" "\x38\x00\x00\x00"
                    "\x01" "K4\x00" "\x29\x5c\x8f\xc2\xf5\xb8\x53\x40"
                    "\x12" "K5\x00" "\x39\x00\x00\x00\x00\x00\x00\x00"
                    "\x12" "K6\x00" "\x3A\x00\x00\x00\x00\x00\x00\x00"
                    "\x02" "K7\x00" "\x08\x00\x00\x00" "Astring\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, result);
    //EXPECT_EQ(R"({"K1":true,"K2":false,"K3":56,"K4":78.89,"K6":"Astring"})", result);
}
TEST(BsonPrinterTest, MapWithMapValues)
{
    std::stringstream                   stream;
    BsonTestPrinter                     printer(stream);

    std::size_t map1map1Size = 
            printer.getSizeMapTest(2)
                    + 2 + printer.getSizeValueTest(true)
                    + 2 + printer.getSizeValueTest(false);
    std::size_t map1map2Size =
            printer.getSizeMapTest(3)
                    + 2 + printer.getSizeValueTest(78.89)
                    + 2 + printer.getSizeValueTest(57l)
                    + 2 + printer.getSizeValueTest(58ll);
    std::size_t map1 =
            printer.getSizeMapTest(4)
                    + 2 + map1map1Size
                    + 2 + printer.getSizeValueTest(56)
                    + 2 + map1map2Size
                    + 2 + printer.getSizeValueTest(std::string("Astring"));
    printer.openDoc();
    printer.openMap(map1);
    printer.addKey("K0");
    printer.openMap(map1map1Size);
    printer.addKey("K1");
    printer.addValue(true);
    printer.addKey("K2");
    printer.addValue(false);
    printer.closeMap();
    printer.addKey("K3");
    printer.addValue(56);
    printer.addKey("K4");
    printer.openMap(map1map2Size);
    printer.addKey("K4");
    printer.addValue(78.89);
    printer.addKey("K5");
    printer.addValue(57l);
    printer.addKey("K6");
    printer.addValue(58ll);
    printer.closeMap();
    printer.addKey("K7");
    printer.addValue(std::string("Astring"));
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    static const char expectedRaw[]
                = "\x5d\x00\x00\x00"
                  "\x03" "K0\x00" 
                        "\x0F\x00\x00\x00"
                        "\x08" "K1\x00" "\x01"
                        "\x08" "K2\x00" "\x00"
                        "\x00"
                  "\x10" "K3\x00" "\x38\x00\x00\x00"
                  "\x03" "K4\x00"
                        "\x29\x00\x00\x00"
                        "\x01" "K4\x00" "\x29\x5c\x8f\xc2\xf5\xb8\x53\x40"
                        "\x12" "K5\x00" "\x39\x00\x00\x00\x00\x00\x00\x00"
                        "\x12" "K6\x00" "\x3A\x00\x00\x00\x00\x00\x00\x00"
                        "\x00"
                  "\x02" "K7\x00" "\x08\x00\x00\x00" "Astring\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, result);
    //EXPECT_EQ(R"({"K1":{"K1":true,"K2":false},"K3":56,"K4":{"K4":78.89},"K6":"Astring"})", result);
}
TEST(BsonPrinterTest, MapWithArrayValues)
{
    std::stringstream                   stream;
    BsonTestPrinter                     printer(stream);

    std::size_t map1array1Size
            = printer.getSizeArrayTest(8)
            + printer.getSizeValueTest(static_cast<unsigned short>(55))
            + printer.getSizeValueTest(56u)
            + printer.getSizeValueTest(57ul)
            + printer.getSizeValueTest(58ull)
            + printer.getSizeValueTest(60.f)
            + printer.getSizeValueTest(61.0L);
    std::size_t map1array2Size
            = printer.getSizeArrayTest(1)
            + printer.getSizeValueTest(78.89);
    std::size_t map1Size
            = printer.getSizeMapTest(4)
            + 2 + map1array1Size
            + 2 + printer.getSizeValueTest(56)
            + 2 + map1array2Size
            + 2 + printer.getSizeValueTest(std::string("Astring"));
    printer.openDoc();
    printer.openMap(map1Size);
    printer.addKey("K0");
    printer.openArray(map1array1Size);
    printer.addValue(true);
    printer.addValue(false);
    printer.addValue(static_cast<unsigned short>(55));
    printer.addValue(56u);
    printer.addValue(57ul);
    printer.addValue(58ull);
    printer.addValue(60.f);
    printer.addValue(61.0L);
    printer.closeArray();
    printer.addKey("K1");
    printer.addValue(56);
    printer.addKey("K2");
    printer.openArray(map1array2Size);
    printer.addValue(78.89);
    printer.closeArray();
    printer.addKey("K3");
    printer.addValue(std::string("Astring"));
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    static const char expectedRaw[]
                = "\x7A\x00\x00\x00"
                  "\x04" "K0\x00" 
                        "\x45\x00\x00\x00"
                        "\x08" "0\x00" "\x01"
                        "\x08" "1\x00" "\x00"
                        "\x10" "2\x00" "\x37\x00\x00\x00"
                        "\x10" "3\x00" "\x38\x00\x00\x00"
                        "\x12" "4\x00" "\x39\x00\x00\x00\x00\x00\x00\x00"
                        "\x12" "5\x00" "\x3A\x00\x00\x00\x00\x00\x00\x00"
                        "\x01" "6\x00" "\x00\x00\x00\x00\x00\x00\x4E\x40"
                        "\x01" "7\x00" "\x00\x00\x00\x00\x00\x80\x4E\x40"
                        "\x00"
                  "\x10" "K1\x00" "\x38\x00\x00\x00"
                  "\x04" "K2\x00"
                        "\x10\x00\x00\x00"
                        "\x01" "0\x00" "\x29\x5c\x8f\xc2\xf5\xb8\x53\x40"
                        "\x00"
                  "\x02" "K3\x00" "\x08\x00\x00\x00" "Astring\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, result);
    //EXPECT_EQ(R"({"K1":[true,false,55,56,57,58,60,61],"K3":56,"K4":[78.89],"K6":"Astring"})", result);
}
TEST(BsonPrinterTest, ArrayWithMapValues)
{
    std::stringstream                   stream;
    BsonTestPrinter                     printer(stream);

    std::size_t array1map1Size
            = printer.getSizeMapTest(2)
            + 2 + printer.getSizeValueTest(true)
            + 2 + printer.getSizeValueTest(false);
    std::size_t array1map2Size
            = printer.getSizeMapTest(3)
            + 2 + printer.getSizeValueTest(78.89)
            + 2 + printer.getSizeValueTest(57l)
            + 2 + printer.getSizeValueTest(58ll);
    std::size_t array1Size
            = printer.getSizeArrayTest(4)
            + array1map1Size
            + printer.getSizeValueTest(56)
            + array1map2Size
            + printer.getSizeValueTest(std::string("Astring"));
    printer.openDoc();
    printer.openArray(array1Size);
    printer.openMap(array1map1Size);
    printer.addKey("K1");
    printer.addValue(true);
    printer.addKey("K2");
    printer.addValue(false);
    printer.closeMap();
    printer.addValue(56);
    printer.openMap(array1map2Size);
    printer.addKey("K4");
    printer.addValue(78.89);
    printer.addKey("K5");
    printer.addValue(57l);
    printer.addKey("K6");
    printer.addValue(58ll);
    printer.closeMap();
    printer.addValue(std::string("Astring"));
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    static const char expectedRaw[]
                = "\x59\x00\x00\x00"
                  "\x03" "0\x00" 
                        "\x0F\x00\x00\x00"
                        "\x08" "K1\x00" "\x01"
                        "\x08" "K2\x00" "\x00"
                        "\x00"
                  "\x10" "1\x00" "\x38\x00\x00\x00"
                  "\x03" "2\x00"
                        "\x29\x00\x00\x00"
                        "\x01" "K4\x00" "\x29\x5c\x8f\xc2\xf5\xb8\x53\x40"
                        "\x12" "K5\x00" "\x39\x00\x00\x00\x00\x00\x00\x00"
                        "\x12" "K6\x00" "\x3A\x00\x00\x00\x00\x00\x00\x00"
                        "\x00"
                  "\x02" "3\x00" "\x08\x00\x00\x00" "Astring\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, result);
    //EXPECT_EQ(R"([{"K1":true,"K2":false},56,{"K4":78.89},"Astring"])", result);
}
TEST(BsonPrinterTest, ArrayWithArrayValues)
{
    std::stringstream                   stream;
    BsonTestPrinter                     printer(stream);

    std::size_t array1array1Size
            = printer.getSizeArrayTest(2)
            + printer.getSizeValueTest(true)
            + printer.getSizeValueTest(false);
    std::size_t array1array2Size
            = printer.getSizeArrayTest(3)
            + printer.getSizeValueTest(78.89)
            + printer.getSizeValueTest(57l)
            + printer.getSizeValueTest(58ll);
    std::size_t array1Size
            = printer.getSizeArrayTest(4)
            + array1array1Size
            + printer.getSizeValueTest(56)
            + array1array2Size
            + printer.getSizeValueTest(std::string("Astring"));
    printer.openDoc();
    printer.openArray(array1Size);
    printer.openArray(array1array1Size);
    printer.addValue(true);
    printer.addValue(false);
    printer.closeArray();
    printer.addValue(56);
    printer.openArray(array1array2Size);
    printer.addValue(78.89);
    printer.addValue(57l);
    printer.addValue(58ll);
    printer.closeArray();
    printer.addValue(std::string("Astring"));
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    static const char expectedRaw[]
                = "\x54\x00\x00\x00"
                  "\x04" "0\x00" 
                        "\x0D\x00\x00\x00"
                        "\x08" "0\x00" "\x01"
                        "\x08" "1\x00" "\x00"
                        "\x00"
                  "\x10" "1\x00" "\x38\x00\x00\x00"
                  "\x04" "2\x00"
                        "\x26\x00\x00\x00"
                        "\x01" "0\x00" "\x29\x5c\x8f\xc2\xf5\xb8\x53\x40"
                        "\x12" "1\x00" "\x39\x00\x00\x00\x00\x00\x00\x00"
                        "\x12" "2\x00" "\x3A\x00\x00\x00\x00\x00\x00\x00"
                        "\x00"
                  "\x02" "3\x00" "\x08\x00\x00\x00" "Astring\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, result);
    //EXPECT_EQ(R"([[true,false],56,[78.89],"Astring"])", result);

}
TEST(BsonPrinterTest, CloseMapWithArray)
{
    std::stringstream                   stream;
    BsonTestPrinter                     printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    printer.openDoc();
    printer.openMap(printer.getSizeMapTest(0));
    ASSERT_ANY_THROW(
        printer.closeArray();
    );
}
TEST(BsonPrinterTest, CloseArrayWithMap)
{
    std::stringstream                   stream;
    BsonTestPrinter                     printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    printer.openDoc();
    printer.openArray(printer.getSizeArrayTest(0));
    ASSERT_ANY_THROW(
        printer.closeMap();
    );
}
TEST(BsonPrinterTest, PuttingKeyInArray)
{
    std::stringstream                   stream;
    BsonTestPrinter                     printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    printer.openDoc();
    printer.openArray(printer.getSizeArrayTest(0));
    ASSERT_ANY_THROW(
        printer.addKey("This old house");
    );
}
TEST(BsonPrinterTest, AddRawValueTest)
{
    std::stringstream                   stream;
    BsonTestPrinter                     printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    printer.openDoc();
    printer.openMap(printer.getSizeMapTest(1)
              + 2 + printer.getSizeRawTest(std::string("12").size()));
    printer.addKey("K1");
    printer.addRawValue("12");
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    static const char expectedRaw[]
                = "\x10\x00\x00\x00"
                  "\x05" "K1\x00" "\x02\x00\x00\x00" "\x80" "12"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, result);
    //EXPECT_EQ(result, R"({"K1":12})");
}

