#ifndef IORATE_EGG_DETAIL_IS_TUPLE_LIKE_HPP
#define IORATE_EGG_DETAIL_IS_TUPLE_LIKE_HPP


#include <array>
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>
#include <boost/mpl/bool.hpp>


namespace iorate { namespace egg { namespace detail {


    template <class T>
    struct is_tuple_like_aux
      : boost::mpl::false_
    {};

    template <class T1, class T2>
    struct is_tuple_like_aux<std::pair<T1, T2>>
      : boost::mpl::true_
    {};

    template <class ...Types>
    struct is_tuple_like_aux<std::tuple<Types...>>
      : boost::mpl::true_
    {};

    template <class T, std::size_t N>
    struct is_tuple_like_aux<std::array<T, N>>
      : boost::mpl::true_
    {};

    template <class T>
    struct is_tuple_like
      : is_tuple_like_aux<typename std::remove_cv<T>::type>
    {};


} } } // namespace iorate::egg::detail


#endif
