#pragma once

#include <iostream>
#include <algorithm>
#include <array>

namespace naive {
    template<std::size_t D, class T = double, class Container = std::array<T, D>>
    class point {
    public:
        template<class ... Args>
        constexpr point(Args &&... args) requires (sizeof...(Args) == D)
            && (std::is_same_v<T, std::remove_cvref_t<Args>> && ...) : coords{ std::forward<Args>(args)... } {}

        constexpr T &operator[](size_t idx) {
            return coords[idx];
        }

        constexpr const T &operator[](size_t idx) const {
            return coords[idx];
        }

        constexpr point &operator+=(const point &other) {
            for (size_t i = 0; i < D; ++i) {
                coords[i] += other.coords[i];
            }
            return *this;
        }

        constexpr point &operator-=(const point &other) {
            for (size_t i = 0; i < D; ++i) {
                coords[i] -= other.coords[i];
            }
            return *this;
        }

        template<std::size_t D1, class T1, class C1>
        friend constexpr std::ostream &operator<<(std::ostream &os, const point<D1, T1, C1> &p);

        template<std::size_t D1, class T1, class C1>
        friend constexpr T1 operator*(const point<D1, T1, C1> &lhs, const point<D1, T1, C1> &rhs);

    private:
        Container coords;
    };

    template<std::size_t D, class T, class C>
    constexpr std::ostream &operator<<(std::ostream &os, const point<D, T, C> &p) {
        os << '{';
        for (size_t i = 0; i < D - 1; ++i) {
            os << p.coords[i] << ',';
        }
        os << p.coords[D - 1] << '}';
        return os;

    }

    template<std::size_t D, class T = double, class C = std::array<T, D>>
    constexpr point<D, T, C> operator+(const point<D, T, C> &lhs, const point<D, T, C> &rhs) {
        auto result = lhs;
        result += rhs;
        return result;
    }

    template<std::size_t D, class T = double, class C = std::array<T, D>>
    constexpr point<D, T, C> operator-(const point<D, T, C> &lhs, const point<D, T, C> &rhs) {
        auto result = lhs;
        result -= rhs;
        return result;
    }

    template<std::size_t D, class T, class C>
    constexpr T operator*(const point<D, T, C> &lhs, const point<D, T, C> &rhs) {
        T res = static_cast<T>(0);
        for (size_t i = 0; i < D; ++i) {
            res += lhs.coords[i] * rhs.coords[i];
        }
        return res;
    }
}

