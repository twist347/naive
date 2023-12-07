#pragma once

#include <n_allocator.h>
#include <n_deleter.h>

namespace naive {
    template<class T>
    class shared_ptr {
    public:
        using element_type = std::remove_extent_t<T>;
        using pointer = element_type *;

        // ctors and dtor

        constexpr shared_ptr() : cb_(nullptr) {}

        constexpr explicit shared_ptr(pointer ptr) : cb_(new cb_t(ptr)) {}

        constexpr shared_ptr(const shared_ptr &other) : cb_(other.cb_) {
            ++cb_->count_;
        }

        constexpr shared_ptr &operator=(const shared_ptr &other) {
            if (this == &other) {
                return *this;
            }
            if (cb_ && --cb_->count_ == 0) {
                delete cb_;
            }
            cb_ = other.cb_;
            ++cb_->count_;
            return *this;
        }

        constexpr shared_ptr(shared_ptr &&other) noexcept: cb_(other.cb_) {
            other.cb_ = nullptr;
        }

        constexpr shared_ptr &operator=(shared_ptr &&other) noexcept {
            if (this == &other) {
                return *this;
            }
            if (cb_ && --cb_->count_ == 0) {
                delete cb_;
            }
            cb_ = other.cb_;
            other.cb_ = nullptr;
            return *this;
        }

        constexpr ~shared_ptr() {
            if (cb_ && --cb_->count_ == 0) {
                delete cb_;
            }
        }

        // modifiers

        constexpr void reset() noexcept {
            if (cb_ && --cb_->count_ == 0) {
                delete cb_;
            }
            cb_ = nullptr;
        }

        constexpr void reset(pointer ptr) noexcept {
            reset();
            cb_ = new cb_t(ptr);
        }

        constexpr void swap(shared_ptr &other) noexcept {
            std::swap(cb_, other.cb_);
        }

        // observers

        constexpr pointer get() const noexcept {
            return cb_ ? cb_->ptr_ : nullptr;
        }

        constexpr element_type &operator*() const requires(!std::is_array_v<T>) {
            return *cb_->ptr_;
        }

        constexpr pointer operator->() const requires(!std::is_array_v<T>) {
            return cb_->ptr_;
        }

        constexpr element_type &operator[](std::ptrdiff_t idx) const requires std::is_array_v<T> {
            return get()[idx];
        }

        long use_count() const noexcept {
            return cb_ ? cb_->count_ : 0;
        }

        explicit operator bool() const noexcept {
            return get() != nullptr;
        }

    private:
        template<class U, class Deleter = naive::default_delete<U>>
        struct control_block : private Deleter {

            using element_type = std::remove_extent_t<U>;
            using pointer = element_type *;
            using deleter_type = Deleter;

            constexpr explicit control_block(pointer ptr) : ptr_(ptr), count_(1) {}

            ~control_block() {
                get_deleter()(ptr_);
            }

            constexpr deleter_type &get_deleter() noexcept {
                return static_cast<deleter_type &>(*this);
            }

            constexpr const deleter_type &get_deleter() const noexcept {
                return static_cast<const deleter_type &>(*this);
            }

            pointer ptr_;
            std::size_t count_;
        };

        using cb_t = control_block<T>;
        cb_t *cb_;
    };

    template<class T, class ...Args>
    requires(!std::is_array_v<T>)
    constexpr auto make_shared(Args &&...args) {
        return naive::shared_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template<class T>
    requires(std::is_array_v<T>)
    constexpr auto make_shared(std::size_t n) {
        return naive::shared_ptr<T>(new std::remove_extent_t<T>[n]);
    }
}

