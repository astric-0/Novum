#pragma once

#include<functional>

namespace Novum
{
    class Typenames 
    {
    public:
        template <typename T>
        using DECIDER = std::function<bool(const T&, const T&)>;

        template <typename T>
        using BOOL_LOOPER = std::function<bool(T&, size_t)>;     

        template <typename T>
        using VOID_LOOPER = std::function<void(T&, size_t)>;

        Typenames() = delete;
    };
}