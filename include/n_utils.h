#pragma once

#include <concepts>
#include <cmath>
#include <n_concepts.h>

namespace naive::utils {
    template<concepts::is_numeric T, concepts::is_numeric U>
    constexpr auto to(U u) -> T {
        return static_cast<T>(u);
    }

    template<concepts::is_floating T>
    auto eps = to<T>(1e-10);

    template<concepts::is_floating T>
    constexpr auto eq_flt(const T &lhs, const T &rhs) -> bool {
        return std::abs(lhs - rhs) < eps<T>;
    }
}