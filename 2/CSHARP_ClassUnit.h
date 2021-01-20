#pragma once

#include "ClassUnit.h"

class CSHARP_ClassUnit : public ClassUnit
{
public:
    // См. ClassUnit.h
    explicit CSHARP_ClassUnit(const std::string& name, const Configuration::Flags& flags = Configuration::AccessModifier::PRIVATE);
    void add(const Configuration::Ptr& unit, const Configuration::UI& flags) override;
    std::string compile(const Configuration::UI& level) const override;

private:
    // Поле модификатора доступа класса
    Configuration::Flags _accMod;
};

inline CSHARP_ClassUnit::CSHARP_ClassUnit(const std::string& name, const Configuration::Flags& flags) :
    ClassUnit(name),
    _accMod(flags)
{
    // Так как в c# 6 модификаторов доступа, то выставляем значение по аналогии в CPP_ClassUnit на 6 (см. Configuration.h)
    _fields.resize(0x06);
}

inline void CSHARP_ClassUnit::add(const Configuration::Ptr& unit, const Configuration::UI& flags)
{
    if (unit == nullptr)
        THROW(__FUNCTION__);

    // По аналогии с CPP_ClassUnit.h
    unsigned accessModifier = Configuration::AccessModifier::PRIVATE;

    if (flags < 0x06)
        accessModifier = flags;

    _fields[accessModifier].push_back(unit);
;}

inline std::string CSHARP_ClassUnit::compile(const Configuration::UI& level) const
{
    // Производим генерацию модификатора доступа + имя класса
    std::string result = generateShift(level) + Configuration::ACCESS_MODIFIERS[_accMod] + " class " + _name + " {\n";

    // Проходимся по всем полям класса
    for (size_t i = 0; i < _fields.size(); ++i)
    {
        // Если в модификаторе нет юнитов, то пропускаем
        if (_fields[i].empty())
            continue;

        // В поле модификатора собираем каждый юнит и генерируем их с отступами и модификаторами доступа
        for (const auto& field : _fields[i])
            result += generateShift(level + 1) + Configuration::ACCESS_MODIFIERS[i] + ' ' + field->compile(level + 1);

        result += '\n';
    }

    // По аналогии с CPP_ClassUnit
    result += generateShift(level) + "};\n";

    return result;
}
