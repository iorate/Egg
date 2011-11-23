#ifndef IORATE_EGG_FIX_HPP
#define IORATE_EGG_FIX_HPP


#include <type_traits>
#include <utility>
#include <boost/mpl/placeholders.hpp>
#include "./compose.hpp"
#include "./curry.hpp"
#include "./detail/auto_function.hpp"
#include "./detail/move.hpp"
#include "./generator.hpp"


namespace iorate { namespace egg {


    namespace fix_detail {


        template <class F>
        struct result_
        {
            F m_f;

            constexpr F const &base() noexcept
            {
                return m_f;
            }

            template <class Me, class A1>
            struct apply
            {
                typedef
                    decltype(std::declval<F const &>()(std::declval<Me>())(std::declval<A1>()))
                type;
            };

            template <class A1>
            constexpr typename apply<result_ const &, A1>::type operator()(A1 &&a1)
            {
                return m_f(*this)(IORATE_EGG_FORWARD(a1));
            }
        };


    } // namespace fix_detail


    typedef
        generator<fix_detail::result_<std::decay<boost::mpl::_1>>>::type
    T_fix;

    constexpr T_fix fix = {};


    typedef
        decltype(compose(fix, curry2))
    T_fix2;

    constexpr T_fix2 fix2 = compose(fix, curry2);


} } // namespace iorate::egg


#endif
