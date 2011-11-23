#ifndef IORATE_EGG_COMPOSE_HPP
#define IORATE_EGG_COMPOSE_HPP


#include <cstddef>
#include <tuple>
#include <type_traits>
#include "./detail/auto_function.hpp"
#include "./detail/index_tuple.hpp"
#include "./detail/move.hpp"


namespace iorate { namespace egg {


    namespace compose_detail {


        template <class F, class G, std::size_t ...Indexes, class ...Args>
        constexpr IORATE_EGG_AUTO_FUNCTION(result_call_aux(F const &f, G const &g, detail::index_tuple<Indexes...>, Args &&...args))
        (
            return f(std::get<Indexes>(g)(IORATE_EGG_FORWARD(args)...)...)
        )

        template <class F, class ...G>
        struct result_
        {
            F m_f;
            std::tuple<G...> m_g;

            template <class F_, class ...G_>
            constexpr result_(F_ &&f, G_ &&...g)
              : m_f(IORATE_EGG_FORWARD(f)), m_g(IORATE_EGG_FORWARD(g)...)
            {}

            template <class ...Args>
            constexpr IORATE_EGG_AUTO_FUNCTION(operator()(Args &&...args))
            (
                return result_call_aux(m_f, m_g, typename detail::build_index_tuple<sizeof...(G)>::type(), IORATE_EGG_FORWARD(args)...)
            )
        };


    } // namespace compose_detail


    struct T_compose
    {
        template <class F, class ...G>
        constexpr compose_detail::result_<typename std::decay<F>::type, typename std::decay<G>::type...> operator()(F &&f, G &&...g)
        {
            return { IORATE_EGG_FORWARD(f), IORATE_EGG_FORWARD(g)... };
        }
    };

    constexpr T_compose compose = {};


} } // namespace iorate::egg


#endif
