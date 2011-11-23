#ifndef IORATE_EGG_MEMOIZE_HPP
#define IORATE_EGG_MEMOIZE_HPP


#include <memory>
#include <type_traits>
#include <unordered_map>
#include <boost/any.hpp>
#include <boost/mpl/placeholders.hpp>
#include "./detail/auto_function.hpp"
#include "./detail/move.hpp"
#include "./generator.hpp"


namespace iorate { namespace egg {


    namespace memoize_detail {


        template <class F>
        struct fixed
        {
            F m_f;
            std::shared_ptr<boost::any> m_pany;

            fixed(F const &f)
              : m_f(f), m_pany(new boost::any())
            {}

            template <class A1, class Re = typename std::decay<typename std::result_of<F const &(fixed const &, A1)>::type>::type>
            Re operator()(A1 a1) const
            {
                typedef std::unordered_map<A1, Re> map_t;

                if (m_pany->empty())
                    *m_pany = map_t();

                map_t &m = boost::any_cast<map_t &>(*m_pany);

                auto it = m.find(a1);
                if (it != m.end())
                    return it->second;
                else
                    return m.insert({ a1, m_f(*this, A1(a1)) }).first->second;
            }
        };


        template <class F>
        struct result_
        {
            F m_f;

            constexpr F const &base() noexcept
            {
                return m_f;
            }

            template <class A1>
            IORATE_EGG_AUTO_FUNCTION(operator()(A1 &&a1) const)
            (
                return fixed<F>(m_f)(IORATE_EGG_FORWARD(a1))
            )
        };


    } // namespace memoize_detail


    typedef
        generator<memoize_detail::result_<std::decay<boost::mpl::_1>>>::type
    T_memoize;

    constexpr T_memoize memoize = {};


} } // namespace iorate::egg


#endif
