#ifndef IORATE_EGG_UNFUSE_HPP
#define IORATE_EGG_UNFUSE_HPP


#include <type_traits>
#include <boost/mpl/placeholders.hpp>
#include "./detail/auto_function.hpp"
#include "./detail/boost_use_default_fwd.hpp"
#include "./detail/if_use_default.hpp"
#include "./detail/move.hpp"
#include "./generator.hpp"
#include "./pack.hpp"


namespace iorate { namespace egg {


    namespace unfuse_detail {


        template <class F, class Pack>
        struct result_
        {
            typedef typename
                detail::if_use_default<Pack, T_pack>::type
            pack_t;

            F m_f;

            constexpr F const &base() noexcept
            {
                return m_f;
            }

            template <class ...Args>
            constexpr IORATE_EGG_AUTO_FUNCTION(operator()(Args &&...args))
            (
                return m_f(pack_t()(IORATE_EGG_FORWARD(args)...))
            )
        };


    } // namespace unfuse_detail


    template <class Pack = boost::use_default>
    struct X_unfuse 
      : generator<unfuse_detail::result_<std::decay<boost::mpl::_1>, Pack>>::type
    {};

    typedef X_unfuse<> T_unfuse;
    constexpr T_unfuse unfuse = {};


} } // namespace iorate::egg


#endif
