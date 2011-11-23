#ifndef IORATE_EGG_DETAIL_tuple_get_c_HPP
#define IORATE_EGG_DETAIL_tuple_get_c_HPP


#include <tuple>
#include <type_traits>
#include <boost/fusion/include/advance.hpp>
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/deref.hpp>
#include "./auto_function.hpp"
#include "./is_fusion_sequence.hpp"
#include "./is_tuple_like.hpp"
#include "./move.hpp"


namespace iorate { namespace egg { namespace detail {


    template <class N, class T, class Dummy = void>
    struct tuple_get_impl;

    template <class N>
    struct X_tuple_get
    {
        template <class T>
        constexpr IORATE_EGG_AUTO_FUNCTION(operator()(T &&t) noexcept)
        (
            return tuple_get_impl<N, typename std::remove_reference<T>::type>()(IORATE_EGG_FORWARD(t))
        )
    };


    // Tuple-like
    //

    template <class N, class T>
    struct tuple_get_impl<N, T, typename std::enable_if<is_tuple_like<T>::value>::type>
    {
        template <class T_>
        constexpr IORATE_EGG_AUTO_FUNCTION(operator()(T_ &&t) noexcept)
        (
            return std::get<N::value>(IORATE_EGG_FORWARD(t))
        )
    };


    // FusionSequence
    //

    template <class N, class T>
    struct tuple_get_impl<N, T, typename std::enable_if<is_fusion_sequence<T>::value>::type>
    {
        template <class T_>
        constexpr IORATE_EGG_AUTO_FUNCTION(operator()(T_ &&t) noexcept)
        (
            return boost::fusion::deref(boost::fusion::advance<N>(boost::fusion::begin(IORATE_EGG_FORWARD(t))))
        )
    };


} } } // namespace iorate::egg::detail


#endif
