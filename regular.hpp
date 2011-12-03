#ifndef IORATE_EGG_REGULAR_HPP
#define IORATE_EGG_REGULAR_HPP


#include <type_traits>
#include <boost/mpl/placeholders.hpp>
#include <boost/none.hpp>
#include <boost/optional.hpp>
#include "./detail/auto_function.hpp"
#include "./detail/move.hpp"
#include "./generator.hpp"


namespace iorate { namespace egg {


    namespace regular_detail {


        template <class T>
        struct dummy_assignable
        {
            T m_t;

            dummy_assignable &operator=(dummy_assignable const &) noexcept
            {
                return *this;
            }
        };
        
        template <class F>
        struct result_
        {
            boost::optional<dummy_assignable<F>> m_f;

            result_() noexcept
              : m_f()
            {}

            result_(F const &f)
              : m_f(dummy_assignable<F> { f })
            {}

            result_ &operator=(result_ const &other) noexcept
            {
                m_f = boost::none;
                m_f = other.m_f;
                return *this;
            }

            template <class ...Args>
            IORATE_EGG_AUTO_FUNCTION(operator()(Args &&...args))
            (
                return (m_f->m_t)(IORATE_EGG_FORWARD(args)...)
            )
        };


    } // regular_detail


    typedef
        generator<regular_detail::result_<std::decay<boost::mpl::_1>>>::type
    T_regular;

    constexpr T_regular regular = {};


} } // namespace iorate::egg


#endif
