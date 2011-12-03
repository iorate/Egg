#ifndef IORATE_EGG_ALWAYS_HPP
#define IORATE_EGG_ALWAYS_HPP


#include <memory>
#include <type_traits>
#include <boost/mpl/placeholders.hpp>
#include "./generator.hpp"


namespace iorate { namespace egg {


    namespace always_detail {


        template <class T>
        struct result_
        {
            T m_t;

            template <class ...Args>
            constexpr T const &operator()(Args &&...) noexcept
            {
                return m_t;
            }
        };


    } // namespace always_detail


    typedef
        generator<always_detail::result_<std::decay<boost::mpl::_1>>>::type
    T_always;

    constexpr T_always always = {};


    namespace always_ref_detail {


        template <class T>
        struct result_
        {
            T *m_p;

            template <class ...Args>
            constexpr T &operator()(Args &&...) noexcept
            {
                return *m_p;
            }
        };


    } // namespace always_ref_detail


    struct T_always_ref
    {
        template <class T>
        constexpr always_ref_detail::result_<T> operator()(T &t) noexcept
        {
            return { std::addressof(t) };
        }
    };

    constexpr T_always_ref always_ref = {};


} } // namespace iorate::egg


#endif
