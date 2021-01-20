#pragma once

#include "Configuration.h"
#include "ClassUnit.h"
#include "MethodUnit.h"
#include "PrintUnit.h"

// Абстрактная фабрика с дефолтным конструктором и методами, возвращающие smart pointers ( shared_ptr ) на Класс / Метод / ВыводЮнит
class AbstractFactory
{
public:
    // Возвращает smart ptr ClassUnit
    virtual std::shared_ptr<ClassUnit> CreateClassUnit(const std::string& name, const Configuration::Flags& accFlags = 0, const Configuration::Flags& modFlags = 0) const = 0;

    // Возвращает smart ptr MethodUnit
    virtual std::shared_ptr<MethodUnit> CreateMethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags) const = 0;

    // Возвращает smart ptr PrintUnit
    virtual std::shared_ptr<PrintUnit> CreatePrintOperatorUnit(const std::string& text) const = 0;

    // Дефолтный деструктор, чтобы не писать реализацию как {}, виртуальнй для правильного наследования ( очищения памяти и вызов деструктора, исключение непредвиденных обстоятельств )
    virtual ~AbstractFactory() = default;
};
