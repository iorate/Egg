#ifndef IORATE_EGG_ON_HPP
#define IORATE_EGG_ON_HPP


#include <type_traits>
#include <boost/mpl/placeholders.hpp>
#include "./detail/move.hpp"
#include "./generator.hpp"


namespace iorate { namespace egg {


    namespace on_detail {


        template <class F, class G>
        struct result_
        {
            F m_f;
            G m_g;

            template <class ...Args>
            constexpr IORATE_EGG_AUTO_FUNCTION(operator()(Args &&...args))
            (
                return m_f(m_g(IORATE_EGG_FORWARD(args))...)
            )
        };


    } // namespace on_detail


    typedef
        generator<on_detail::result_<std::decay<boost::mpl::_1>, std::decay<boost::mpl::_2>>>::type
    T_on;

    constexpr T_on on = {};


} } // namespace iorate::egg


#endif
