#ifndef YEARN_UTILS_H
#define YEARN_UTILS_H

#include <type_traits>

template <typename T, typename... Args>
constexpr bool is_in(T value, Args... args) {
    static_assert(std::is_enum_v<T>, "T must be an enum type");
    return ((value == args) || ...);
}

#endif  // YEARN_UTILS_H
