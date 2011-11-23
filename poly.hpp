#ifndef IORATE_EGG_POLY_HPP
#define IORATE_EGG_POLY_HPP


#include <boost/mpl/apply.hpp>
#include "./detail/auto_function.hpp"
#include "./detail/move.hpp"


namespace iorate { namespace egg {


    namespace poly_detail {


        template <class Lam>
        struct aux_
        {
            template <class ...Args>
            constexpr IORATE_EGG_AUTO_FUNCTION(operator()(Args &&...args))
            (
                return typename boost::mpl::apply<Lam, Args...>::type()(IORATE_EGG_FORWARD(args)...)
            )
        };


    } // namespace poly_detail


    template <class Lam>
    struct poly
    {
        typedef 
            poly_detail::aux_<Lam>
        type;
    };


} } // namespace iorate::egg


#endif
