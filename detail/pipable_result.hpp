#ifndef IORATE_EGG_DETAIL_PIPABLE_pipable_resultHPP
#define IORATE_EGG_DETAIL_PIPABLE_pipable_resultHPP


#include <tuple>
#include <type_traits>
#include "./auto_function.hpp"
#include "./move.hpp"
#include "../fuse.hpp"


namespace iorate { namespace egg { namespace detail {


    namespace pipable_operators {


        template <class F, class ...Args>
        struct pipable_forwarder
        {
            F m_f;
            std::tuple<Args &&...> m_args;

            constexpr pipable_forwarder(F const &f, Args &&...args)
              : m_f(f), m_args(IORATE_EGG_FORWARD(args)...)
            {}

            template <class A1>
            struct result_of_output
              : std::result_of<F const &(A1, Args...)>
            {};

            template <class A1>
            constexpr typename result_of_output<A1>::type output(A1 &&a1)
            {
                return fuse(m_f)(std::tuple_cat(std::forward_as_tuple(IORATE_EGG_FORWARD(a1)), std::tuple<Args &&...>(m_args)));
            }
        };

        // Workaround for gcc-4.7.0
        template <class F>
        struct pipable_forwarder<F>
        {
            F m_f;

            template <class A1>
            constexpr IORATE_EGG_AUTO_FUNCTION(output(A1 &&a1))
            (
                return m_f(IORATE_EGG_FORWARD(a1))
            )
        };

        template <class F, class A1, class ...Args>
        constexpr IORATE_EGG_AUTO_FUNCTION(operator|(A1 &&a1, pipable_forwarder<F, Args...> const &pi))
        (
            return pi.output(IORATE_EGG_FORWARD(a1))
        )

        template <class F, class A1, class ...Args>
        constexpr IORATE_EGG_AUTO_FUNCTION(operator|=(pipable_forwarder<F, Args...> const &pi, A1 &&a1))
        (
            return pi.output(IORATE_EGG_FORWARD(a1))
        )


        template <class F>
        struct pipable_result
        {
            F m_f;

            constexpr F const &base() noexcept
            {
                return m_f;
            }

            template <class A1>
            constexpr IORATE_EGG_AUTO_FUNCTION(output(A1 &&a1))
            (
                return m_f(IORATE_EGG_FORWARD(a1))
            )

            template <class ...Args>
            constexpr pipable_forwarder<F, Args...> operator()(Args &&...args)
            {
                return { m_f, IORATE_EGG_FORWARD(args)... };
            }
        };

        template <class F, class A1>
        constexpr IORATE_EGG_AUTO_FUNCTION(operator|(A1 &&a1, pipable_result<F> const &pi))
        (
            return pi.output(IORATE_EGG_FORWARD(a1))
        )

        template <class F, class A1>
        constexpr IORATE_EGG_AUTO_FUNCTION(operator|=(pipable_result<F> const &pi, A1 &&a1))
        (
            return pi.output(IORATE_EGG_FORWARD(a1))
        )


    } // namespace pipable_operators


    using pipable_operators::pipable_forwarder;
    using pipable_operators::pipable_result;


} } } // namespace iorate::egg::detail


#endif
