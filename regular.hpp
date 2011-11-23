#ifndef IORATE_EGG_REGULAR_HPP
#define IORATE_EGG_REGULAR_HPP


#include <boost/optional.hpp>
#include "./detail/auto_function.hpp"
#include "./detail/move.hpp"
#include "./indirect.hpp"


namespace iorate { namespace egg {


    struct T_regular
    {
        template <class F>
        constexpr IORATE_EGG_AUTO_FUNCTION(operator()(F &&f))
        (
            return indirect(boost::make_optional(IORATE_EGG_FORWARD(f)))
        )
    };

    constexpr T_regular regular = {};


} } // namespace iorate::egg


#endif
