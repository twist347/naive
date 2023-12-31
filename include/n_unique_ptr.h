#pragma once

#include <utility>
#include <n_deleter.h>

namespace naive {

    template<class T, class Deleter = naive::default_delete<T>>
    class unique_ptr : private Deleter {
    public:
        using element_type = std::remove_extent_t<T>;
        using pointer = element_type *;
        using deleter_type = Deleter;

        // ctors and dtor

        constexpr unique_ptr() : ptr_(nullptr) {}

        constexpr explicit unique_ptr(pointer ptr) : ptr_(ptr) {}

        constexpr unique_ptr(pointer ptr, const Deleter &deleter) : Deleter(deleter), ptr_(ptr) {}

        constexpr unique_ptr(const unique_ptr &) = delete;

        constexpr unique_ptr &operator=(const unique_ptr &) = delete;

        constexpr unique_ptr(unique_ptr &&other) noexcept: ptr_(other.ptr_) {
            other.ptr_ = nullptr;
        }

        constexpr unique_ptr &operator=(unique_ptr &&other) noexcept {
            if (this == &other) {
                return *this;
            }
            reset(other.release());
            return *this;
        }

        constexpr ~unique_ptr() {
            get_deleter()(ptr_);
        }

        constexpr typename std::add_lvalue_reference_t<T>
        operator*() const noexcept(noexcept(*std::declval<pointer>())) requires (!std::is_array_v<T>) { return *ptr_; }

        constexpr pointer operator->() const requires (!std::is_array_v<T>) { return ptr_; }

        constexpr element_type &operator[](std::size_t idx) const requires std::is_array_v<T> { return get()[idx]; }

        // modifiers

        constexpr pointer release() {
            auto copy_ptr = ptr_;
            ptr_ = nullptr;
            return copy_ptr;
        }

        constexpr void reset(pointer ptr = nullptr) noexcept {
            if (ptr == get()) {
                return;
            }
            auto copy_ptr = get();
            ptr_ = ptr;
            get_deleter()(copy_ptr);
        }

        constexpr void swap(unique_ptr &other) noexcept {
            std::swap(ptr_, other.ptr_);
            // TODO: is it?
            std::swap(static_cast<deleter_type &>(*this), static_cast<deleter_type &>(other));
        }

        // observers

        constexpr pointer get() const noexcept { return ptr_; }

        constexpr deleter_type &get_deleter() noexcept { return static_cast<deleter_type &>(*this); }

        constexpr const deleter_type &get_deleter() const noexcept { return static_cast<const deleter_type &>(*this); }

        explicit operator bool() const noexcept { return get() != nullptr; }

    private:
        pointer ptr_;
    };

    template<class T, class D>
    constexpr bool operator==(const unique_ptr<T, D> &lhs, const unique_ptr<T, D> &rhs) {
        return lhs.get() == rhs.get();
    }

    template<class T, class D>
    constexpr bool operator!=(const unique_ptr<T, D> &lhs, const unique_ptr<T, D> &rhs) {
        return !(lhs == rhs);
    }

    template<class T, class D>
    constexpr bool operator<(const unique_ptr<T, D> &lhs, const unique_ptr<T, D> &rhs) {
        return std::less<typename std::remove_cvref_t<decltype(lhs)>::pointer>{}(lhs.get(), rhs.get());
    }

    template<class T, class D>
    constexpr bool operator>(const unique_ptr<T, D> &lhs, const unique_ptr<T, D> &rhs) {
        return rhs < lhs;
    }

    template<class T, class D>
    constexpr bool operator<=(const unique_ptr<T, D> &lhs, const unique_ptr<T, D> &rhs) {
        return !(rhs < lhs);
    }

    template<class T, class D>
    constexpr bool operator>=(const unique_ptr<T, D> &lhs, const unique_ptr<T, D> &rhs) {
        return !(lhs < rhs);
    }

    template<class T, class ...Args>
    requires(!std::is_array_v<T>)
    constexpr auto make_unique(Args &&...args) {
        return naive::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template<class T>
    requires(std::is_array_v<T>)
    constexpr auto make_unique(std::size_t n) {
        return naive::unique_ptr<T>(new std::remove_extent_t<T>[n]);
    }

    // TODO: make_unique_for_overwrite
}
