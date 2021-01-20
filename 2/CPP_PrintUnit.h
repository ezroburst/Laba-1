#pragma once

#include "PrintUnit.h"

class CPP_PrintUnit : public PrintUnit
{
public:
    // См. PrintUnit.h
    explicit CPP_PrintUnit(const std::string& text);
    void add(const Configuration::Ptr& unit, const Configuration::Flags& flags) override {}
    std::string compile(const Configuration::UI& level) const override;
};

inline CPP_PrintUnit::CPP_PrintUnit(const std::string& text) :
    PrintUnit(text)
{
}

inline std::string CPP_PrintUnit::compile(const Configuration::UI& level) const
{
    // Генерация на языке C++ вывода в консоль нужного текста
    return generateShift(level) + "printf( \"" + _text + "\" );\n";
}
