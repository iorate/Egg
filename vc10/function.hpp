#ifndef IORATE_EGG_VC10_FUNCTION_HPP
#define IORATE_EGG_VC10_FUNCTION_HPP


#include <type_traits>
#include <utility>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/utility/result_of.hpp>
// #include "../config.hpp"


#if !defined(IORATE_EGG_MAX_LINEAR_ARITY)
    #define IORATE_EGG_MAX_LINEAR_ARITY 10
#endif


namespace iorate { namespace egg {


    template <class Function>
    struct ERROR_IORATE_EGG_FUNCTION_NON_NULLARY;


    namespace function_detail {


        BOOST_MPL_HAS_XXX_TRAIT_DEF(nullary_result_type)

        template <class Little>
        struct extract_nullary_result_of_little
        {
            typedef typename Little::nullary_result_type type;
        };

        template <class Little, class Function>
        struct nullary_result_of_little
          : boost::mpl::eval_if<
                has_nullary_result_type<Little>,
                extract_nullary_result_of_little<Little>,
                boost::mpl::identity<ERROR_IORATE_EGG_FUNCTION_NON_NULLARY<Function>>
            >
        {};


    } // namespace function_detail


    template <class Little>
    struct function
    {
        typedef typename 
            function_detail::nullary_result_of_little<Little, function>::type
        nullary_result_type;

        template <class FunCall>
        struct result;

        #define BOOST_PP_LOCAL_MACRO(n)                                         \
        template <class Fun, BOOST_PP_ENUM_PARAMS(n, class A)>                  \
        struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))>                          \
          : Little::template apply<Little const, BOOST_PP_ENUM_BINARY_PARAMS(n, A, && BOOST_PP_INTERCEPT)> \
        {};                                                                     \
        /**/
        #define BOOST_PP_LOCAL_LIMITS (1, IORATE_EGG_MAX_LINEAR_ARITY)
        #include BOOST_PP_LOCAL_ITERATE()

        Little m_little;

        nullary_result_type operator()() const
        {
            return m_little.template call<nullary_result_type>();
        }

        #define IORATE_EGG_FUNCTION_forward(z, i, unused)                       \
        std::forward<BOOST_PP_CAT(A, i)>(BOOST_PP_CAT(a, i))                    \
        /**/

        #define BOOST_PP_LOCAL_MACRO(n)                                         \
        template <BOOST_PP_ENUM_PARAMS(n, class A)>                             \
        typename result<function const(BOOST_PP_ENUM_BINARY_PARAMS(n, A, && BOOST_PP_INTERCEPT))>::type \
        operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &&a)) const                \
        {                                                                       \
            return m_little.template call<                                      \
                typename result<function const(BOOST_PP_ENUM_BINARY_PARAMS(n, A, && BOOST_PP_INTERCEPT))>::type \
            >(BOOST_PP_ENUM(n, IORATE_EGG_FUNCTION_forward, ~));                \
        }                                                                       \
        /**/
        #define BOOST_PP_LOCAL_LIMITS (1, IORATE_EGG_MAX_LINEAR_ARITY)
        #include BOOST_PP_LOCAL_ITERATE()

        #undef IORATE_EGG_FUNCTION_forward
    };

    #define IORATE_EGG_FUNCTION(...) { __VA_ARGS__ }


} } // namespace iorate::egg


namespace std {


    template <class Little>
    struct result_of<iorate::egg::function<Little>()>
    {
        typedef typename
            iorate::egg::function<Little>::nullary_result_type
        type;
    };

    template <class Little>
    struct result_of<iorate::egg::function<Little> const()>
    {
        typedef typename
            iorate::egg::function<Little>::nullary_result_type
        type;
    };


} // namespace std


namespace boost {


    template <class Little>
    struct result_of<iorate::egg::function<Little>()>
    {
        typedef typename
            iorate::egg::function<Little>::nullary_result_type
        type;
    };

    template <class Little>
    struct result_of<iorate::egg::function<Little> const()>
    {
        typedef typename
            iorate::egg::function<Little>::nullary_result_type
        type;
    };


} // namespace boost


#endif
