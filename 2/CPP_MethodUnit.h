#pragma once

#include "MethodUnit.h"

class CPP_MethodUnit : public MethodUnit
{
public:
    // См. MethodUnit.h
    explicit CPP_MethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags);
    void add(const Configuration::Ptr& unit, const Configuration::Flags& flags) override;
    std::string compile(const Configuration::UI& level) const override;
};

inline CPP_MethodUnit::CPP_MethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags) :
    MethodUnit(name, returnType, flags)
{
}

inline void CPP_MethodUnit::add(const Configuration::Ptr& unit, const Configuration::Flags& /*flags*/)
{
    if (unit == nullptr)
        THROW(__FUNCTION__);

    // В тело метода добавляем юнит
    _body.push_back(unit);
}

inline std::string CPP_MethodUnit::compile(const Configuration::UI& level) const
{
    // Производим нужные сдвиги
    std::string result = generateShift(level);

    // Если бит флага установлен на STATIC, то метод статичный
    if (_flags & Configuration::Modifier::STATIC)
        result += "static ";
    // если бит VIRTUAL, то метод виртуальный
    else if (_flags & Configuration::Modifier::VIRTUAL)
        result += "virtual ";

    // Добавляем возвращаемый тип и имя метода
    result += _returnType + ' ' + _name + "()";

    // Если имеет спецификатор CONST, добавим это
    if (_flags & Configuration::Modifier::CONST)
        result += " const";

    result += " {\n";

    // Производим генерацию с нужными отступами
    for (const auto& it : _body)
        result += it->compile(level + 1);

    result += generateShift(level) + "}\n";

    // Возвращаем результат
    return result;
}
