#ifndef IORATE_EGG_INFIX_HPP
#define IORATE_EGG_INFIX_HPP


#include "./detail/auto_function.hpp"
#include "./detail/move.hpp"


namespace iorate { namespace egg {


    namespace infix_detail {


        template <class t, class A1>
        struct thingy
        {
            t &&m_f;
            A1 &&m_a1;
        };


    } // namespace infix_detail


    namespace infix {


        template <class T, class A1>
        constexpr infix_detail::thingy<T, A1> operator^(A1 &&a1, T &&t)
        {
            return { IORATE_EGG_FORWARD(t), IORATE_EGG_FORWARD(a1) };
        }

        template <class T, class A1, class A2>
        constexpr IORATE_EGG_AUTO_FUNCTION(operator^(infix_detail::thingy<T, A1> t, A2 &&a2))
        (
            return IORATE_EGG_FORWARD(t.m_f)(IORATE_EGG_FORWARD(t.m_a1), IORATE_EGG_FORWARD(a2))
        )


    } // namespace infix


} } // namespace iorate::egg


#endif
