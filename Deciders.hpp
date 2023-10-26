#pragma once
#include <functional>
#include "Typenames.hpp"

namespace Novum
{

class Deciders
{
public:
    template <typename T>
    const static Novum::Typenames::DECIDER<T> GET_ASEC ()
    {
        return [](const T& given, const T& before) -> bool {
            return before < given;
        };
    }

    template <typename T>
    const static Novum::Typenames::DECIDER<T> GET_DESC ()
    {
        return [](const T& given, const T& before) -> bool {
            return before > given;
        };
    }

    Deciders() = delete;    
};

}