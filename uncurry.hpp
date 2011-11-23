#ifndef IORATE_EGG_UNCURRY_HPP
#define IORATE_EGG_UNCURRY_HPP


#include <type_traits>
#include <utility>
#include <boost/mpl/placeholders.hpp>
#include "./detail/auto_function.hpp"
#include "./detail/move.hpp"
#include "./generator.hpp"


namespace iorate { namespace egg {


    namespace uncurry_detail {


        template <class F, class ...Args>
        struct result_call_aux;

        template <class F>
        struct result_call_aux<F>
        {
            constexpr F &&operator()(F &&f) noexcept
            {
                return IORATE_EGG_FORWARD(f);
            }
        };

        template <class F, class A1, class ...Args>
        struct result_call_aux<F, A1, Args...>
        {
            constexpr IORATE_EGG_AUTO_FUNCTION(operator()(F &&f, A1 &&a1, Args &&...args))
            (
                return result_call_aux<decltype(std::declval<F>()(std::declval<A1>())), Args...>()(IORATE_EGG_FORWARD(f)(IORATE_EGG_FORWARD(a1)), IORATE_EGG_FORWARD(args)...)
            )
        };

        template <class F>
        struct result_
        {
            F m_f;

            constexpr F const &base() noexcept
            {
                return m_f;
            }

            template <class ...Args>
            constexpr IORATE_EGG_AUTO_FUNCTION(operator()(Args &&...args))
            (
                return result_call_aux<F const &, Args...>()(m_f, IORATE_EGG_FORWARD(args)...)
            )
        };


    } // namespace uncurry_detail


    typedef
        generator<uncurry_detail::result_<std::decay<boost::mpl::_1>>>::type
    T_uncurry;

    constexpr T_uncurry uncurry = {};


} } // namespace iorate::egg


#endif
