#ifndef DEPRICATED_TEST_H
#define DEPRICATED_TEST_H

#include "Traits.h"
#include <iostream>
#include <string>

namespace DepricatedTypeSpace
{

struct CustomSerialize
{
    int value;
    // required by ThorsAnvil_MakeTraitCustom to serialize the data.
    friend std::ostream& operator<<(std::ostream& stream, CustomSerialize const& data)
    {
        return stream << data.value;
    }
};

struct NormalObject
{
    std::string         name;
    CustomSerialize     value;
};


}

ThorsAnvil_MakeTraitCustom(DepricatedTypeSpace::CustomSerialize);
ThorsAnvil_MakeTrait(DepricatedTypeSpace::NormalObject, name, value);

#endif
