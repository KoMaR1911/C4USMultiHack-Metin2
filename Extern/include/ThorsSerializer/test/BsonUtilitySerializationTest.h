#include "Traits.h"
#include "MongoUtility.h"

class MongoObjectID
{
    ThorsAnvil::Serialize::MongoUtility::ObjectID id;
    friend class ThorsAnvil::Serialize::Traits<MongoObjectID>;
    public:
        MongoObjectID(std::int32_t timestamp, std::int64_t random, std::int32_t counter)
            : id(timestamp, random, counter)
        {}
        bool operator==(MongoObjectID const& rhs) const {return id == rhs.id;}
};
class MongoUTCDateTime
{
    ThorsAnvil::Serialize::MongoUtility::UTCDateTime dt;
    friend class ThorsAnvil::Serialize::Traits<MongoUTCDateTime>;
    public:
        MongoUTCDateTime(std::int64_t timestamp)
            : dt(timestamp)
        {}
        bool operator==(MongoUTCDateTime const& rhs) const {return dt == rhs.dt;}
};
class MongoBsonTimeStamp
{
    ThorsAnvil::Serialize::MongoUtility::BsonTimeStamp ts;
    friend class ThorsAnvil::Serialize::Traits<MongoBsonTimeStamp>;
    public:
        MongoBsonTimeStamp(std::int32_t timestamp, int inc)
            : ts(timestamp, inc)
        {}
        bool operator==(MongoBsonTimeStamp const& rhs) const {return ts == rhs.ts;}
};

class MongoBsonBinaryObj
{
        std::string buffer;
    friend class ThorsAnvil::Serialize::Traits<MongoBsonBinaryObj>;
    public:
        MongoBsonBinaryObj(std::string const& data)
            : buffer(data)
        {}
        bool operator==(MongoBsonBinaryObj const& rhs) const {return buffer == rhs.buffer;}

        std::size_t getSize() const             {return buffer.size();}
        void        resize(std::size_t size)    {buffer.resize(size);}
        char const* getBuffer() const           {return &buffer[0];}
        char*       getBuffer()                 {return &buffer[0];}
};

struct MongoBsonJsavScriptObj
{
    std::vector<char>   buffer;
    friend class ThorsAnvil::Serialize::Traits<MongoBsonJsavScriptObj>;
    public:
        MongoBsonJsavScriptObj(std::string const& value)
            : buffer(std::begin(value), std::end(value))
        {}
        bool operator==(MongoBsonJsavScriptObj const& rhs) const {return buffer == rhs.buffer;}
        std::size_t getSize() const             {return buffer.size();}
        void        resize(std::size_t size)    {buffer.resize(size);}
        char const* getBuffer() const           {return &buffer[0];}
        char*       getBuffer()                 {return &buffer[0];}
};

struct MongoBsonRegExObj
{
    std::string pat;
    std::string opt;
    friend class ThorsAnvil::Serialize::Traits<MongoBsonRegExObj>;
    public:
        MongoBsonRegExObj(std::string const& p, std::string const& o)
            : pat(p)
            , opt(o)
        {}
        bool operator==(MongoBsonRegExObj const& rhs) const {return std::tie(pat, opt) == std::tie(rhs.pat, rhs.opt);}
        std::string const& pattern() const      {return pat;}
        std::string const& options() const      {return opt;}
        std::string&       pattern()            {return pat;}
        std::string&       options()            {return opt;}
};

class MongoBsonBinary
{
    friend class ThorsAnvil::Serialize::Traits<MongoBsonBinary>;
    MongoBsonBinaryObj  binary;
    public:
        MongoBsonBinary(std::string const& value)
            : binary(value)
        {}
        bool operator==(MongoBsonBinary const& rhs) const {return binary == rhs.binary;}
};
class MongoBsonJsavScript
{
    friend class ThorsAnvil::Serialize::Traits<MongoBsonJsavScript>;
    MongoBsonJsavScriptObj  javascript;
    public:
        MongoBsonJsavScript(std::string const& value)
            : javascript(value)
        {}
        bool operator==(MongoBsonJsavScript const& rhs) const {return javascript == rhs.javascript;}
};
class MongoBsonRegExp
{
    friend class ThorsAnvil::Serialize::Traits<MongoBsonRegExp>;
    MongoBsonRegExObj  regex;
    public:
        MongoBsonRegExp(std::string const& p, std::string const& o)
            : regex(p, o)
        {}
        bool operator==(MongoBsonRegExp const& rhs) const {return regex == rhs.regex;}
};



ThorsAnvil_MakeTraitCustomSerialize(MongoBsonBinaryObj,     ThorsAnvil::Serialize::MongoUtility::BinarySerializer<MongoBsonBinaryObj>);
ThorsAnvil_MakeTraitCustomSerialize(MongoBsonJsavScriptObj, ThorsAnvil::Serialize::MongoUtility::JavascriptSerializer<MongoBsonJsavScriptObj>);
ThorsAnvil_MakeTraitCustomSerialize(MongoBsonRegExObj,      ThorsAnvil::Serialize::MongoUtility::RegExSerializer<MongoBsonRegExObj>);

ThorsAnvil_MakeTrait(MongoObjectID,        id);
ThorsAnvil_MakeTrait(MongoUTCDateTime,     dt);
ThorsAnvil_MakeTrait(MongoBsonTimeStamp,   ts);
ThorsAnvil_MakeTrait(MongoBsonBinary,      binary);
ThorsAnvil_MakeTrait(MongoBsonJsavScript,  javascript);
ThorsAnvil_MakeTrait(MongoBsonRegExp,      regex);

