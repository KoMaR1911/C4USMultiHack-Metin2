#include "Traits.h"
#include "Serialize.h"
#include <string>
#include <memory>

namespace SmartPtrTest
{
    struct Object
    {
        int         id;
        std::string name;
    };
}
struct Wrapper
{
    SmartPtrTest::Object* data;
};
struct WrapperUni
{
    std::unique_ptr<SmartPtrTest::Object> data;
};
struct WrapperShared
{
    std::shared_ptr<SmartPtrTest::Object> data;
};

ThorsAnvil_MakeTrait(SmartPtrTest::Object, id, name);
ThorsAnvil_MakeTrait(Wrapper, data);
ThorsAnvil_MakeTrait(WrapperUni, data);
ThorsAnvil_MakeTrait(WrapperShared, data);

