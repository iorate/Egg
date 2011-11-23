#ifndef IORATE_ADDRESSOF_HPP
#define IORATE_ADDRESSOF_HPP


#include <type_traits>
#include "./detail/enable_if.hpp"


namespace iorate { namespace egg {


    namespace addressof_detail {


        template <class T>
        struct derived_from : T
        {
            constexpr T const volatile *address() volatile
            {
                return this;
            }
        };


    } // namespace addressof_detail


    struct T_addressof
    {
        template <class T, IORATE_EGG_ENABLE_IF((std::is_union<T>::value || std::is_class<T>::value))>
        constexpr T *operator()(T &t) noexcept
        {
            // gcc-4.7.0 accepts this even at compile-time.
            return const_cast<T *>(static_cast<addressof_detail::derived_from<T> const volatile &>(t).address());
        }

        template <class T, IORATE_EGG_ENABLE_IF((!(std::is_union<T>::value || std::is_class<T>::value)))>
        constexpr T *operator()(T &t) noexcept
        {
            return &t;
        }
    };

    constexpr T_addressof addressof = {};


} } // namespace iorate::egg


#endif 
