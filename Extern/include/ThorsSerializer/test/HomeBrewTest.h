#include "JsonThor.h"
#include "SerUtil.h"

struct HomeBrewBlock
{
    std::string             key;
    int                     code;
};

ThorsAnvil_MakeTrait(HomeBrewBlock, key, code);

