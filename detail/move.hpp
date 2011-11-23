#ifndef IORATE_EGG_DETAIL_MOVE_HPP
#define IORATE_EGG_DETAIL_MOVE_HPP


#include <type_traits>
#include <utility>


namespace iorate { namespace egg {


#if defined(__GNUC__)


    using std::forward;
    using std::move;


#else


    template <class T>
    constexpr T &&forward(typename std::remove_reference<T>::type &t) noexcept
    {
        return static_cast<T &&>(t);
    }

    template <class T>
    constexpr T &&forward(typename std::remove_reference<T>::type &&t) noexcept
    {
        static_assert(!std::is_lvalue_reference<T>::value, "error: template argument is a lvalue reference type");
        return static_cast<T &&>(t);
    }


    template <class T>
    constexpr typename std::remove_reference<T>::type &&move(T &&t) noexcept
    {
        return static_cast<typename std::remove_reference<T>::type &&>(t);
    }


#endif


} } // namespace iorate::egg


// http://d.hatena.ne.jp/gintenlabo/20110721/1311271956
#define IORATE_EGG_FORWARD(a) ::iorate::egg::forward<decltype(a)>(a)


#endif
