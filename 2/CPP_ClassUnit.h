#pragma once

#include "ClassUnit.h"

class CPP_ClassUnit : public ClassUnit
{
public:
    // Конструктор принимает имя
    explicit CPP_ClassUnit(const std::string& name);

    // См. Unit.h
    void add(const Configuration::Ptr& unit, const Configuration::UI& flags) override;
    std::string compile(const Configuration::UI& level) const override;
};

inline CPP_ClassUnit::CPP_ClassUnit(const std::string& name) :
    ClassUnit(name)
{
    // Так как в c++ только 3 модификатора доступа у класса, то и размер выставляем как 3 ( для pubulic, protected, private )
    _fields.resize(0x03);
}

inline void CPP_ClassUnit::add(const Configuration::Ptr& unit, const Configuration::UI& flags)
{
    if (unit == nullptr)
        THROW(__FUNCTION__);

    // Выставляем модификатор доступа на случай ошибки ( по умолчанию вставим в private )
    unsigned accessModifier = Configuration::AccessModifier::PRIVATE;

    // Если модификатор существует, то всё ок
    if (flags < 0x03)
        accessModifier = flags;

    // Вставляем в нужную область (public, protected, private) свой Unit
    _fields[accessModifier].push_back(unit);
}

inline std::string CPP_ClassUnit::compile(const Configuration::UI& level) const
{
    // Производим генерацию класса
    std::string result = generateShift(level) + "class " + _name + " {\n";

    // Проходимся по всем полям модификаторов
    for (size_t i = 0; i < _fields.size(); ++i)
    {
        // Если в поле модификатора ничего нет, то переходим на следующую итерацию
        if (_fields[i].empty())
            continue;

        // Добавляем к result имя модификатора
        result += Configuration::ACCESS_MODIFIERS[i] + ":\n";

        // Проходимся по всем юнитам в поле модификатора и генерируем модификаторы, потом добавляем их
        for (const auto& it : _fields[i])
        {
            result += it->compile(level + 1);
        }

        result += '\n';
    }

    // Производим нужную корректировку
    result += generateShift(level) + "};\n";

    // Возвращаем результат
    return result;
}
