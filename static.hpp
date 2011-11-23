#ifndef IORATE_EGG_STATIC_HPP
#define IORATE_EGG_STATIC_HPP


#include "./detail/auto_function.hpp"
#include "./detail/move.hpp"


namespace iorate { namespace egg {


    namespace static_detail {


        template <class F>
        struct aux_
        {
            template <class ...Args>
            constexpr IORATE_EGG_AUTO_FUNCTION(operator()(Args &&...args))
            (
                return F()(IORATE_EGG_FORWARD(args)...)
            )
        };


    } // namespace static_detail


    template <class F>
    struct static_
    {
        typedef
            static_detail::aux_<F>
        type;
    };


} } // namespace iorate::egg


#endif
