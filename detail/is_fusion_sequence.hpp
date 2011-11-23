#ifndef IORATE_EGG_DETAIL_IS_FUSION_SEQUENCE_HPP
#define IORATE_EGG_DETAIL_IS_FUSION_SEQUENCE_HPP


#include <boost/fusion/include/is_sequence.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include "./is_tuple_like.hpp"


namespace iorate { namespace egg { namespace detail {


    template <class T>
    struct is_fusion_sequence
      : boost::mpl::and_<
            boost::mpl::not_<is_tuple_like<T>>,
            boost::fusion::traits::is_sequence<T>
        >
    {};


} } } // namespace iorate::egg::detail


#endif
