#pragma once

#include <concepts>
#include <iostream>

namespace naive {
    namespace detail {
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

    template<detail::is_floating T>
    class real {
    public:
        using value_type = T;

        real(const value_type &value) : value_(value) {}

        // forbid a + b = c
        real &operator=(const real &other) & = default;

        real &operator+=(const real &r) {
            value_ += r.value_;
            return *this;
        }

        real &operator-=(const real &r) {
            value_ -= r.value_;
            return *this;
        }

        real &operator*=(const real &r) {
            value_ *= r.value_;
            return *this;
        }

        real &operator/=(const real &r) {
            if (detail::eq<value_type>(r.value_, detail::to<value_type>(0.0))) {
                throw std::invalid_argument("division by zero");
            }
            value_ /= r.value_;
            return *this;
        }

        real &operator%=(const real &r) {
            if (detail::eq<value_type>(r.value_, detail::to<value_type>(0.0))) {
                throw std::invalid_argument("division by zero");
            }
            value_ %= r.value_;
            return *this;
        }

        real &operator++() {
            ++this->value_;
            return *this;
        }

        real operator++(int) {
            auto copy = *this;
            operator++();
            return copy;
        }

        real &operator--() {
            --this->value_;
            return *this;
        }

        real operator--(int) {
            auto copy = *this;
            operator--();
            return copy;
        }

        // conversion to value_type
        operator value_type() {
            return value_;
        }

        template<detail::is_floating U>
        friend std::ostream &operator<<(std::ostream &os, const real<U> &r);

        template<detail::is_floating U>
        friend std::istream &operator>>(std::istream &is, real<U> &r);

    private:
        value_type value_;
    };

    template<detail::is_floating T>
    real<T> operator+(const real<T> &lhs, const real<T> &rhs) {
        auto result = lhs;
        result += rhs;
        return result;
    }

    template<detail::is_floating T>
    real<T> operator-(const real<T> &lhs, const real<T> &rhs) {
        auto result = lhs;
        result -= rhs;
        return result;
    }

    template<detail::is_floating T>
    real<T> operator*(const real<T> &lhs, const real<T> &rhs) {
        auto result = lhs;
        result *= rhs;
        return result;
    }

    template<detail::is_floating T>
    real<T> operator/(const real<T> &lhs, const real<T> &rhs) {
        auto result = lhs;
        result /= rhs;
        return result;
    }

    template<detail::is_floating T>
    real<T> operator%(const real<T> &lhs, const real<T> &rhs) {
        auto result = lhs;
        result %= rhs;
        return result;
    }

    template<detail::is_floating T>
    std::ostream &operator<<(std::ostream &os, const real<T> &r) {
        os << r.value_;
        return os;
    }

    template<detail::is_floating U>
    std::istream &operator>>(std::istream &is, real<U> &r) {
        is >> r.value_;
        return is;
    }
}

