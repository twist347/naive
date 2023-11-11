#pragma once

#include <concepts>
#include <cmath>

namespace utils {
    template<class T>
    concept is_floating = std::is_floating_point_v<T>;

    template<is_floating T, is_floating U>
    constexpr auto to(U u) -> T {
        return static_cast<T>(u);
    }

    template<is_floating T>
    auto eps = to<T>(1e-10);

    template<is_floating T>
    constexpr auto eq(const T &lhs, const T &rhs) -> bool {
        return std::abs(lhs - rhs) < eps<T>;
    }
}