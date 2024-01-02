#pragma once

#include <iostream>
#include <algorithm>
#include <n_allocator.h>
#include <n_buffer.h>

namespace naive {

    // heap array implementation with strong exception safety

    template<class T, class Allocator = naive::allocator<T>>
    class array : protected array_raw_buffer<T, Allocator> {

    public:
        using value_type = std::remove_cvref_t<T>;
        using size_type = std::size_t;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = value_type *;
        using const_pointer = const value_type *;
        using iterator = value_type *;
        using const_iterator = const value_type *;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using difference_type = std::ptrdiff_t;

        // ctors and dtor

        constexpr array() = default;

        constexpr explicit array(size_type size) : array_raw_buffer<value_type>(size) {
            for (size_type i = 0; i < size_; ++i) {
                alloc_.construct(buffer_ + i);
            }
        }

        constexpr array(size_type size, const Allocator &alloc) : array_raw_buffer<value_type>(size, alloc) {
            for (size_type i = 0; i < size_; ++i) {
                alloc_.construct(buffer_ + i);
            }
        }

        constexpr array(size_type size, const value_type &val) : array(size) {
            std::fill(begin(), end(), val);
        }

        constexpr array(std::initializer_list<value_type> il) : array_raw_buffer<value_type>(il.size()) {
            auto it = il.begin();
            for (size_type i = 0; i < size_; ++i) {
                alloc_.construct(buffer_ + i, *it++);
            }
        }

        constexpr array(const array &other) : array_raw_buffer<value_type>(other.size()) {
            for (size_type i = 0; i < size_; ++i) {
                alloc_.construct(buffer_ + i, other.buffer_[i]);
            }
        }

        constexpr array &operator=(const array &other) {
            // TODO: may be inefficient if size == other.size
            array copy = other;
            std::swap(*this, copy);
            return *this;
        }

        constexpr array(array &&other) noexcept = default;

        constexpr array &operator=(array &&other) noexcept = default;

        constexpr ~array() = default;

        // element access

        constexpr reference operator[](size_type idx) { return begin()[idx]; }

        constexpr const_reference operator[](size_type idx) const noexcept { return begin()[idx]; }

        constexpr pointer data() { return buffer_; }

        constexpr const_pointer data() const { return buffer_; }

        constexpr reference at(size_type idx) {
            if (idx >= size_) {
                throw std::out_of_range("out of bound");
            }
            return operator[](idx);
        }

        constexpr const_reference at(size_type idx) const {
            if (idx >= size_) {
                throw std::out_of_range("out of bound");
            }
            return operator[](idx);
        }

        constexpr reference front() noexcept { return *begin(); }

        constexpr const_reference front() const noexcept { return *begin(); }

        constexpr reference back() noexcept { return *(end() - 1); }

        constexpr const_reference back() const noexcept { return *(end() - 1); }

        // iterators

        constexpr iterator begin() noexcept { return data(); }

        constexpr const_iterator begin() const noexcept { return data(); }

        constexpr iterator end() noexcept { return begin() + size(); }

        constexpr const_iterator end() const noexcept { return begin() + size(); }

        constexpr const_iterator cbegin() const noexcept { return begin(); }

        constexpr const_iterator cend() const noexcept { return end(); }

        constexpr reverse_iterator rbegin() noexcept { return static_cast<reverse_iterator>(end()); }

        constexpr const_reverse_iterator rbegin() const noexcept { return static_cast<const_reverse_iterator>(end()); }

        constexpr reverse_iterator rend() noexcept { return static_cast<reverse_iterator>(begin()); }

        constexpr const_reverse_iterator rend() const noexcept { return static_cast<const_reverse_iterator>(begin()); }

        constexpr const_reverse_iterator crbegin() const noexcept { return static_cast<const_reverse_iterator>(end()); }

        constexpr const_reverse_iterator crend() const noexcept { return static_cast<const_reverse_iterator>(begin()); }

        // capacity

        constexpr size_type size() const noexcept { return size_; }

        constexpr bool empty() const noexcept { return size() == static_cast<size_type>(0); }

        // operations

        constexpr void fill(const value_type &val) { std::fill(begin(), end(), val); }

        constexpr void swap(array &other) {
            std::swap(size_, other.size_);
            std::swap(buffer_, other.buffer_);
        }

    private:
        using arb = array_raw_buffer<T, Allocator>;

        using arb::alloc_;
        using arb::size_;
        using arb::buffer_;
    };

    // print

    template<class T>
    std::ostream &operator<<(std::ostream &os, const array<T> &arr) {
        std::for_each(arr.begin(), arr.end(), [&os](const auto &val) { os << val << ' '; });
        return os;
    }

    // comparisons

    template<class T>
    constexpr bool operator==(const array<T> &lhs, const array<T> &rhs) {
        if (lhs.size() != rhs.size()) {
            return false;
        }
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template<class T>
    constexpr bool operator!=(const array<T> &lhs, const array<T> &rhs) {
        return !(lhs == rhs);
    }
}
