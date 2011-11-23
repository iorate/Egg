#ifndef IORATE_EGG_FUSE_HPP
#define IORATE_EGG_FUSE_HPP


#include <cstddef>
#include <type_traits>
#include <boost/mpl/placeholders.hpp>
#include "./detail/auto_function.hpp"
#include "./detail/index_tuple.hpp"
#include "./detail/move.hpp"
#include "./detail/tuple_size.hpp"
#include "./generator.hpp"
#include "./get.hpp"


namespace iorate { namespace egg {


    namespace fuse_detail {


        template <class F, class Args, std::size_t ...Indexes>
        constexpr IORATE_EGG_AUTO_FUNCTION(result_call_aux(F const &f, Args &&args, detail::index_tuple<Indexes...>))
        (
            return f(X_get_c<Indexes>()(IORATE_EGG_FORWARD(args))...)
        )

        template <class F>
        struct result_
        {
            F m_f;

            constexpr F const &base() noexcept
            {
                return m_f;
            }

            template <class Args>
            constexpr IORATE_EGG_AUTO_FUNCTION(operator()(Args &&args))
            (
                return result_call_aux(m_f, IORATE_EGG_FORWARD(args), typename detail::build_index_tuple<detail::tuple_size<typename std::remove_reference<Args>::type>::value>::type())
            )
        };


    } // namespace fuse_detail


    typedef
        generator<fuse_detail::result_<std::decay<boost::mpl::_1>>>::type
    T_fuse;

    constexpr T_fuse fuse = {};


} } // namespace iorate::egg


#endif
