#ifndef IORATE_EGG_PREPROCESSOR_CAT3_HPP
#define IORATE_EGG_PREPROCESSOR_CAT3_HPP


#include <boost/preprocessor/cat.hpp>


#define IORATE_EGG_PP_CAT3(x, y, z) \
    BOOST_PP_CAT(BOOST_PP_CAT(x, y), z) \
    /**/


#endif
