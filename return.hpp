#ifndef IORATE_EGG_RETURN_HPP
#define IORATE_EGG_RETURN_HPP


#include <type_traits>
#include <boost/mpl/placeholders.hpp>
#include "./detail/auto_function.hpp"
#include "./detail/boost_use_default_fwd.hpp"
#include "./detail/if_use_default.hpp"
#include "./detail/move.hpp"
#include "./generator.hpp"


namespace iorate { namespace egg {


    namespace return_detail {


        template <class F, class R>
        struct result_
        {
            F m_f;

            constexpr F const &base() noexcept
            {
                return m_f;
            }

            template <class ...Args>
            constexpr auto operator()(Args &&...args) ->
                typename detail::if_use_default<R, decltype(m_f(IORATE_EGG_FORWARD(args)...))>::type
            {
                return m_f(IORATE_EGG_FORWARD(args)...);
            }
        };


    } // namespace return_detail


    template <class R = boost::use_default>
    struct X_return
      : generator<return_detail::result_<std::decay<boost::mpl::_1>, R>>::type
    {};

    template <class R, class F>
    constexpr IORATE_EGG_AUTO_FUNCTION(return_(F &&f))
    (
        return X_return<R>()(IORATE_EGG_FORWARD(f))
    )


} } // namespace iorate::egg


#endif
