#pragma once

namespace naive {
    template<class T>
    struct default_delete {
        constexpr default_delete() noexcept = default;

        constexpr void operator()(T *ptr) const noexcept {
            delete ptr;
        }
    };

    template<class T>
    struct default_delete<T[]> {
        constexpr default_delete() noexcept = default;

        constexpr void operator()(T *ptr) const noexcept {
            delete[] ptr;
        }
    };
}