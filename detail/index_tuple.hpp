#ifndef IORATE_EGG_DETAIL_INDEX_TUPLE_HPP
#define IORATE_EGG_DETAIL_INDEX_TUPLE_HPP


#include <cstddef>


namespace iorate { namespace egg { namespace detail {


    template <std::size_t ...Indexes>
    struct index_tuple
    {
        typedef index_tuple<Indexes..., sizeof...(Indexes)> next;
    };


    template <std::size_t N>
    struct build_index_tuple
    {
        typedef typename build_index_tuple<N-1>::type::next type;
    };

    template <>
    struct build_index_tuple<0>
    {
        typedef index_tuple<> type;
    };


} } } // namespace iorate::egg::detail


#endif
