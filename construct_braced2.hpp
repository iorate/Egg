#ifndef IORATE_EGG_CONSTRUCT_BRACED2_HPP
#define IORATE_EGG_CONSTRUCT_BRACED2_HPP


#include <boost/mpl/placeholders.hpp>
#include "./detail/move.hpp"


namespace iorate { namespace egg {


    template <class T = boost::mpl::_1>
    struct X_construct_braced2
    {
        template <class ...Args>
        constexpr T operator()(Args &&...args)
        {
            return T { { IORATE_EGG_FORWARD(args)... } };
        }
    };


} } // namespace iorate::egg


#endif
