#ifndef THORS_ANVIL_SERIALIZE_BSON_PARSER_H
#define THORS_ANVIL_SERIALIZE_BSON_PARSER_H
/*
 * BsonParser<T>
 *      This is used in conjunction with BsonPrinter<T>
 *
 *      Together these provide an implementation of:
 *          the ParserInterface for type T
 *          and PrinterInterface for type T
 *
 *      These Interfaces are used by Serializer and DeSerializer (see Serialize.h)
 *
 *      It uses ThorsAnvil::Serialize::Traits<T> to know what objects to pull from the stream.
 *      For arrays order is important.
 *      For Objects the order of elements is not important. It looks up the key in the Traits<T>
 *      information to understand which member is being de-serialized but unspecified elements
 *      will not cause an error.
 */

#include "Serialize.h"
#include "BsonUtil.h"
#include "ThorsIOUtil/Utility.h"
#include "ThorsLogging/ThorsLogging.h"
#include <GitUtility/ieee754_types.h>
#include <boost/endian/conversion.hpp>
#include <istream>
#include <string>
#include <vector>

namespace ThorsAnvil
{
    namespace Serialize
    {
        class BsonParser;
        namespace MongoUtility
        {
            class UTCDateTime;
            BsonParser& operator>>(BsonParser& parser, MongoUtility::UTCDateTime& data);
        }

class BsonParser: public ParserInterface
{
    friend BsonParser& MongoUtility::operator>>(BsonParser& parser, MongoUtility::UTCDateTime& data);

    std::vector<BsonContainer>  currentContainer;
    std::vector<std::size_t>    dataLeft;
    std::vector<std::size_t>    dataSize;
    ParserToken                 nextToken;
    std::string                 nextKey;
    char                        nextType;
    bool                        skipOverValue;


    public:
        BsonParser(std::istream& stream, ParserConfig config = ParserConfig{});
        virtual FormatType formatType()                         override {return FormatType::Bson;}
        virtual ParserToken getNextToken()                      override;
        virtual std::string getKey()                            override;

        virtual void    ignoreDataValue()                       override;

        virtual void    getValue(short int& value)              override    {value = getIntValue<MaxTemplate<4, sizeof(short int)>::value, short int>();}
        virtual void    getValue(int& value)                    override    {value = getIntValue<sizeof(int), int>();}
        virtual void    getValue(long int& value)               override    {value = getIntValue<sizeof(long int), long int>();}
        virtual void    getValue(long long int& value)          override    {value = getIntValue<sizeof(long long int), long long int>();}

        virtual void    getValue(unsigned short int& value)     override    {value = getIntValue<MaxTemplate<4, sizeof(unsigned short int)>::value, unsigned short int>();}
        virtual void    getValue(unsigned int& value)           override    {value = getIntValue<sizeof(unsigned int), unsigned int>();}
        virtual void    getValue(unsigned long int& value)      override    {value = getIntValue<sizeof(unsigned long int), unsigned long int>();}
        virtual void    getValue(unsigned long long int& value) override    {value = getIntValue<sizeof(unsigned long long int), unsigned long long int>();}

        virtual void    getValue(float& value)                  override    {value = getFloatValue<8, float>();}
        virtual void    getValue(double& value)                 override    {value = getFloatValue<8, double>();}
        virtual void    getValue(long double& value)            override    {value = getFloatValue<8, long double>();}

        virtual void    getValue(bool& value)                   override    {if (nextType != '\x08')    {badType();}value = readBool();}

        virtual void    getValue(std::string& value)            override    {if (nextType != '\x02')    {badType();}value = readString();}

        virtual bool    isValueNull()                           override    {return (nextType == '\x0A');}

        virtual std::string getRawValue()                       override;

        void useStreamData(std::size_t amount) {dataLeft.back() -= amount;}

    public:
        char getValueType() const     {return nextType;}
        template<std::size_t size, typename Int> Int readLE()
        {
            Int docSize;
            input.read(reinterpret_cast<char*>(&docSize), size);
            return boost::endian::little_to_native(docSize);
        }

        template<std::size_t size, typename Int> Int readBE()
        {
            Int docSize = 0;
            input.read(reinterpret_cast<char*>(&docSize) + (sizeof(docSize) - size), size);
            return boost::endian::big_to_native(docSize);
        }


    private:
        template<std::size_t size, typename Int>
        Int readSize();
        bool isEndOfContainer(std::size_t unread);
        std::size_t peekSize();

        void readEndOfContainer();

        template<std::size_t Size, typename Int>
        Int getIntValue();
        template<std::size_t Size, typename Float>
        Float getFloatValue();

        void readKey();

        template<std::size_t Size, typename Int>
        Int readInt();

        template<std::size_t Size>
        IEEE_754::_2008::Binary<Size * 8> readFloat();

        bool readBool();
        std::string readString();
        void readNull();
        std::string readBinary();

        [[noreturn]]
        void badType()
        {
            ThorsLogAndThrow("ThorsAnvil::Serialize::BsonParser",
                             "badType",
                             "Trying to read a type that we can can't convert.");
        }
};
    }
}

#if defined(HEADER_ONLY) && HEADER_ONLY == 1
#include "BsonParser.source"
#endif

#endif
