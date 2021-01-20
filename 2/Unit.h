#pragma once

#include "Configuration.h"

/*
 * Основной абстрактный класс, от которого наследуются ClassUnit / MethodUnit / PrintUnit
 * Имеет чистые вирутальные функции add(добавление юнита, области класса, метода или вывода)
 * compile(формирование юнита в виде текста и возврат строки)
 */
class Unit
{
public:
    // Дефолтный деструктор с noexcept; означает, что деструктор не выбрасывает исключений(ускоряет скорость компиляции)
    // default для чистоты коды, чтобы не производить пустую реализацию {}
    virtual ~Unit() noexcept = default;

    // Функция добавления юнитов в класс / метод. Флаги доступа (модификаторы доступа)
    virtual void add(const Configuration::Ptr& unit, const Configuration::Flags& flags = 0)	= 0;

    // Формирование юнита
    virtual std::string compile(const Configuration::UI& level = 0) const					= 0;

protected:
    // Функция воспроизводящая табуляцию
    virtual std::string generateShift(const Configuration::UI& level) const;
};

inline std::string Unit::generateShift(const Configuration::UI& level) const
{
    std::string result;

    // Каждый цикл добавление табуляции к переменной
    for (Configuration::UI i = 0; i < level; ++i)
        result += '\t';

    return result;
}
