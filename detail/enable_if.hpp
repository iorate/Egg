#ifndef IORATE_EGG_DETAIL_ENABLE_IF_HPP
#define IORATE_EGG_DETAIL_ENABLE_IF_HPP


#include <type_traits>


// http://d.hatena.ne.jp/gintenlabo/20110413/1302675301
#define IORATE_EGG_ENABLE_IF(cond) typename ::std::enable_if<(cond)>::type * = nullptr


#endif
