#pragma once

#include "Unit.h"

// Абстрактный класс ВыводЮнит ( не интерфейс! )
class PrintUnit : public Unit
{
public:
    // Конструктор принимает только текст для вывода в косноль ( для каждого языка )
    explicit PrintUnit(std::string text);

    // Определение функции add, использование которой в PrintUnit не нужно, поэтому {}
    void add(const Configuration::Ptr&, const Configuration::Flags& flags) override {}

    // См. Unit.h
    std::string compile(const Configuration::UI& level) const override = 0;

protected:
    std::string _text;
};

// Встраиваемый конструктор, компилятор подставляет код непосредственно
// std::move принимает r-value ссылку, чтобы не производить лишнее копирование данных для _text
inline PrintUnit::PrintUnit(std::string text) :
    _text(std::move(text))
{
}
