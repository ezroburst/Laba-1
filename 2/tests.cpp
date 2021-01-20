#include "Tests.h"
#include <AbstractFactory.h>
#include <CPP_AbstractFactory.h>
#include <cassert>
#include <fstream>
#include <iostream>

Tests::Tests()
{
    testCpp();
}

void Tests::testCpp()
{
    /*std::string result = "class MyClass {\n\
public:\n\
    void testFunc1() {\n\
    }\n\
    virtual void testFunc3() const {\n\
    }\n\n\
\
protected:\n\
    static void testFunc4() {\n\
        printf( \"Hello, UnitedTimur! ;)\" );\n\
    }\n\n\
\
private:\n\
    static void testFunc2() {\n\
    }\n\
\n\
};\n";*/

    auto firstTest = [&]() -> bool
    {
        std::shared_ptr<AbstractFactory> factory(new CPP_AbstractFactorty());

        std::shared_ptr<MethodUnit> method(factory->CreateMethodUnit("testFunc4", "void", Configuration::Modifier::STATIC));

        std::string test = method->compile(0);

        std::string result = "static void testFunc4() {\n\
}\n";

        for (size_t i = 0; i < test.size(); ++i)
            if (test[i] != result[i])
                return false;

        return true;
    };

    auto secondTest = [&]() -> bool
    {
        std::shared_ptr<AbstractFactory> factory(new CPP_AbstractFactorty());

        //myClass->add(factory->CreateMethodUnit("testFunc3", "void", Configuration::Modifier::VIRTUAL | Configuration::Modifier::CONST), Configuration::AccessModifier::PUBLIC);
    };

    assert(firstTest());
}
