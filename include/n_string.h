#pragma once

#include <n_allocator.h>
#include <algorithm>
#include <cstring>

namespace naive {
    template<class CharT = char, class Allocator = naive::allocator<CharT>>
    class string {
    public:
        using value_type = CharT;
        using allocator_type = Allocator;
        using size_type = Allocator::size_type;
        using difference_type = Allocator::difference_type;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = Allocator::pointer;
        using const_pointer = Allocator::const_pointer;
        using iterator = value_type *;
        using const_iterator = const value_type *;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        explicit constexpr string(const Allocator &alloc = Allocator()) : alloc_(alloc),
                                                                          size_(static_cast<size_type>(0)),
                                                                          capacity_(min_capacity),
                                                                          buffer_(alloc_.allocate(capacity_)) {
            buffer_[0] = '\0';
        }

        constexpr string(size_t count, CharT ch) : size_(count),
                                                   capacity_(size_ < min_capacity ? min_capacity : size_ + 1),
                                                   buffer_(alloc_.allocate(capacity_)) {
            std::memset(begin(), ch, size() * sizeof(CharT));
            buffer_[size_] = '\0';
            assert(size() < capacity());
        }

        constexpr string(const CharT *c_str, size_type count) : size_(count),
                                                                capacity_(size_ < min_capacity
                                                                          ? min_capacity
                                                                          : size_ + 1),
                                                                buffer_(alloc_.allocate(capacity_)) {
            std::memcpy(begin(), c_str, size() * sizeof(CharT));
            buffer_[size_] = '\0';
        }

        constexpr string(const CharT *c_str) : string(c_str, std::strlen(c_str)) {}

        constexpr string(const string &other) : alloc_(other.alloc_), size_(other.size_), capacity_(other.capacity_),
                                                buffer_(alloc_.allocate(capacity_)) {
            std::memcpy(begin(), other.begin(), size() * sizeof(CharT));
            buffer_[size_] = '\0';
        }

        constexpr string &operator=(const string &other) {
            if (this == &other) {
                return *this;
            }
            if (alloc_ != other.alloc_) {
                alloc_ = other.alloc_;
            }
            if (size() != other.size()) {
                alloc_.deallocate(buffer_, capacity());
                size_ = other.size();
                buffer_ = alloc_.allocate(size());
            }
            std::memcpy(begin(), other.begin(), size() * sizeof(CharT));
            return *this;
        }

        constexpr string(string &&other) noexcept: alloc_(std::move(other.alloc_)),
                                                   size_(std::exchange(other.size_, static_cast<size_type>(0))),
                                                   capacity_(std::exchange(other.capacity_, static_cast<size_type>(0))),
                                                   buffer_(std::exchange(other.buffer_, nullptr)) {}

        constexpr string &operator=(string &&other) noexcept {
            if (this == &other) {
                return *this;
            }

            alloc_.deallocate(buffer_, capacity_);

            alloc_ = std::move(other.alloc_);
            size_ = std::exchange(other.size_, static_cast<size_type>(0));
            capacity_ = std::exchange(other.capacity_, static_cast<size_type>(0));
            buffer_ = std::exchange(other.buffer_, nullptr);
            return *this;
        }

        constexpr ~string() {
            alloc_.deallocate(buffer_, capacity_);
        }

        constexpr allocator_type get_allocator() const noexcept {
            return alloc_;
        }

        // access

        constexpr reference operator[](size_type idx) { return begin()[idx]; }

        constexpr const_reference operator[](size_type idx) const { return begin()[idx]; }

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

        constexpr const char *c_str() const noexcept { return data(); }

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

        constexpr size_type length() const noexcept { return size(); }

        constexpr size_type capacity() const noexcept { return capacity_; }

        constexpr bool empty() const noexcept { return size() == static_cast<size_type>(0); }

        constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

        constexpr void reserve(size_type new_cap) {
            assert(size_ < capacity_);
            if (new_cap <= capacity_) {
                return;
            }
            new_cap = new_cap < min_capacity ? min_capacity : new_cap;
            auto new_buffer = alloc_.allocate(new_cap);
            std::memcpy(new_buffer, begin(), size() * sizeof(CharT));
            new_buffer[size_] = '\0';
            alloc_.deallocate(buffer_, capacity_);
            buffer_ = new_buffer;
            capacity_ = new_cap;
            assert(size_ < capacity_);
        }

        constexpr void shrink_to_fit() {
            assert(size_ < capacity_);
            if (capacity_ == size_ + 1 || capacity_ == min_capacity) {
                return;
            }
            // TODO: maybe realloc
            auto new_buffer = alloc_.allocate(size_ + 1);
            std::memcpy(new_buffer, begin(), size() * sizeof(CharT));
            new_buffer[size_] = '\0';
            alloc_.deallocate(buffer_, capacity_);
            capacity_ = size_ < min_capacity ? min_capacity : size_ + 1;
            buffer_ = new_buffer;
            assert(size_ < capacity_);
        }

        // modifiers

        constexpr void clear() noexcept {
            assert(size_ < capacity_);
            size_ = 0;
            buffer_[0] = '\0';
        }

        constexpr void resize(size_type new_size) {
            assert(size_ < capacity_);
            if (new_size == size_) {
                return;
            }
            if (new_size < size_) {
                buffer_[new_size] = '\0';
                size_ = new_size;
            } else {
                if (new_size >= capacity_) {
                    reserve(2 * capacity_ > new_size ? 2 * capacity_: new_size + 1);
                }
                for (size_type i = size_; i < new_size; ++i) {
                    buffer_[i] = '\0';
                }
                size_ = new_size;
            }
            assert(size_ < capacity_);
        }

    private:
        constexpr static size_type min_capacity = 8;

        Allocator alloc_;
        size_type size_;
        size_type capacity_;
        pointer buffer_;
    };

    // print

    template<class T>
    std::ostream &operator<<(std::ostream &os, const naive::string<T> &str) {
        std::for_each(str.begin(), str.end(), [&os](auto ch) { os << ch; });
        return os;
    }

    template<class T>
    bool operator==(const naive::string<T> &lhs, const naive::string<T> &rhs) {
        if (lhs.size() != rhs.size()) {
            return false;
        }
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template<class T>
    bool operator!=(const naive::string<T> &lhs, const naive::string<T> &rhs) {
        return !(lhs == rhs);
    }
}
