#pragma once

#include <functional>
#include <cstdint>
#include <ostream>
#include "Typenames.hpp"

namespace Novum
{

class Actors
{
public:

    template <typename T>
    static const Novum::Typenames::VOID_LOOPER<T> ADD_BY(const T& add_Value)
    {
        return [add_Value] (T& value, size_t index) {
            value += add_Value;
        };
    }

    template <typename T>
    static const Novum::Typenames::VOID_LOOPER<T> COUT(const char* separator = "")
    {
        return [separator] (const T& value, size_t index) {
            std::cout << value << separator;
        };
    }

    Actors() = delete;
};

}