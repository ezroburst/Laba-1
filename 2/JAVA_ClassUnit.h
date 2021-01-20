#pragma once

#include "ClassUnit.h"

class JAVA_ClassUnit : public ClassUnit
{
public:
    // См. ClassUnit.h
    explicit JAVA_ClassUnit(const std::string& name, const Configuration::Flags& flags = Configuration::AccessModifier::PUBLIC, const Configuration::Flags& accMod = 0);
    void add(const Configuration::Ptr& unit, const Configuration::UI& flags) override;
    std::string compile(const Configuration::UI& level) const override;

private:
    // Модификаторы доступа
    Configuration::Flags _accMod;
    Configuration::Flags _classMod;
};

inline JAVA_ClassUnit::JAVA_ClassUnit(const std::string& name, const Configuration::Flags& flags, const Configuration::Flags& accMod) :
    ClassUnit(name),
    _accMod(flags),
    _classMod(0x00)
{
    // В JAVA как и в C++ 3 модификатора доступа
    _fields.resize(0x03);

    // Если же биты флагов отмечены на Final ( класс запрещающий наследовать себя ), то выставляем эти биты в _classMod
    if (_accMod & Configuration::Modifier::FINAL)
        _classMod |= Configuration::Modifier::FINAL;
    // Аналогично с abstract
    else if (_accMod & Configuration::Modifier::ABSTRACT)
        _classMod |= Configuration::Modifier::ABSTRACT;
}

inline void JAVA_ClassUnit::add(const Configuration::Ptr& unit, const Configuration::UI& flags)
{
    if (unit == nullptr)
        THROW(__FUNCTION__);

    // По аналогии с CPP_ClassUnit.h
    unsigned accessModifier = Configuration::AccessModifier::PRIVATE;

    if (flags < 0x03)
        accessModifier = flags;

    _fields[accessModifier].push_back(unit);
;}

inline std::string JAVA_ClassUnit::compile(const Configuration::UI& level) const
{
    // Добавляем модификатор доступа к классу
    std::string accMod = Configuration::ACCESS_MODIFIERS[_accMod] + ' ';
    std::string classMod;

    // Запомнили выбор из констктора и теперь добавляем спецификаторы final или abstract к классу ( при условии что биты такие установлены в 1 )
    if (_classMod & Configuration::Modifier::FINAL)
        classMod = "final ";
    else if (_classMod & Configuration::Modifier::ABSTRACT)
        classMod = "abstract ";

    // Генерируем модификатор / имя класса
    std::string result = generateShift(level) + accMod + classMod + "class " + _name + " {\n";

    // Проходим по всем модификаторам
    for (size_t i = 0; i < _fields.size(); ++i)
    {
        // Если public например пусто, то пропускаем
        if (_fields[i].empty())
            continue;

        // Генерурем в каждом поле доступа свои юниты
        for (const auto& field : _fields[i])
            result += generateShift(level + 1) + Configuration::ACCESS_MODIFIERS[i] + ' ' + field->compile(level + 1);

        result += '\n';
    }

    // По аналогии с CPP_ClassUnit.h
    result += generateShift(level) + "};\n";

    return result;
}
