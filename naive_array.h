#pragma once

#include <iostream>
#include <iterator>
#include <algorithm>

namespace naive {

    template<class T>
    class array {
    public:
        using value_type = T;
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

        constexpr explicit array(size_type sz) : size_(sz), buffer_(allocate(size_)) {}

        constexpr array(size_type sz, const value_type &val) : size_(sz), buffer_(allocate(size_)) {
            std::fill(begin(), end(), val);
        }

        constexpr array(std::initializer_list<value_type> il) : size_(il.size()), buffer_(allocate(size_)) {
            std::copy(il.begin(), il.end(), begin());
        }

        constexpr array(const array &other) : size_(other.size_) {
            auto new_buffer = allocate(size_);
            std::copy(other.buffer_, other.buffer_ + other.size_, new_buffer);
            buffer_ = new_buffer;
        }

        constexpr array &operator=(const array &other) {
            array copy(other);
            std::swap(copy, *this);
            return *this;
        }

        constexpr array(array &&other) noexcept: size_(other.size_), buffer_(other.buffer_) {
            other.size_ = 0;
            other.buffer_ = nullptr;
        }

        constexpr array &operator=(array &&other) noexcept {
            deallocate(buffer_);

            std::swap(buffer_, other.buffer_);
            std::swap(size_, other.size_);

            other.buffer_ = nullptr;
            other.size_ = 0;
            return *this;
        }

        constexpr ~array() {
            size_ = 0;
            delete[] buffer_;
        }

        // access

        constexpr reference operator[](size_type idx) { return buffer_[idx]; }

        constexpr const_reference operator[](size_type idx) const noexcept { return buffer_[idx]; }

        constexpr pointer data() { return static_cast<pointer>(buffer_); }

        constexpr const_pointer data() const { return static_cast<const_pointer>(buffer_); }

        constexpr reference at(size_type idx) {
            if (idx >= size_) {
                throw std::out_of_range("out of bound");
            }
            return buffer_[idx];
        }

        constexpr const_reference at(size_type idx) const {
            if (idx >= size_) {
                throw std::out_of_range("out of bound");
            }
            return buffer_[idx];
        }

        constexpr reference front() noexcept { return buffer_[static_cast<size_type>(0)]; }

        constexpr const_reference front() const noexcept { return buffer_[static_cast<size_type>(0)]; }

        constexpr reference back() noexcept { return buffer_[static_cast<size_type>(size_ - 1)]; }

        constexpr const_reference back() const noexcept { return buffer_[static_cast<size_type>(size_ - 1)]; }

        // iterators

        constexpr iterator begin() noexcept { return iterator(data()); }

        constexpr const_iterator begin() const noexcept { return const_iterator(data()); }

        constexpr iterator end() noexcept { return iterator(data() + size_); }

        constexpr const_iterator end() const noexcept { return const_iterator(data() + size_); }

        constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

        constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

        constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

        constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

        constexpr const_iterator cbegin() const noexcept { return const_iterator(data()); }

        constexpr const_iterator cend() const noexcept { return const_iterator(data() + size_); }

        constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

        constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

        // capacity

        constexpr size_type size() const noexcept { return size_; }

        constexpr bool empty() const noexcept { return size() == 0; }

        // operations

        constexpr void fill(const value_type &val) { std::fill(begin(), end(), val); }

        constexpr void swap(array &other) { std::swap_ranges(begin(), end(), other.begin()); }

        // print

        friend std::ostream &operator<<(std::ostream &os, const array &arr) {
            std::for_each(arr.begin(), arr.end(), [&os](const auto &val) { os << val << ' '; });
            return os;
        }

    private:
        constexpr value_type *allocate(size_type sz) {
            return new value_type[sz];
        }

        constexpr void deallocate(value_type *buffer) {
            delete[] buffer;
        }

        size_t size_;
        value_type *buffer_;
    };

    // comparisons

    template<class T>
    bool operator==(const array<T> &lhs, const array<T> &rhs) {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
}
