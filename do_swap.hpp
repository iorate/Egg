#ifndef IORATE_EGG_SWAP_HPP
#define IORATE_EGG_SWAP_HPP


#include <utility>


namespace iorate { namespace egg {


    namespace do_swap_detail {


        using std::swap;

        template <class T>
        inline void call_aux(T &x, T &y) noexcept(noexcept(swap(x, y)))
        {
            swap(x, y);
        }


    } // namespace do_swap_detail


    struct T_do_swap
    {
        template <class T1, class T2>
        void operator()(T1 &x, T2 &y) const noexcept(noexcept(do_swap_detail::call_aux(x, y)))
        {
            do_swap_detail::call_aux(x, y);
        }
    };

    constexpr T_do_swap do_swap = {};


} } // namespace iorate::egg


#endif
