#ifndef IORATE_EGG_AMBI_HPP
#define IORATE_EGG_AMBI_HPP


#include <type_traits>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include "./config.hpp"
#include "./detail/auto_function.hpp"
#include "./detail/move.hpp"
#include "./detail/pipable_result.hpp"


namespace iorate { namespace egg {


    namespace ambi_c_detail {


        template <int N, class F>
        struct result_
        {
            F m_f;

            constexpr F const &base() noexcept
            {
                return m_f;
            }

            template <class A1>
            constexpr IORATE_EGG_AUTO_FUNCTION(operator()(A1 &&a1))
            (
                return m_f(IORATE_EGG_FORWARD(a1))
            )

            template <class ...Args, typename std::enable_if<sizeof...(Args) == N>::type * = nullptr>
            constexpr detail::pipable_forwarder<F, Args...> operator()(Args &&...args)
            {
                return { m_f, IORATE_EGG_FORWARD(args)... };
            }

            template <class ...Args, typename std::enable_if<sizeof...(Args) != N>::type * = nullptr>
            constexpr IORATE_EGG_AUTO_FUNCTION(operator()(Args &&...args))
            (
                return m_f(IORATE_EGG_FORWARD(args)...)
            )
        };

        template <int N, class F, class A1>
        constexpr IORATE_EGG_AUTO_FUNCTION(operator|(A1 &&a1, result_<N, F> const &pi))
        (
            return pi.output(IORATE_EGG_FORWARD(a1))
        )

        template <int N, class F, class A1>
        constexpr IORATE_EGG_AUTO_FUNCTION(operator|=(result_<N, F> const &pi, A1 &&a1))
        (
            return pi.output(IORATE_EGG_FORWARD(a1))
        )


    } // namespace ambi_c_detail


    template <int N>
    struct X_ambi_c
    {
        template <class F>
        constexpr ambi_c_detail::result_<N, typename std::decay<F>::type> operator()(F &&f)
        {
            return { IORATE_EGG_FORWARD(f) };
        }
    };

    template <int N, class F>
    constexpr IORATE_EGG_AUTO_FUNCTION(ambi_c(F &&f))
    (
        return X_ambi_c<N>()(IORATE_EGG_FORWARD(f))
    )


    #define BOOST_PP_LOCAL_MACRO(n) \
    typedef X_ambi_c<n> BOOST_PP_CAT(T_ambi, n); \
    constexpr BOOST_PP_CAT(T_ambi, n) BOOST_PP_CAT(ambi, n) = {}; \
    /**/
    #define BOOST_PP_LOCAL_LIMITS (0, IORATE_EGG_MAX_LINEAR_ARITY-1)
    #include BOOST_PP_LOCAL_ITERATE()


} } // namespace iorate::egg


#endif
