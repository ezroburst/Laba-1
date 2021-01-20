#pragma once

#include "Unit.h"

// Абстрактный класс Метода ( не интерфейс! )
class MethodUnit : public Unit
{
public:
    // Конструктор принимает имя, возвращаемый тип и флаги модификаторов
    explicit MethodUnit(std::string name, std::string returnType, const Configuration::Flags& flags);

    // Деструктор по аналогии в Unit.h
    virtual ~MethodUnit() noexcept = default;

    // Тоже самое см. в Unit.h
    void add(const Configuration::Ptr&, const Configuration::Flags& flags) override = 0;
    std::string compile(const Configuration::UI& level) const override				= 0;

protected:
    // Имя метода
    std::string _name;

    // Возвращаемый тип void, int и т.д.
    std::string _returnType;

    // Модификаторы доступа метода
    Configuration::Flags _flags;

    // Тело метода
    Configuration::Body _body;
};

// Конструктор с std::move; r-value ссылки позволяют не копировать лишние байты. Непосредственное владение. Флаги доступа
inline MethodUnit::MethodUnit(std::string name, std::string returnType, const Configuration::Flags& flags) :
    _name(std::move(name)),
    _returnType(std::move(returnType)),
    _flags(flags)
{
}
