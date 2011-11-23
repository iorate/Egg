#ifndef IORATE_EGG_PIPABLE_HPP
#define IORATE_EGG_PIPABLE_HPP


#include <type_traits>
#include <boost/mpl/placeholders.hpp>
#include "./detail/pipable_result.hpp"
#include "./generator.hpp"


namespace iorate { namespace egg {


    typedef
        generator<detail::pipable_result<std::decay<boost::mpl::_1>>>::type
    T_pipable;

    constexpr T_pipable pipable = {};


} } // namespace iorate::egg


#endif
