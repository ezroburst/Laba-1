#pragma once

#include "MethodUnit.h"

class JAVA_MethodUnit : public MethodUnit
{
public:
    // См. MethodUnit.h
    explicit JAVA_MethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags);
    void add(const Configuration::Ptr& unit, const Configuration::Flags& flags) override;
    std::string compile(const Configuration::UI& level) const override;
};

inline JAVA_MethodUnit::JAVA_MethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags) :
    MethodUnit(name, returnType, flags)
{
}

inline void JAVA_MethodUnit::add(const Configuration::Ptr& unit, const Configuration::Flags& /*flags*/)
{
    if (unit == nullptr)
        THROW(__FUNCTION__);

    // Добавляем в тело метода юнит
    _body.push_back(unit);
}

inline std::string JAVA_MethodUnit::compile(const Configuration::UI& level) const
{
    std::string result;

    // По аналогии с CSHARP_MethodUnit проверяем наличие установленых битов в 1
    // Для работы с многопоточностью
    if (_flags & Configuration::Modifier::SYNCHRONIZED)
        result += "synchronized ";

    // Метод статичный
    if (_flags & Configuration::Modifier::STATIC)
        result += "static ";

    // Метод абстрактный ( почти как чистая функция в плюсах )
    if (_flags & Configuration::Modifier::ABSTRACT)
        result += "abstract ";

    // Метод помечен как final
    else if (_flags & Configuration::Modifier::FINAL)
        result += "final ";

    // Добавляем возвращаемый тип и имя метода
    result += _returnType + ' ' + _name + "()" + " {\n";

    // Проходим по всему телу и генереруем метод
    for (const auto& it : _body)
        result += it->compile(level + 1);

    // По аналогии с CPP_MethodUnit
    result += generateShift(level) + "}\n";

    return result;
}

