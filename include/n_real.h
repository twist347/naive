#pragma once

#include <iostream>
#include <n_concepts.h>

namespace naive {

    template<concepts::is_numeric T>
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
            value_ /= r.value_;
            return *this;
        }

        real &operator%=(const real &r) {
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

        real *operator&() {
            return this;
        }

        // conversion to value_type
        operator value_type()  {
            return value_;
        }

        auto operator<=>(const real &other) const = default;

        template<concepts::is_numeric U>
        friend std::ostream &operator<<(std::ostream &os, const real<U> &r);

        template<concepts::is_numeric U>
        friend std::istream &operator>>(std::istream &is, real<U> &r);

    private:
        value_type value_;
    };

    template<concepts::is_numeric T>
    real<T> operator+(const real<T> &lhs, const real<T> &rhs) {
        auto result = lhs;
        result += rhs;
        return result;
    }

    template<concepts::is_numeric T>
    real<T> operator-(const real<T> &lhs, const real<T> &rhs) {
        auto result = lhs;
        result -= rhs;
        return result;
    }

    template<concepts::is_numeric T>
    real<T> operator*(const real<T> &lhs, const real<T> &rhs) {
        auto result = lhs;
        result *= rhs;
        return result;
    }

    template<concepts::is_numeric T>
    real<T> operator/(const real<T> &lhs, const real<T> &rhs) {
        auto result = lhs;
        result /= rhs;
        return result;
    }

    template<concepts::is_integral T>
    real<T> operator%(const real<T> &lhs, const real<T> &rhs) {
        auto result = lhs;
        result %= rhs;
        return result;
    }

    template<concepts::is_numeric T>
    std::ostream &operator<<(std::ostream &os, const real<T> &r) {
        os << r.value_;
        return os;
    }

    template<concepts::is_numeric T>
    std::istream &operator>>(std::istream &is, real<T> &r) {
        is >> r.value_;
        return is;
    }
}

