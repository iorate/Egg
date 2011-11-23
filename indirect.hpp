#ifndef IORATE_EGG_INDIRECT_HPP
#define IORATE_EGG_INDIRECT_HPP


#include <type_traits>
#include <boost/mpl/placeholders.hpp>
#include "./detail/auto_function.hpp"
#include "./detail/move.hpp"
#include "./generator.hpp"


namespace iorate { namespace egg {


    namespace indirect_detail {


        template <class P>
        struct result_
        {
            P m_p;

            constexpr IORATE_EGG_AUTO_FUNCTION(base())
            (
                return *m_p
            )

            template <class ...Args>
            constexpr IORATE_EGG_AUTO_FUNCTION(operator()(Args &&...args))
            (
                return (*m_p)(IORATE_EGG_FORWARD(args)...)
            )
        };


    } // namespace indirect_detail


    typedef
        generator<indirect_detail::result_<std::decay<boost::mpl::_1>>>::type
    T_indirect;

    constexpr T_indirect indirect = {};


} } // namespace iorate::egg


#endif
