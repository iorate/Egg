#ifndef IORATE_EGG_APPLY_HPP
#define IORATE_EGG_APPLY_HPP


#include "./detail/auto_function.hpp"
#include "./detail/move.hpp"


namespace iorate { namespace egg {


    struct T_apply
    {
        template <class F, class ...Args>
        constexpr IORATE_EGG_AUTO_FUNCTION(operator()(F &&f, Args &&...args))
        (
            return IORATE_EGG_FORWARD(f)(IORATE_EGG_FORWARD(args)...)
        )
    };

    constexpr T_apply apply = {};


} } // namespace iorate::egg


#endif
