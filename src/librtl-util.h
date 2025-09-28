#ifndef _LIBRTL_BASE_UTIL_H
#define _LIBRTL_BASE_UTIL_H

#include <functional>
#include <cstddef>
#include <tuple>
#include <utility>

// Macro for marking the begining of a new namespace `NAME`
#ifndef NAMESPACE_BEGIN
#   define NAMESPACE_BEGIN(NAME) namespace NAME {
#endif

#ifndef NAMESPACE_END
#   define NAMESPACE_END(NAME) }
#endif

NAMESPACE_BEGIN(rtl)
NAMESPACE_BEGIN(detail)

/**
 * @brief Combine two hashed values into a new hash.
 * 
 * The hash combiner is based on Boost's golden ratio hash cobiner.
 *
 * @param a First hash value to combine
 * @param b Second hash value to combine
 * @return The combined hash value
 */
constexpr std::size_t hash_combine(std::size_t a, std::size_t b)
{
    static_assert(sizeof(std::size_t) == 8 || sizeof(std::size_t) == 4);
    if constexpr (sizeof(std::size_t) == 8) {
        return a ^ (b + 0x9e3779b97f4a7c15ULL + (a << 6) + (a >> 2));
    } else {
        return a ^ (b + 0x9e3779b9 + (b << 6) + (b >> 2));
    }
}

template <typename TUPLE, std::size_t INDEX = 0>
constexpr std::size_t hash_tuple_impl(const TUPLE& tuple) {
    if constexpr(INDEX >= std::tuple_size<TUPLE>::value) {
        return 0; /* An empty tuple hashes to zero, unconditionally */
    } else if constexpr (INDEX == std::tuple_size<TUPLE>::value - 1) {
        auto hasher = std::hash<std::tuple_element_t<INDEX, TUPLE>>{};
        return hasher(std::get<INDEX>(tuple));
    } else {
        auto hasher = std::hash<std::tuple_element_t<INDEX, TUPLE>>{};
        return hash_combine(
            hasher(std::get<INDEX>(tuple)),
            hash_tuple_impl<TUPLE, INDEX + 1>(tuple)
        );
    }
}

/**
 * @breif Hash a tuple of arbitrary number of individually hashable elements
 *
 * @param tuple A tuple whos element can be hashed individually
 * @return The hash value
 */
template <typename... Args>
static inline std::size_t hash_tuple(const std::tuple<Args...>& tuple) {
    return hash_tuple_impl(tuple);
}

NAMESPACE_END(detail)
NAMESPACE_END(rtl)

#endif
