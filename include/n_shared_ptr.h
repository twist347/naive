#pragma once

#include <n_allocator.h>
#include <n_deleter.h>

namespace naive {
    template<class T>
    class shared_ptr {
    public:
        using pointer = T *;
        using element_type = T;

        constexpr shared_ptr() : cb_(nullptr) {}

        constexpr explicit shared_ptr(T *ptr) : cb_(new control_block(ptr)) {}

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
            cb_ = new control_block(ptr);
        }

        constexpr void swap(shared_ptr &other) noexcept {
            std::swap(cb_, other.cb_);
        }

        // observers

        constexpr T *get() const noexcept {
            return cb_ ? cb_->ptr_ : nullptr;
        }

        constexpr T &operator*() const {
            return *cb_->ptr_;
        }

        constexpr T *operator->() const {
            return cb_->ptr_;
        }

        constexpr T &operator[](std::ptrdiff_t idx) const {
            return get()[idx];
        }

    private:
        struct control_block {
            constexpr explicit control_block(T *ptr) : ptr_(ptr), count_(1) {}

            ~control_block() {
                delete ptr_;
            }

            T *ptr_;
            std::size_t count_;
        };

        control_block *cb_;
    };

    template<class T, class ... Args>
    constexpr auto make_shared(Args &&... args) {
        return shared_ptr<T>(new T(std::forward<Args>(args)...));
    }
}
