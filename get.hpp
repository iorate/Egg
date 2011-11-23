#ifndef IORATE_EGG_GET_HPP
#define IORATE_EGG_GET_HPP


#include <boost/mpl/int.hpp>
#include "./detail/auto_function.hpp"
#include "./detail/move.hpp"
#include "./detail/tuple_get.hpp"


namespace iorate { namespace egg {


    template <class N>
    struct X_get 
      : detail::X_tuple_get<N>
    {};

    template <class N, class T>
    constexpr IORATE_EGG_AUTO_FUNCTION(get(T &&t) noexcept)
    (
        return X_get<N>()(IORATE_EGG_FORWARD(t))
    )


    template <int N>
    struct X_get_c
      : X_get<boost::mpl::int_<N>>
    {};

    template <int N, class T>
    constexpr IORATE_EGG_AUTO_FUNCTION(get_c(T &&t) noexcept)
    (
        return X_get_c<N>()(IORATE_EGG_FORWARD(t))
    )


    typedef X_get_c<0> T_first;
    constexpr T_first first  = {};

    typedef X_get_c<1> T_second;
    constexpr T_second second = {};


} } // namespace iorate::egg


#endif
