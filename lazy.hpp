#ifndef IORATE_EGG_LAZY_HPP
#define IORATE_EGG_LAZY_HPP


#include <type_traits>
#include <boost/mpl/placeholders.hpp>
#include "./bind.hpp"
#include "./detail/auto_function.hpp"
#include "./detail/boost_use_default_fwd.hpp"
#include "./detail/if_use_default.hpp"
#include "./detail/move.hpp"
#include "./generator.hpp"


namespace iorate { namespace egg {


    namespace lazy_detail {


        template <class F, class Bind>
        struct result_
        {
            typedef
                typename detail::if_use_default<Bind, T_bind>::type
            bind_t;

            F m_f;

            constexpr F const &base() noexcept
            {
                return m_f;
            }

            template <class ...Args>
            constexpr IORATE_EGG_AUTO_FUNCTION(operator()(Args &&...args))
            (
                return bind_t()(m_f, IORATE_EGG_FORWARD(args)...)
            )
        };


    } // namespace lazy_detail


    template <class Bind = boost::use_default>
    struct X_lazy 
      : generator<lazy_detail::result_<std::decay<boost::mpl::_1>, Bind>>::type
    {};

    typedef X_lazy<> T_lazy;
    constexpr T_lazy lazy = {};


} } // namespace iorate::egg


#endif
