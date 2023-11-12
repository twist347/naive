#pragma once

#include <concepts>

namespace naive::concepts {
    template<class T>
    concept is_floating = std::is_floating_point_v<std::remove_cvref_t<T>>;

    template<class T>
    concept is_eq_comparable = requires(std::remove_cvref_t<T> a, std::remove_cvref_t<T> b) {
        { a == b } -> std::convertible_to<bool>;
        { a != b } -> std::convertible_to<bool>;
    };

    template<class T>
    concept is_array_el =
        std::is_default_constructible_v<std::remove_cvref_t<T>> &&
        (std::is_copy_assignable_v<std::remove_cvref_t<T>> || std::is_move_assignable_v<std::remove_cvref_t<T>>) &&
        (std::is_copy_constructible_v<std::remove_cvref_t<T>> || std::is_move_constructible_v<std::remove_cvref_t<T>>) &&
        is_eq_comparable<std::remove_cvref_t<T>>;
}