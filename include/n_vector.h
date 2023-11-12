#pragma once

#include <n_utils.h>
#include <algorithm>

namespace naive {

    template<class T>
    class vector {
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

        constexpr vector() : size_(naive::utils::to<size_type>(0)), capacity_(naive::utils::to<size_type>(0)) {}

        constexpr explicit vector(size_type size) : size_(size), capacity_(size_), buffer_(allocate(size_)) {}

        constexpr vector(size_type size, const value_type val) :
                size_(size), capacity_(size_), buffer_(allocate(size_)) {
            std::fill(begin(), end(), val);
        }

        constexpr vector(std::initializer_list<value_type> il) :
                size_(il.size()), capacity_(il.size()), buffer_(allocate(size_)) {
            std::copy(il.begin(), il.end(), begin());
        }

        constexpr vector(const vector &other) : size_(other.size_), capacity_(other.capacity_) {
            auto new_buffer = allocate(capacity_);
            std::copy(other.buffer_, other.buffer_ + other.size_, new_buffer);
            buffer_ = new_buffer;
        }

        constexpr vector &operator=(const vector &other) {
            // TODO: if other.size_ == size_
            // copy and swap idiom
            auto copy = other;
            std::swap(copy, *this);
            return *this;
        }

        constexpr vector(vector &&other) noexcept: size_(other.size_), capacity_(other.capacity_),
                                                   buffer_(other.buffer_) {
            other.size_ = naive::utils::to<size_type>(0);
            other.capacity_ = naive::utils::to<size_type>(0);
            other.buffer_ = nullptr;
        }

        constexpr vector &operator=(vector &&other) noexcept {
            deallocate(buffer_);

            std::swap(size_, other.size_);
            std::swap(capacity_, other.capacity_);
            std::swap(buffer_, other.buffer_);

            other.size_ = naive::utils::to<size_type>(0);
            other.capacity_ = naive::utils::to<size_type>(0);
            other.buffer_ = nullptr;

            return *this;
        }

        constexpr ~vector() {
            deallocate(buffer_);
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

        constexpr size_type capacity() const noexcept { return capacity_; }

        constexpr bool empty() const noexcept { return size() == naive::utils::to<size_type>(0); }

    private:
        constexpr value_type *allocate(size_type sz) {
            return new value_type[sz];
        }

        constexpr void deallocate(value_type *buffer) {
            delete[] buffer;
        }

        size_type size_;
        size_type capacity_;
        value_type *buffer_;
    };

    // print

    template<class T>
    std::ostream &operator<<(std::ostream &os, const vector<T> &arr) {
        std::for_each(arr.begin(), arr.end(), [&os](const auto &val) { os << val << ' '; });
        return os;
    }
}