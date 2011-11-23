#ifndef IORATE_EGG_IMPLICIT_HPP
#define IORATE_EGG_IMPLICIT_HPP


#include <tuple>
#include <type_traits>
#include <utility>
#include <boost/mpl/apply.hpp>
#include "./detail/move.hpp"
#include "./fuse.hpp"


namespace iorate { namespace egg {


    namespace implicit_detail {


        template <class Lam, class ...Args>
        struct from
        {
            std::tuple<Args &&...> m_args;

            constexpr from(Args &&...args)
              : m_args(IORATE_EGG_FORWARD(args)...)
            {}

            template <class To>
            constexpr operator To()
            {
                return fuse(typename boost::mpl::apply<Lam, To>::type())(std::tuple<Args &&...>(m_args));
            }
        };

        template <class Lam>
        struct aux_
        {
            template <class ...Args>
            constexpr from<Lam, Args...> operator()(Args &&...args) noexcept
            {
                return { IORATE_EGG_FORWARD(args)... };
            }
        };


    } // namespace implicit_detail


    template <class Lam>
    struct implicit
    {
        typedef
            implicit_detail::aux_<Lam>
        type;
    };


} } // namespace iorate::egg


#endif
