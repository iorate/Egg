#ifndef IORATE_PACK_HPP
#define IORATE_PACK_HPP


#include <tuple>
#include "./detail/objectify.hpp"


namespace iorate { namespace egg {


    IORATE_EGG_OBJECTIFY(pack, std::forward_as_tuple, noexcept)


} } // namespace iorate::egg


#endif
