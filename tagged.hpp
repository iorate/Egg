#ifndef IORATE_EGG_TAGGED_HPP
#define IORATE_EGG_TAGGED_HPP


#include <type_traits>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/placeholders.hpp>
#include "./detail/auto_function.hpp"
#include "./detail/move.hpp"
#include "./detail/unspecified.hpp"
#include "./generator.hpp"


namespace iorate { namespace egg {


    namespace tagged_detail {


        template <class F, class Tag>
        struct result_
        {
            F m_f;

            constexpr F const &base() noexcept
            {
                return m_f;
            }

            template <class ...Args>
            constexpr IORATE_EGG_AUTO_FUNCTION(operator()(Args &&...args))
            (
                return m_f(IORATE_EGG_FORWARD(args)...)
            )
        };


    } // namespace tagged_detail


    template <class Tag>
    struct X_tagged
      : generator<tagged_detail::result_<std::decay<boost::mpl::_1>, Tag>>::type
    {};

    template <class Tag, class F>
    constexpr IORATE_EGG_AUTO_FUNCTION(tagged(F &&f))
    (
        return X_tagged<Tag>()(IORATE_EGG_FORWARD(f))
    )


    namespace tag_of_detail {

        
        template <class F>
        struct aux_
        {
            using type = unspecified;
        };

        template <class F, class Tag>
        struct aux_<tagged_detail::result_<F, Tag>>
        {
            using type = Tag;
        };


    } // namespace tag_of_detail


    template <class F>
    struct tag_of
      : tag_of_detail::aux_<typename std::remove_cv<F>::type>
    {};


    template <class F, class Tag>
    struct is_tagged_with
      : boost::mpl::false_
    {};

    template <class F>
    struct is_tagged_with<F, typename tag_of<F>::type>
      : boost::mpl::true_
    {};


} } // namespace iorate::egg


#endif
