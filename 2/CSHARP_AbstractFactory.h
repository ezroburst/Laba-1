#pragma once

#include "AbstractFactory.h"
#include "CSHARP_ClassUnit.h"
#include "CSHARP_MethodUnit.h"
#include "CSHARP_PrintUnit.h"

class CSHARP_AbstractFactory : public AbstractFactory
{
public:
    // См. AbstractFactory.h
    std::shared_ptr<ClassUnit> CreateClassUnit(const std::string& name, const Configuration::Flags& accFlags, const Configuration::Flags& modFlags = 0) const override;
    std::shared_ptr<MethodUnit> CreateMethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags) const override;
    std::shared_ptr<PrintUnit> CreatePrintOperatorUnit(const std::string& text) const override;
    ~CSHARP_AbstractFactory() override = default;
};

// Создаёт smart ptr CSHARP_ClassUnit и возвращает его
inline std::shared_ptr<ClassUnit> CSHARP_AbstractFactory::CreateClassUnit(const std::string& name, const Configuration::Flags& accFlags, const Configuration::Flags& /*modFlags*/) const
{
    return std::make_shared<CSHARP_ClassUnit>(name, accFlags);
}

// По аналогии
inline std::shared_ptr<MethodUnit> CSHARP_AbstractFactory::CreateMethodUnit(const std::string& name, const std::string& returnType, const Configuration::Flags& flags) const
{
    return std::make_shared<CSHARP_MethodUnit>(name, returnType, flags);
}

// По аналогии
inline std::shared_ptr<PrintUnit> CSHARP_AbstractFactory::CreatePrintOperatorUnit(const std::string& text) const
{
    return std::make_shared<CSHARP_PrintUnit>(text);
}
