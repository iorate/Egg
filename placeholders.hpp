#ifndef IORATE_EGG_PLACEHOLDERS_HPP
#define IORATE_EGG_PLACEHOLDERS_HPP


#include "./detail/placeholder.hpp"


namespace iorate { namespace egg {


    namespace placeholders {


        typedef detail::placeholder<1> TT_1;
        typedef detail::placeholder<2> TT_2;
        typedef detail::placeholder<3> TT_3;

        constexpr TT_1 _1 = {};
        constexpr TT_2 _2 = {};
        constexpr TT_3 _3 = {};


    } // namespace placeholders


    using namespace placeholders;


} } // namespace iorate::egg


#endif
