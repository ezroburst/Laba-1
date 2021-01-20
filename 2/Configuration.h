#pragma once

#include <memory>
#include <vector>
#include <string>

//#define THROW(message) throw std::exception(message, -0x01)

/*
 * Forward declararion ( на русском это что-то типо такого: первочаначальное определие класса )
 * Делают это для того, чтобы не происходило лишней компиляции и не приходилось бы писать #include "Unit.h"
 */
class Unit;

// Конфигурационный "файл" для упрощения работы с фабрикой
namespace Configuration
{
    // Создание псевдонима Ptr
    typedef std::shared_ptr<Unit> Ptr;

    // Псевдонимы
    using Flags		= unsigned int;
    using UI		= unsigned int;

    // Поля для юнитов классов, чтобы можно было каждый блок разделить на public, protected и т.д.
    using Fields	= std::vector<std::vector<std::shared_ptr<Unit>>>;

    // Тело Юнита, по аналогии с предыдущим
    using Body		= std::vector<std::shared_ptr<Unit>>;

    // Тип перечисления для модификаторов доступа класса
    enum AccessModifier : unsigned
    {
        PUBLIC = 0x00,
        PROTECTED,
        PRIVATE,
        INTERNAL,
        PROTECTED_INTERNAL,
        PRIVATE_PROTECTED
    };

    /*
     * Модификаторы доступа для методов
     * Сделал их в шестнадцетиричной системе для удобного чтения
     * Каждое число соответствует каждому биту в числе, чтобы флаги можно было совмещать для одного метода
     * Например STATIC = 0x01 в битах будет так 0...001, CONST - 0...0010 и так далее
     */
    enum Modifier : unsigned
    {
        STATIC			= 0x01,
        CONST			= 0x02,
        VIRTUAL			= 0x04,
        ABSTRACT		= 0x08,
        ASYNC			= 0x10,
        UNSAFE			= 0x20,
        SEALED			= 0x40,
        FINAL			= SEALED,
        SYNCHRONIZED	= 0x80
    };

    // Модификаторы доступа в текстовом варианте
    static const std::vector<std::string> ACCESS_MODIFIERS = {
        "public",
        "protected",
        "private",
        "internal",
        "protected internal",
        "private protected"
    };
}
