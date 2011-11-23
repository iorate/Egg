#ifndef IORATE_EGG_ADAPTED_TO_HPP
#define IORATE_EGG_ADAPTED_TO_HPP


#include <type_traits>
#include "./detail/boost_use_default_fwd.hpp"
#include "./detail/if_use_default.hpp"


namespace iorate { namespace egg {


    template <class B = boost::use_default>
    struct X_adapted_to
    {
        template <class F>
        constexpr auto operator()(F const &f) ->
            typename detail::eval_if_use_default<B, std::decay<decltype(f.base())>>::type
        {
            return f.base();
        }
    };

    typedef X_adapted_to<> T_adapted_to;
    constexpr T_adapted_to adapted_to = {};


} } // namespace iorate::egg


#endif
