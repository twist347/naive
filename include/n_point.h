#pragma once

#include <iostream>
#include <algorithm>
#include <array>

namespace naive {
    template<std::size_t D, class T = double, class Container = std::array<T, D>>
    class point {
    public:
        template<class ... Args>
        constexpr point(Args &&... args)requires (sizeof...(Args) == D)
            && (std::is_same_v<T, std::remove_cvref_t<Args>> && ...)
                : coords{ std::forward<Args>(args)... } {}

        constexpr T &operator[](size_t idx) {
            return coords[idx];
        }
        constexpr const T &operator[](size_t idx) const noexcept {
            return coords[idx];
        }

        constexpr point &operator+=(const point &other) {
            for (size_t i = 0; i < D; ++i) {
                coords[i] += other.coords[i];
            }
            return *this;
        }

        friend constexpr std::ostream &operator<<(std::ostream &os, const point &p) {
            os << '{';
            for (size_t i = 0; i < D - 1; ++i) {
                os << p.coords[i] << ',';
            }
            os << p.coords[D - 1] << '}';
            return os;
        }

    private:
        Container coords;
    };

    template<std::size_t D, class T = double, class C = std::array<T, D>>
    constexpr point<D, T, C> operator+(const point<D, T, C> &lhs, const point<D, T, C> &rhs) {
        auto result = lhs;
        result += rhs;
        return result;
    }
}

