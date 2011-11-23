#ifndef IORATE_EGG_IDENTITY_HPP
#define IORATE_EGG_IDENTITY_HPP


#include <type_traits>
#include "./detail/move.hpp"


namespace iorate { namespace egg {


    struct T_identity
    {
        template <class T>
        constexpr T &&operator()(T &&t) noexcept
        {
            return IORATE_EGG_FORWARD(t);
        }
    };

    constexpr T_identity identity = {};


    struct T_identity_by_val
    {
        template <class T>
        constexpr typename std::decay<T>::type operator()(T &&t) noexcept
        {
            return IORATE_EGG_FORWARD(t);
        }
    };

    constexpr T_identity_by_val identity_by_val = {};


} } // namespace iorate::egg


#endif
