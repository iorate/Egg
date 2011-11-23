#ifndef IORATE_EGG_MONO_HPP
#define IORATE_EGG_MONO_HPP


#include <type_traits>
#include <utility>
#include <boost/mpl/placeholders.hpp>
#include "./detail/auto_function.hpp"
#include "./detail/if_use_default.hpp"
#include "./detail/move.hpp"
#include "./generator.hpp"


namespace iorate { namespace egg {


    namespace mono_detail {


        template <class F, class Sig>
        struct result_;

        template <class F, class R, class ...Args>
        struct result_<F, R (Args...)>
        {
            typedef typename
                detail::if_use_default<R, decltype(std::declval<F const &>()(std::declval<Args>()...))>::type
            result_type;

            F m_f;

            constexpr F const &base() noexcept
            {
                return m_f;
            }

            constexpr result_type operator()(Args ...args)
            {
                return m_f(IORATE_EGG_FORWARD(args)...);
            }
        };

        template <class F, class R, class A1>
        struct result_<F, R (A1)>
        {
            typedef typename
                detail::if_use_default<R, decltype(std::declval<F const &>()(std::declval<A1>()))>::type
            result_type;

            typedef A1 argument_type;

            F m_f;

            constexpr F const &base() noexcept
            {
                return m_f;
            }

            constexpr result_type operator()(A1 a1)
            {
                return m_f(IORATE_EGG_FORWARD(a1));
            }
        };

        template <class F, class R, class A1, class A2>
        struct result_<F, R (A1, A2)>
        {
            typedef typename
                detail::if_use_default<R, decltype(std::declval<F const &>()(std::declval<A1>(), std::declval<A2>()))>::type
            result_type;

            typedef A1 first_argument_type;
            typedef A2 second_argument_type;

            F m_f;

            constexpr F const &base() noexcept
            {
                return m_f;
            }

            constexpr result_type operator()(A1 a1, A2 a2)
            {
                return m_f(IORATE_EGG_FORWARD(a1), IORATE_EGG_FORWARD(a2));
            }
        };


    } // namespace mono_detail


    template <class Sig>
    struct X_mono
      : generator<mono_detail::result_<std::decay<boost::mpl::_1>, Sig>>::type
    {};

    template <class Sig, class F>
    constexpr IORATE_EGG_AUTO_FUNCTION(mono(F &&f))
    (
        return X_mono<Sig>()(IORATE_EGG_FORWARD(f))
    )


} } // namespace iorate::egg


#endif
