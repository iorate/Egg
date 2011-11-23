#ifndef IORATE_EGG_VARIADIC_HPP
#define IORATE_EGG_VARIADIC_HPP


#include <utility>
#include "./detail/boost_use_default_fwd.hpp"
#include "./detail/move.hpp"
#include "./poly.hpp"
#include "./unfuse.hpp"


namespace iorate { namespace egg {


    namespace variadic_poly_detail {


        template <class Lam, class Pack>
        struct aux_
        {
            template <class Me, class ...Args>
            struct apply
            {
                typedef
                    decltype(X_unfuse<Pack>()(typename poly<Lam>::type())(std::declval<Args>()...))
                type;
            };

            template <class ...Args>
            constexpr typename apply<aux_ const &, Args...>::type operator()(Args &&...args)
            {
                return X_unfuse<Pack>()(typename poly<Lam>::type())(IORATE_EGG_FORWARD(args)...);
            }
        };


    } // namespace variadic_poly_detail


    template <class Lam, class Pack = boost::use_default>
    struct variadic_poly
    {
        typedef
            variadic_poly_detail::aux_<Lam, Pack>
        type;
    };


} } // namespace iorate::egg


#endif
