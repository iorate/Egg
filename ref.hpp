#ifndef IORATE_EGG_REF_HPP
#define IORATE_EGG_REF_HPP


#include <functional>
#include <type_traits>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include "./detail/objectify.hpp"


namespace iorate { namespace egg {


    namespace is_reference_wrapper_aux {


        template <class T>
        struct aux_
          : boost::mpl::false_
        {};

        template <class T>
        struct aux_<std::reference_wrapper<T>>
          : boost::mpl::true_
        {};


    } // namespace is_reference_wrapper_aux


    template <class T>
    struct is_reference_wrapper
      : is_reference_wrapper_detail::aux_<typename std::remove_cv<T>::type>
    {};


    template <class T>
    struct unwrap_reference
      : boost::mpl::eval_if<is_reference_wrapper<T>, T, boost::mpl::identity<T>>
    {};


    IORATE_EGG_OBJECTIFY(wrap_ref, std::ref, noexcept)


    struct T_unwrap_ref
    {
        template <class T>
        typename unwrap_reference<T>::type &operator()(T &t) noexcept
        {
            return t;
        }
    };

    constexpr T_unwrap_ref unwrap_ref = {};


} } // namespace iorate::egg


#endif
