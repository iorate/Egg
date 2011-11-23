#ifndef IORATE_EGG_CURRY_HPP
#define IORATE_EGG_CURRY_HPP


#include <functional>
#include <type_traits>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include "./config.hpp"
#include "./detail/auto_function.hpp"
#include "./detail/index_tuple.hpp"
#include "./detail/move.hpp"
#include "./detail/placeholder.hpp"
#include "./identity.hpp"


namespace iorate { namespace egg {


    namespace curry_c_detail {


        template <int N, class F>
        struct result_;


    } // namespace curry_c_detail


    template <int N>
    struct X_curry_c;

    template <>
    struct X_curry_c<1>
      : T_identity_by_val
    {};

    template <int N>
    struct X_curry_c
    {
        template <class F>
        constexpr curry_c_detail::result_<N, typename std::decay<F>::type> operator()(F &&f)
        {
            return { IORATE_EGG_FORWARD(f) };
        }
    };

    template <int N, class F>
    constexpr IORATE_EGG_AUTO_FUNCTION(curry_c(F &&f))
    (
        return X_curry_c<N>()(IORATE_EGG_FORWARD(f))
    )


    namespace curry_c_detail {


        template <int N, class F, class A1, std::size_t ...Indexes>
        constexpr IORATE_EGG_AUTO_FUNCTION(result_call_aux(F const &f, A1 &&a1, detail::index_tuple<Indexes...>))
        (
            return X_curry_c<N-1>()(std::bind(f, IORATE_EGG_FORWARD(a1), detail::placeholder<Indexes+1>()...))
        )

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
                return result_call_aux<N>(m_f, IORATE_EGG_FORWARD(a1), typename detail::build_index_tuple<N-1>::type())
            )
        };


    } // namespace curry_c_detail


    #define BOOST_PP_LOCAL_MACRO(n) \
    typedef X_curry_c<n> BOOST_PP_CAT(T_curry, n); \
    constexpr BOOST_PP_CAT(T_curry, n) BOOST_PP_CAT(curry, n) = {}; \
    /**/
    #define BOOST_PP_LOCAL_LIMITS (2, IORATE_EGG_MAX_ARITY)
    #include BOOST_PP_LOCAL_ITERATE()


} } // namespace iorate::egg


#endif
