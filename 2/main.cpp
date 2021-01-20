#include <iostream>

#include "CPP_AbstractFactory.h"
#include "CSHARP_AbstractFactory.h"
#include "JAVA_AbstractFactory.h"
#include "Tests.h"

std::string generate();

int main(int argc, char* argv[])
{
    // Для проверки на утечку памяти
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    // Пример утечки, раскомментируйте, чтобы посмотреть что выведет консоль ( она укажет на не очищенную область в ОП )
    //int* a = new int;

    std::cout << generate() << std::endl;

    Tests tests;

    /*std::ofstream file("test.txt");

    for (const auto& it : generate())
    {
        file << it;
    }

    file.close();*/

    // Нажмите 'enter'
    return getchar();
}

std::string generate()
{
    try
    {
        std::string result;

        for (int i = 0; i < 3; ++i)
        {
            std::shared_ptr<AbstractFactory> factory;

            switch (i)
            {
                // создаём фабрику языка c++
            case 0:
                factory = std::make_shared<CPP_AbstractFactorty>();
                break;

                // создаём фабрику языка c#
            case 1:
                factory = std::make_shared<CSHARP_AbstractFactory>();
                break;

                // создаём фабрику языка java
            case 2:
                factory = std::make_shared<JAVA_AbstractFactory>();
                break;

                // невозможная ситуация для данного цикла, но в случае если попадём сюда, то ничего критичного не случится
                // этот аттрибут используются в основном для case`ов сообщающий компилятору, что break не обязателен
            default: [[__fallthrough]];
            }

            // smart ptr класса (инициализируем)
            std::shared_ptr<ClassUnit> myClass(factory->CreateClassUnit("MyClass"));
            //std::shared_ptr<ClassUnit> myClass(nullptr);
            // smart ptr метода (инициализируем)
            //std::shared_ptr<MethodUnit> method(nullptr);
            std::shared_ptr<MethodUnit> method(factory->CreateMethodUnit("testFunc4", "void", Configuration::Modifier::STATIC));

            // добавляем в класс юниты (функции)
            if (myClass)
            {
                myClass->add(factory->CreateMethodUnit("testFunc1", "void", 0), Configuration::AccessModifier::PUBLIC);
                myClass->add(factory->CreateMethodUnit("testFunc2", "void", Configuration::Modifier::STATIC), Configuration::AccessModifier::PRIVATE);
                myClass->add(factory->CreateMethodUnit("testFunc3", "void", Configuration::Modifier::VIRTUAL | Configuration::Modifier::CONST), Configuration::AccessModifier::PUBLIC);
            }

            if (method)
                // производим дополнение в методе как добавление вывода текста
                method->add(factory->CreatePrintOperatorUnit("Hello, UnitedTimur! ;)"), 0x0);

            if (myClass)
                // добавляем этот метод в класс
                myClass->add(method, Configuration::AccessModifier::PROTECTED);

            if (myClass)
                // производим генерацию
                result += myClass->compile() + '\n';
        }

        // возвращаем результат
        return result;
    }
    catch (const std::exception& ex)
    {
        return std::string("An error has appeared in " + std::string(ex.what()));
    }
}
