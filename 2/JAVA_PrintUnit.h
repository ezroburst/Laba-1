#pragma once

#include "PrintUnit.h"

class JAVA_PrintUnit : public PrintUnit
{
public:
    // См. PrintUnit
    explicit JAVA_PrintUnit(const std::string& text);
    void add(const Configuration::Ptr& unit, const Configuration::Flags& flags) override {}
    std::string compile(const Configuration::UI& level) const override;
};

inline JAVA_PrintUnit::JAVA_PrintUnit(const std::string& text) :
    PrintUnit(text)
{
}

inline std::string JAVA_PrintUnit::compile(const Configuration::UI& level) const
{
    // Вывод в консоль на языке JAVA
    return generateShift(level) + "System.out.println( \"" + _text + "\" );\n";
}
