#ifndef IORATE_EGG_GENERATOR_HPP
#define IORATE_EGG_GENERATOR_HPP


#include <boost/mpl/apply.hpp>
#include "./construct_braced1.hpp"
#include "./detail/boost_use_default_fwd.hpp"
#include "./detail/if_use_default.hpp"
#include "./detail/move.hpp"


namespace iorate { namespace egg {


    namespace generator_detail {


        template <class Lam, class Cons>
        struct aux_
        {
            typedef typename
                detail::if_use_default<Cons, X_construct_braced1<>>::type
            cons_t;

            template <class ...Args, class T = typename boost::mpl::apply<Lam, Args...>::type>
            constexpr T operator()(Args &&...args)
            {
                return typename boost::mpl::apply<cons_t, T>::type()(IORATE_EGG_FORWARD(args)...);
            }
        };


    } // namespace generator_detail


    template <class Lam, class Cons = boost::use_default>
    struct generator
    {
        typedef
            generator_detail::aux_<Lam, Cons>
        type;
    };


} } // namespace iorate::egg


#endif
