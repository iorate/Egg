#ifndef IORATE_EGG_DETAIL_AUTO_FUNCTION_HPP
#define IORATE_EGG_DETAIL_AUTO_FUNCTION_HPP


#define IORATE_EGG_AUTO_FUNCTION(...) \
    auto __VA_ARGS__ IORATE_EGG_AUTO_FUNCTION_I \
    /**/

#define IORATE_EGG_AUTO_FUNCTION_I(...) \
    IORATE_EGG_AUTO_FUNCTION_II(__VA_ARGS__) \
    /**/

#define IORATE_EGG_AUTO_FUNCTION_II(...) \
    -> decltype(IORATE_EGG_AUTO_FUNCTION_HELPER_ ## __VA_ARGS__) \
    { \
        __VA_ARGS__; \
    } \
    /**/

#define IORATE_EGG_AUTO_FUNCTION_HELPER_return


#endif
