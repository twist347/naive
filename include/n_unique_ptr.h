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

    template<class T, class Deleter = naive::default_delete<T>>
    class unique_ptr : private Deleter {
    public:
        using pointer = T *;
        using element_type = T;
        using deleter_type = Deleter;

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

        constexpr T &operator*() const {
            return *ptr_;
        }

        constexpr T *operator->() const {
            return ptr_;
        }

        // modifiers

        constexpr T *release() {
            T *copy_ptr = ptr_;
            ptr_ = nullptr;
            return copy_ptr;
        }

        constexpr void reset(pointer ptr = nullptr) noexcept {
            if (ptr == ptr_) {
                return;
            }
            auto copy = ptr_;
            ptr_ = ptr;
            if (copy) {
                get_deleter()(copy);
            }
        }

        constexpr void swap(unique_ptr &other) noexcept {
            std::swap(ptr_, other.ptr_);
            std::swap(static_cast<deleter_type &>(*this), static_cast<deleter_type &>(other));
        }

        // observers

        constexpr pointer get() const noexcept {
            return ptr_;
        }

        constexpr deleter_type &get_deleter() noexcept {
            return static_cast<deleter_type &>(*this);
        }

        constexpr const deleter_type &get_deleter() const noexcept {
            return static_cast<const deleter_type &>(*this);
        }

        explicit operator bool() const noexcept {
            return get() != nullptr;
        }

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

    template<class T, class Deleter>
    class unique_ptr<T[], Deleter> : private Deleter {
    public:
        using pointer = T *;
        using element_type = T;
        using deleter_type = Deleter;

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

        constexpr T &operator[](std::size_t idx) const {
            return ptr_[idx];
        }

        // modifiers

        constexpr T *release() {
            T *copy_ptr = ptr_;
            ptr_ = nullptr;
            return copy_ptr;
        }

        constexpr void reset(pointer ptr = nullptr) noexcept {
            if (ptr == ptr_) {
                return;
            }
            auto copy = ptr_;
            ptr_ = ptr;
            if (copy) {
                get_deleter()(copy);
            }
        }

        constexpr void swap(unique_ptr &other) noexcept {
            std::swap(ptr_, other.ptr_);
            std::swap(static_cast<deleter_type &>(*this), static_cast<deleter_type &>(other));
        }

        // observers

        constexpr pointer get() const noexcept {
            return ptr_;
        }

        constexpr deleter_type &get_deleter() noexcept {
            return static_cast<deleter_type &>(*this);
        }

        constexpr const deleter_type &get_deleter() const noexcept {
            return static_cast<const deleter_type &>(*this);
        }

        explicit operator bool() const noexcept {
            return get() != nullptr;
        }

    private:
        pointer ptr_;
    };
}
