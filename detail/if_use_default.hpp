#ifndef IORATE_EGG_DETAIL_IF_USE_DEFAULT_HPP
#define IORATE_EGG_DETAIL_IF_USE_DEFAULT_HPP


#include <type_traits>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include "./boost_use_default_fwd.hpp"


namespace iorate { namespace egg { namespace detail {


    template <class T, class Then, class Else = T>
    struct if_use_default
      : boost::mpl::if_<std::is_same<T, boost::use_default>, Then, Else>
    {};


    template <class T, class Then, class Else = boost::mpl::identity<T>>
    struct eval_if_use_default
      : boost::mpl::eval_if<std::is_same<T, boost::use_default>, Then, Else>
    {};


} } } // namespace iorate::egg::detail


#endif
