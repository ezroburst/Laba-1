#pragma once

#include "MethodUnit.h"

class CSHARP_MethodUnit : public MethodUnit
{
public:
    // См. MethodUnit.h
    explicit CSHARP_MethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags);
    void add(const Configuration::Ptr& unit, const Configuration::Flags& flags) override;
    std::string compile(const Configuration::UI& level) const override;
};

inline CSHARP_MethodUnit::CSHARP_MethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags) :
    MethodUnit(name, returnType, flags)
{
}

inline void CSHARP_MethodUnit::add(const Configuration::Ptr& unit, const Configuration::Flags& /*flags*/)
{
    if (unit == nullptr)
        THROW(__FUNCTION__);

    // Добавление юнита в тело метода
    _body.push_back(unit);
}

inline std::string CSHARP_MethodUnit::compile(const Configuration::UI& level) const
{
    std::string result;

    // По аналогии с CPP_MethodUnit проверяем все биты и добавляем к результаты нужные модификаторы
    if (_flags & Configuration::Modifier::ABSTRACT && !(_flags & Configuration::Modifier::ASYNC))
        result += "abstract ";

    // Модификатор как const в c++
    if (_flags & Configuration::Modifier::SEALED)
        result += "sealed ";

    // Модификатор ассинхронной работы метода, для многопоточности
    if (_flags & Configuration::Modifier::ASYNC)
        result += "async ";

    // Модификатор позволяющий напрямую работать с памятью ( указатели / ссылки )
    if (_flags & Configuration::Modifier::UNSAFE)
        result += "unsafe ";

    // Виртуальный ли метод
    if (_flags & Configuration::Modifier::VIRTUAL)
        result += "virtual ";

    // Статичный ли метод
    if (_flags & Configuration::Modifier::STATIC)
        result += "static ";

    // Добавляем возвращаемый тип и имя метода
    result += _returnType + ' ' + _name + "()" + " {\n";

    // Генерируем результат с нужными отсупами в теле
    for (const auto& it : _body)
        result += it->compile(level + 1);

    result += generateShift(level) + "}\n";

    return result;
}
