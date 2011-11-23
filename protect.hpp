#ifndef IORATE_EGG_PROTECT_HPP
#define IORATE_EGG_PROTECT_HPP


#include <functional>
#include <type_traits>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/placeholders.hpp>
#include "./detail/move.hpp"
#include "./generator.hpp"


namespace iorate { namespace egg {


    namespace protect_detail {


        template <class Expr>
        struct protected_
        {
            Expr m_expr;

            template <class ...Args>
            constexpr Expr const &operator()(Args &&...) noexcept
            {
                return m_expr;
            }
        };


    } // namespace protect_detail


    typedef
        generator<protect_detail::protected_<std::decay<boost::mpl::_1>>>::type
    T_protect;

    constexpr T_protect protect = {};


} } // namespace iorate::egg


namespace std {


    template <class Expr>
    struct is_bind_expression<protect_detail::protected_<Expr>>
      : boost::mpl::true_
    {};


} // namespace std


#endif
