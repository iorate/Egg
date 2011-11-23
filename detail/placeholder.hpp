#ifndef IORATE_EGG_DETAIL_PLACEHOLDER_HPP
#define IORATE_EGG_DETAIL_PLACEHOLDER_HPP


#include <functional>
#include <boost/mpl/int.hpp>


namespace iorate { namespace egg { namespace detail {


    template <int I>
    struct placeholder {};


} } } // namespace iorate::egg::detail


namespace std {


    template <int I>
    struct is_placeholder<iorate::egg::detail::placeholder<I>>
      : boost::mpl::int_<I>
    {};


} // namespace std


#endif
