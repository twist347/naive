#pragma once

#include <utility>

namespace naive {

    // stateless allocator

    template<class T>
    struct allocator {
        using value_type = std::remove_cvref_t<T>;
        using pointer = value_type *;
        using const_pointer = const pointer;
        using reference = value_type &;
        using const_reference = const value_type &;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        // coercion ctor
        template<class U>
        constexpr allocator(const allocator<U> &) {}

        constexpr allocator() = default;

        constexpr allocator(const allocator &) = default;

        [[nodiscard]] constexpr pointer allocate(size_type n) {
            return n == 0 ? nullptr : static_cast<pointer>(::operator new(n * sizeof(value_type)));
        }

        constexpr void deallocate(pointer ptr, size_type size) {
            ::operator delete(ptr);
        }

        template<class ... Args>
        constexpr void construct(pointer ptr, Args &&... args) {
            ::new(static_cast<void *>(ptr)) value_type(std::forward<Args>(args)...);
        }

        constexpr void destroy(pointer ptr) noexcept {
            ptr->~value_type();
        }

        constexpr pointer address(reference ref) const noexcept {
            return std::addressof(ref);
        }

        constexpr const_pointer address(const_reference ref) const noexcept {
            return static_cast<const_pointer>(std::addressof(ref));
        }

        [[nodiscard]] size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max() / sizeof(value_type);
        }
    };

    template<class T>
    bool operator==(const allocator<T> &, const allocator<T> &) {
        return true;
    }

    template<class T>
    bool operator!=(const allocator<T> &, const allocator<T> &) {
        return false;
    }
}

