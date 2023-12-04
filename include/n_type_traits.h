#pragma once

#include <stdfloat>

namespace naive {
    template<class T, T v>
    struct integral_constant {
        static constexpr T value = v;
        using value_type = T;
        using type = integral_constant;

        constexpr operator value_type() const noexcept { return value; }

        constexpr value_type operator()() const noexcept { return value; }
    };

    template<bool B>
    using bool_constant = integral_constant<bool, B>;

    using true_type = bool_constant<true>;
    using false_type = bool_constant<false>;

    // type relationships

    template<class T, class U>
    struct is_same : false_type {};

    template<class T>
    struct is_same<T, T> : true_type {};

    template<class T, class U>
    constexpr bool is_same_v = is_same<T, U>::value;

    // const-volatility specifiers

    template<class T>
    struct remove_cv {
        using type = T;
    };

    template<class T>
    struct remove_cv<const T> {
        using type = T;
    };

    template<class T>
    struct remove_cv<volatile T> {
        using type = T;
    };

    template<class T>
    struct remove_cv<const volatile T> {
        using type = T;
    };

    template<class T>
    struct remove_const {
        using type = T;
    };

    template<class T>
    struct remove_const<const T> {
        using type = T;
    };

    template<class T>
    struct remove_volatile {
        using type = T;
    };

    template<class T>
    struct remove_volatile<volatile T> {
        using type = T;
    };

    template<class T>
    using remove_cv_t = typename remove_cv<T>::type;

    template<class T>
    using remove_const_t = typename remove_const<T>::type;

    template<class T>
    using remove_volatile_t = typename remove_volatile<T>::type;

    template<class T>
    struct add_cv {
        using type = const volatile T;
    };

    template<class T>
    struct add_const {
        using type = const T;
    };

    template<class T>
    struct add_volatile {
        using type = volatile T;
    };

    template<class T>
    using add_cv_t = typename add_cv<T>::type;

    template<class T>
    using add_const_t = typename add_const<T>::type;

    template<class T>
    using add_volatile_t = typename add_volatile<T>::type;

    // primary type categories

    template<class T>
    struct is_void : std::is_same<void, remove_cv_t<T>> {};

    template<class T>
    constexpr bool is_void_v = is_void<T>::value;

    template<class T>
    struct is_null_pointer : is_same<std::nullptr_t, remove_cv_t<T>> {};

    template<class T>
    constexpr bool is_null_pointer_v = is_null_pointer<T>::value;

    // TODO: is_integral

    template<class T>
    struct is_floating_point : bool_constant<
            is_same_v<float, remove_cv_t<T>>
            || is_same_v<double, remove_cv_t<T>>
            || is_same_v<long double, remove_cv_t<T>>
            || is_same_v<std::float16_t, remove_cv_t<T>>
            || is_same_v<std::float32_t, remove_cv_t<T>>
            || is_same_v<std::float64_t, remove_cv_t<T>>
            || is_same_v<std::float128_t, remove_cv_t<T>>> {};

    template<class T>
    constexpr bool is_floating_point_v = is_floating_point<T>::value;

    template<class T>
    struct is_array : false_type {};

    template<class T>
    struct is_array<T[]> : true_type {};

    template<class T, std::size_t N>
    struct is_array<T[N]> : true_type {};

    template<class T>
    constexpr bool is_array_v = is_array<T>::value;

    // TODO: is_enum
    // TODO: is_union
    // TODO: is_class
    // TODO: is_function

    template<class T>
    struct is_pointer : false_type {};

    template<class T>
    struct is_pointer<T *> : true_type {};

    template<class T>
    struct is_pointer<T * const> : true_type {};

    template<class T>
    struct is_pointer<volatile T *> : true_type {};

    template<class T>
    struct is_pointer<const volatile T *> : true_type {};

    template<class T>
    constexpr bool is_pointer_v = is_pointer<T>::value;

    template<class T>
    struct is_lvalue_reference : false_type {};

    template<class T>
    struct is_lvalue_reference<T &> : true_type {};

    template<class T>
    constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

    template<class T>
    struct is_rvalue_reference : false_type {};

    template<class T>
    struct is_rvalue_reference<T &&> : true_type {};

    template<class T>
    constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;

    // TODO: is_member_object_pointer
    // TODO: is_member_function_pointer

    // composite type categories

    // TODO: is_fundamental
    // TODO: is_arithmetic (because of is_integral)
    // TODO: is_scalar (because of ...)
    // TODO: is_object (because of ...)
    // TODO: is_compound (because of ...)

    template<class T>
    struct is_reference : false_type {};

    template<class T>
    struct is_reference<T &> : true_type {};

    template<class T>
    struct is_reference<T &&> : true_type {};

    template<class T>
    constexpr bool is_reference_v = is_reference<T>::value;

    // TODO: is_member_pointer

    // type properties

    template<class T>
    struct is_const : false_type {};

    template<class T>
    struct is_const<const T> : true_type {};

    template<class T>
    constexpr bool is_const_v = is_const<T>::value;

    template<class T>
    struct is_volatile : false_type {};

    template<class T>
    struct is_volatile<volatile T> : true_type {};

    template<class T>
    constexpr bool is_volatile_v = is_volatile<T>::value;

    // TODO: type properties
}