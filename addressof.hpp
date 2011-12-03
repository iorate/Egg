#ifndef IORATE_ADDRESSOF_HPP
#define IORATE_ADDRESSOF_HPP


namespace iorate { namespace egg {


    struct T_addressof
    {
        template <class T>
        constexpr T *operator()(T &t) noexcept
        {
            return (T *)(T const volatile *)&(char const volatile &)(T const volatile &)t;
        }
    };

    constexpr T_addressof addressof = {};


} } // namespace iorate::egg


#endif 
