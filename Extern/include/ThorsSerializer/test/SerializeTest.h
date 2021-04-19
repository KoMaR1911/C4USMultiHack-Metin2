
#ifndef THORS_ANVIL_SERIALIZE_TEST_SERIALIZE_TEST_EXTRA_H
#define THORS_ANVIL_SERIALIZE_TEST_SERIALIZE_TEST_EXTRA_H

#include "Traits.h"
#include "Serialize.h"
#include "Serialize.tpp"

namespace SerializeTest
{

enum RGB { Red, Green, Blue };
struct EumHolder
{
    RGB value;
};
enum Flag { empty = 0, One = 1, Two = 2, Three = 4};

// Added after an issue with enum's with 8 or 9 items
enum class OctalValues { OCT1, OCT2, OCT3, OCT4, OCT5, OCT6, OCT7, OCT8 };

class SerializeTestExtra
{
    public:
    int         theInteger;
    double      aNonRealValue;
    bool        test;
    std::string normalString;

    friend class ThorsAnvil::Serialize::Traits<SerializeTestExtra>;
    public:
        SerializeTestExtra()
        {}
        SerializeTestExtra(int theInteger, double aNonRealValue, bool test, std::string const& normalString)
            : theInteger(theInteger)
            , aNonRealValue(aNonRealValue)
            , test(test)
            , normalString(normalString)
        {}
        ~SerializeTestExtra()
        {}
        SerializeTestExtra(SerializeTestExtra const&)             = delete;
        SerializeTestExtra& operator=(SerializeTestExtra const&)  = delete;
};

class SerializeExact: public SerializeTestExtra
{
    int     anotherValue;
    friend class ThorsAnvil::Serialize::Traits<SerializeExact>;
    public:
        using SerializeTestExtra::SerializeTestExtra;
};

class SerializeExactNoMembers: public SerializeTestExtra
{
    public:
        using SerializeTestExtra::SerializeTestExtra;
};

class SerializeExactNoMembersPoly: public SerializeTestExtra
{
    public:
        using SerializeTestExtra::SerializeTestExtra;
	ThorsAnvil_PolyMorphicSerializer(SerializeExactNoMembersPoly);
};

class SerializeTestChild: public SerializeTestExtra
{
    public:
    int data1;
    int data2;

    friend class ThorsAnvil::Serialize::Traits<SerializeTestChild>;
    public:
        SerializeTestChild()
        {}
        SerializeTestChild(int data1, int data2, int theInteger, double aNonRealValue, bool test, std::string const& normalString)
            : SerializeTestExtra(theInteger, aNonRealValue, test, normalString)
            , data1(data1)
            , data2(data2)
        {}
};

class SerializeTestMembers
{
    public:
    SerializeTestExtra member1;
    SerializeTestChild member2;

    friend class ThorsAnvil::Serialize::Traits<SerializeTestMembers>;
    public:
        SerializeTestMembers()
        {}
        SerializeTestMembers(int data1, int data2, int theInteger, double aNonRealValue, bool test, std::string const& normalString)
            : member1(theInteger, aNonRealValue, test, normalString)
            , member2(data1, data2, theInteger, aNonRealValue, test, normalString)
        {}
};

struct CornerCaseClass
{
    int value;
    virtual ~CornerCaseClass() {}
    ThorsAnvil_PolyMorphicSerializer(CornerCaseClass);
};

}

ThorsAnvil_MakeEnum(SerializeTest::RGB, Red, Green, Blue);
ThorsAnvil_MakeEnum(SerializeTest::OctalValues, OCT1, OCT2, OCT3, OCT4, OCT5, OCT6, OCT7, OCT8);
ThorsAnvil_MakeTrait(SerializeTest::EumHolder, value);
ThorsAnvil_MakeTrait(SerializeTest::SerializeTestExtra, theInteger, aNonRealValue, test, normalString);
ThorsAnvil_ExpandTrait(SerializeTest::SerializeTestExtra, SerializeTest::SerializeExact, anotherValue);
ThorsAnvil_ExpandTrait(SerializeTest::SerializeTestExtra, SerializeTest::SerializeTestChild, data1, data2);
ThorsAnvil_MakeTrait(SerializeTest::SerializeTestMembers, member1, member2);
ThorsAnvil_MakeTrait(SerializeTest::CornerCaseClass, value);
ThorsAnvil_ExpandTrait(SerializeTest::SerializeTestExtra, SerializeTest::SerializeExactNoMembers);
ThorsAnvil_ExpandTrait(SerializeTest::SerializeTestExtra, SerializeTest::SerializeExactNoMembersPoly);
ThorsAnvil_MakeEnumFlag(SerializeTest::Flag, One, Two, Three);


#endif

