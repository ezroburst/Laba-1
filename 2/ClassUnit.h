#pragma once

#include <utility>
#include "Unit.h"

// Абстрактный класс Класса ( не интерфейс! )
class ClassUnit : public Unit
{
public:
    explicit ClassUnit(std::string name);
    virtual ~ClassUnit() noexcept = default;

    virtual void add(const Configuration::Ptr& unit, const Configuration::Flags& flags) override	= 0;
    virtual std::string compile(const Configuration::UI& level = 0) const override					= 0;

protected:
    // Имя класса
    std::string _name;

    // Поля класса public / protected и т.д.
    Configuration::Fields _fields;
};

// std::move; r-value ссылки позволяют не копировать лишние байты памяти (см. PrintUnit.h)
inline ClassUnit::ClassUnit(std::string name) :
    _name(std::move(name))
{
}
