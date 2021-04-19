
# ThorSerialize

## Support for

* [Json](https://www.json.org/json-en.html)
* [Yaml](https://yaml.org/)
* [Bson](http://bsonspec.org/) **NEW**

This is a framework for serializing C++ objects to/from stream in some "standard formats" efficiently.
Standard Formats: Currently supported are Json/Yaml/Bson.

It is designed so that no intermediate format it used; data is read directly from the object and placed on the stream, conversely data is read directly from the stream into C++ objects. Note because C++ container con only hold fully formed objects, data is read into temporary object then inserted (moved if possible otherwise copied) into the container.

User defined classes require no additional code to be serialized, only a simple declaration that defines what member need to be serialized. The appropriate declarations for the standard containers has already been provided.

**Note the constructor is not called.**
The serialization class reads/writes built-in data by default and reads/writes these values directly into the members of the object. To read/write non built-in types you must define a serialization for that class. (Note: it is possible to get this library to call the constructors and methods (this is how the standard containers are accessed). But I have not documented this procedure yet as I want to get some good use cases together so I can define a consistent interface for its usage).

## Usage

There are two main functions for export and import that can be used with streams.
```C++ XXX
    <formatName>Exporter(<object>)    eg   jsonExporter(o)
    <formatNAme>Importer(<object>)    eg   jsonImporter(o)
```
The object part of the above declaration is any object that has a type with ThorsAnvil::Serialize::Traits<> declaration defined for that type. Traits declarations are already provided for all std:: container types and it is simple to provide declarations for user defined types (See below).

A simple example of usage would be (link against libThorSerialize14.dynlib)
```C++
    #include "ThorSerialize/SerUtil.h"
    #include "ThorSerialize/JsonThor.h"
    #include "ThorSerialize/BsonThor.h"
    #include <vector>

    namespace TS = ThorsAnvil::Serialize;

    int main()
    {
        std::vector<int>    data { 1, 2, 3, 4, 5, 6, 7, 8 };
        std::cout << TS::jsonExporter(data) << "\n";

        std::ofstream       file("data.bson");
        file << bsonExporter(data);
    }

    // Output
    [1, 2, 3, 4, 5, 6, 7, 8]
```
## User declared Types

User defined classes can be made serialize-able by defining a specialization of the class ThorsAnvil::Serialize::Traits<>.
The macros `ThorsAnvil_MakeTrait` is provided to simplify this for most standard situations. Yes I know macros are nasty. But the idea is to make usage easier and hide the real work. So the macro takes the names of the members (and generates that appropriate type information from the names). A more detailed explanation of how to build a Traits class by hand is provided below.

A simple example of a traits class definition for a user defined type.
```C++
    #include "ThorSerialize/Traits.h"

    namespace TS = ThorsAnvil::Serialize;

    class MyClass
    {
        int             member1;
        double          data2;
        std::string     name;

        // To allow the serialization code access to private members
        // the "Traits<>" must be a friend of the class. If the members are
        // all public then this is not needed.
        friend class TS::Traits<MyClass>;

        public:
            MyClass(int member1, double data2, std::string const& name)
                : member1(member1), data2(data2), name(name)
            {}
    };

    // This macros crates the appropriate Traits class specialized for the
    // user defined class allowing it to be used by jsonImporter() and jsonExporter()
    ThorsAnvil_MakeTrait(MyClass, member1, data2, name);
```

This is all that is need to make a class serialize-able.
```C++
    #include "ThorSerialize/SerUtil.h"
    #include "ThorSerialize/JsonThor.h"
    #include <vector>

    namespace TS = ThorsAnvil::Serialize;

    int main()
    {
        MyClass     object(15, 100.123, "A string");
        std::cout << TS::jsonExporter(object) << "\n";
    }

    // Output
    {"member1":15, "data2": 100.123, "name":"A string"}
```
## Members

A serialize-able class can be a member/parent or contained in another serialize-able with no additional work.

    #include "ThorSerialize/SerUtil.h"
    #include "ThorSerialize/JsonThor.h"
    #include <vector>

    namespace TS = ThorsAnvil::Serialize;

    int main()
    {
        std::vector<MyClass>    vec1{ {23, 89.99, "obj1"}, {67, 89.98. "obj2"}, {32, 23.45, "obj3"}};
        std::cout << TS::jsonExporter(vec1) << "\n";
    }

    // Output
    [{"member1":23, "data2": 89.99, "name":"obj1"}, {"member1":67, "data2": 89.98, "name":"obj2"}, {"member1":32, "data2": 23.45, "name":"obj3"}]

## Inheriting

A user defined class that inherits from a serialize-able class can also be extended the serializable attributes but you must a slightly different macro:

    #include "MyClass.h"
    #include "ThorSerialize/Traits.h"


    namespace TS = ThorsAnvil::Serialize;

    class MySubClass: public MyClass
    {
        std::string     parentName;

        // To allow the serialization code access to private members
        // the "Traits<>" must be a friend of the class. If the members are
        // all public then this is not needed.
        friend class TS::Traits<MySubClass>;

        public:
            MySubClass(int member1, double data2, std::string const& name, std::string const& parentName)
                : MyClass(member1, data2, name)
                , parentName(parentName)
            {}
    };

    // This macros crates the appropriate Traits class specialized for the
    // user defined class allowing it to be used by jsonImporter() and jsonExporter()
    ThorsAnvil_ExpandTrait(MyClass, MySubClass, parentName);

The only real difference is exchanging the `ThorsAnvil_MakeTrait` for `ThorsAnvil_ExpandTrait` macro. Both macros accept any number of field names.

## Serialization Formats

Currently the framework exposes three specific format types (Json/Yaml/Bson). But it has been designed to be easily extended to support other formats that may be useful. The basis for other formats is defined via the ParserInterface and PrinterInterface classes.


A framework for implementing parsers onto.

For each implementation we expect to see:

    File:               Class:              Description:
    ====================================================
    <Name>Printer.h     <Name>Printer       A class that implements the PrinterInterface (defined in Serialize.h)
    <Name>Parser.h      <Name>Parser        A class that implements the ParserInterface (defined in Serialize.h)
    <Name>Thor.h        Name                A class "Name" that defines the names of the printer and parser types.
                        <name>Import        Import/Export function that simply wrap the Import/Export functions
                        <name>Export        generic function (using "Name") as input.

Other Files to make Serialization automatic:

    File:               Class:              Description:
    ====================================================
    Serialize.h         ParserInterface     An interface to parsing used by DeSerialize
                        PrinterInterface    An interface to printing used by Serialize
                        Serializer<T>       Generic serialize class that uses Traits<T> and <Name>PrinterInterface
                        DeSerializer<T>     Generic de-serializer class that uses Traits<T> and <Name>ParserInterface

    Exporter.h          Exporter (class)                        Used to interact with stream.
                        Export   (wrapper to create Exporter)   Specializations should just wrap these
    Importer.h          Importer (class)
                        Import   (wraooer to create Importer)

    Traits.h            Traits<T>
                        Macros: ThorsAnvil_MakeTrait    Simplifies the creation of Traits for user types.

    SerUtil.h           Traits<std::pair<A,B>>          Provides traits for all the standard containers.
                        Traits<std::array<T, N>>
                        Traits<std::list<T>>
                        Traits<std::vector<T>>
                        Traits<std::deque<T>>
                        Traits<std::set<T>>
                        Traits<std::multiset<T>>
                        Traits<std::map<K, V>>
                        Traits<std::multimap<K, V>>


    UnicodeIterator.h   Iterator for replacing escape characters with their actual encodings for use inside the application.
                        Should be used by the <XXX>Parser class on strings that can contain escape characters.


Usage:

    #include "Serialize.h"
    #include "JsonThor.h"
    #include "YamlThor.h"
    #include "BsonThor.h"

    namespace TS = ThorsAnvil::Serialize;

    std::cout << TS::jsonExporter(object1);
    std::cin  >> TS::jsonImporter(object1);

    std::cout << TS::yamlExporter(object1);
    std::cin  >> TS::yamlImporter(object1);

    std::cout << TS::bsonExporter(object1);
    std::cin  >> TS::bsonImporter(object1);

All standard types have a serialization defined for them. To add one for your class.

    class MyClass
    {
        int             value1;
        double          data;
        std::string     descriptions;

        friend class ThorsAnvil::Serialize::Traits<MyClass>;
        public:
            // STUFF
    };

    ThorsAnvil_MakeTrait(MyClass, value1, data, descriptions)




