#ifndef IORATE_EGG_DETAIL_TUPLE_SIZE_HPP
#define IORATE_EGG_DETAIL_TUPLE_SIZE_HPP


#include <tuple>
#include <type_traits>
#include <boost/fusion/include/size.hpp>
#include "./is_fusion_sequence.hpp"
#include "./is_tuple_like.hpp"


namespace iorate { namespace egg { namespace detail {


    template <class T, class Dummy = void>
    struct tuple_size_impl;

    template <class T>
    struct tuple_size
      : tuple_size_impl<T>
    {};


    // Tuple-like
    //

    template <class T>
    struct tuple_size_impl<T, typename std::enable_if<is_tuple_like<T>::value>::type>
      : std::tuple_size<T>
    {};


    // FusionSequence
    //

    template <class T>
    struct tuple_size_impl<T, typename std::enable_if<is_fusion_sequence<T>::value>::type>
      : boost::fusion::result_of::size<T>::type
    {};


} } } // namespace iorate::egg::detail


#endif
