#pragma once

#include "AbstractFactory.h"
#include "CPP_ClassUnit.h"
#include "CPP_MethodUnit.h"
#include "CPP_PrintUnit.h"

// Абстрактная фабрика для языка C++
class CPP_AbstractFactorty : public AbstractFactory
{
public:
    // См. AbstractFactory.h
    std::shared_ptr<ClassUnit> CreateClassUnit(const std::string& name, const Configuration::Flags& accFlags = 0, const Configuration::Flags& modFlags = 0) const override;
    std::shared_ptr<MethodUnit> CreateMethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags) const override;
    std::shared_ptr<PrintUnit> CreatePrintOperatorUnit(const std::string& text) const override;
    ~CPP_AbstractFactorty() override = default;
};

// Создаёт smart ptr CPP_ClassUnit и возвращает его
inline std::shared_ptr<ClassUnit> CPP_AbstractFactorty::CreateClassUnit(const std::string& name, const Configuration::Flags& /*accFlags*/, const Configuration::Flags& /*modFlags*/) const
{
    return std::make_shared<CPP_ClassUnit>(name);
}

// По аналогии
inline std::shared_ptr<MethodUnit> CPP_AbstractFactorty::CreateMethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags) const
{
    return std::make_shared<CPP_MethodUnit>(name, returnType, flags);
}

// По аналогии
inline std::shared_ptr<PrintUnit> CPP_AbstractFactorty::CreatePrintOperatorUnit(const std::string& text) const
{
    return std::make_shared<CPP_PrintUnit>(text);
}
