#ifndef IORATE_EGG_DETAIL_OBJECTIFY_HPP
#define IORATE_EGG_DETAIL_OBJECTIFY_HPP


#include <boost/preprocessor/cat.hpp>
#include "./auto_function.hpp"
#include "./move.hpp"


#define IORATE_EGG_OBJECTIFY(object, function, exceptspec) \
    struct BOOST_PP_CAT(T_, object) \
    { \
        template <class ...Args> \
        constexpr IORATE_EGG_AUTO_FUNCTION(operator()(Args &&...args) exceptspec) \
        ( \
            return (function)(IORATE_EGG_FORWARD(args)...) \
        ) \
    }; \
    constexpr BOOST_PP_CAT(T_, object) object = {}; \
    /**/


#endif
