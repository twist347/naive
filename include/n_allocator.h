#pragma once

#include <utility>

namespace naive {

    template<class T>
    struct allocator {
        using value_type = T;
        using pointer = value_type *;
        using const_pointer = const pointer;
        using reference = value_type &;
        using const_reference = const value_type &;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        constexpr pointer allocate(size_type size) {
            return size == 0 ? nullptr : static_cast<pointer>(::operator new(size * sizeof(value_type)));
        }

        constexpr void deallocate(pointer ptr, size_type size) {
            operator delete[](ptr);
        }

        template<class ... Args>
        constexpr void construct(pointer ptr, const Args &&... args) {
            new(ptr) value_type(std::forward<Args>(args)...);
        }

        constexpr void destroy(pointer ptr) {
            ptr->~value_type();
        }
    };
}
