#pragma once

#include <n_utils.h>
#include <n_allocator.h>
#include <algorithm>
#include <stdexcept>

namespace naive {

    template<class T, class Allocator = naive::allocator<T>>
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

        // ctors and dtor

        constexpr vector() : size_(naive::utils::to<size_type>(0)),
                             capacity_(naive::utils::to<size_type>(0)),
                             buffer_(alloc_and_construct(naive::utils::to<size_type>(0))) {}

        constexpr explicit vector(size_type size) :
                size_(size), capacity_(size_), buffer_(alloc_and_construct(size_)) {}

        constexpr vector(size_type size, const value_type &val) :
                size_(size), capacity_(size_), buffer_(alloc_.allocate(size_)) {
            for (size_type i = 0; i < size_; ++i) {
                alloc_.construct(buffer_ + i, val);
            }
        }

        constexpr vector(std::initializer_list<value_type> il) :
                size_(il.size()), capacity_(il.size()), buffer_(alloc_.allocate(size_)) {
            auto it = il.begin();
            for (size_type i = 0; i < size_; ++i) {
                alloc_.construct(buffer_ + i, *(it++));
            }
        }

        constexpr vector(const vector &other) : size_(other.size_), capacity_(other.capacity_) {
            auto new_buffer = alloc_.allocate(capacity_);
            for (size_type i = 0; i < size_; ++i) {
                alloc_.construct(new_buffer + i, other.buffer_[i]);
            }
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
            if (this == &other) return *this;
            destruct_and_dealloc(buffer_, capacity_);
            std::swap(size_, other.size_);
            std::swap(capacity_, other.capacity_);
            std::swap(buffer_, other.buffer_);

            other.size_ = naive::utils::to<size_type>(0);
            other.capacity_ = naive::utils::to<size_type>(0);
            other.buffer_ = nullptr;

            return *this;
        }

        constexpr ~vector() {
            for (size_t i = 0; i < size_; ++i) {
                alloc_.destruct(buffer_ + i);
            }
            alloc_.deallocate(buffer_, capacity_);
        }

        // access

        constexpr reference operator[](size_type idx) { return buffer_[idx]; }

        constexpr const_reference operator[](size_type idx) const { return buffer_[idx]; }

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

        constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

        constexpr void reserve(size_type new_cap) {
            if (new_cap <= capacity_) {
                return;
            }
            auto new_buffer = alloc_.allocate(new_cap);
            for (size_type i = 0; i < size_; ++i) {
                alloc_.construct(new_buffer + i, std::move(buffer_[i]));
                alloc_.destruct(buffer_ + i);
            }
            alloc_.deallocate(buffer_, size_);
            capacity_ = new_cap;
            buffer_ = new_buffer;
        }

        constexpr void shrink_to_fit() {
            if (capacity_ == size_) {
                return;
            }
            auto new_buffer = alloc_.allocate(size_);
            for (size_type i = 0; i < size_; ++i) {
                alloc_.construct(new_buffer + i, std::move(buffer_[i]));
                alloc_.destruct(buffer_ + i);
            }
            alloc_.deallocate(buffer_, capacity_);
            buffer_ = new_buffer;
            capacity_ = size_;
        }

        // modifiers

        constexpr void clear() noexcept {
            for (size_type i = 0; i < size_; ++i) {
                alloc_.destruct(buffer_ + i);
            }
            size_ = 0;
        }

        constexpr iterator erase(const_iterator pos) {
            auto idx = std::distance(cbegin(), pos);
            for (size_type i = idx; i < size_ - 1; ++i) {
                buffer_[i] = std::move(buffer_[i + 1]);
            }
            alloc_.destruct(buffer_ + size_ - 1);
            --size_;
            return buffer_ + idx;
        }

        constexpr void pop_back() {
            erase(std::prev(end()));
        }

        constexpr void swap(vector &other) noexcept {
            std::swap(size_, other.size_);
            std::swap(capacity_, other.capacity_);
            std::swap(buffer_, other.buffer_);
        }

        // TODO erase(first, last)

        constexpr iterator insert(const_iterator pos, const value_type &val) {
            return insert_impl(pos, val);
        }

        constexpr iterator insert(const_iterator pos, value_type &&val) {
            return insert_impl(pos, std::forward<value_type>(val));
        }

        template<class ... Args>
        constexpr iterator emplace(const_iterator pos, Args &&... args) {
            value_type obj(std::forward<Args>(args)...);
            return insert_impl(pos, std::move(obj));
        }

        constexpr void push_back(const value_type &val) {
            push_back_impl(val);
        }

        constexpr void push_back(value_type &&val) {
            push_back_impl(std::forward<value_type>(val));
        }

        template<class ... Args>
        constexpr reference emplace_back(Args &&... args) {
            push_back_impl(std::forward<Args>(args)...);
            return back();
        }

        constexpr void resize(size_type new_size) {
            if (size_ == new_size) {
                return;
            } else if (new_size > size_) {
                auto new_buffer = alloc_.allocate(new_size);
                for (size_type i = 0; i < size_; ++i) {
                    alloc_.construct(new_buffer + i, std::move(buffer_[i]));
                    alloc_.destruct(buffer_ + i);
                }
                for (size_type i = size_; i < new_size; ++i) {
                    alloc_.construct(new_buffer + i);
                }
                alloc_.deallocate(buffer_, capacity_);
                size_ = new_size;
                capacity_ = new_size;
                buffer_ = new_buffer;
            } else {
                for (size_type i = new_size; i < size_; ++i) {
                    alloc_.destruct(buffer_ + i);
                }
                size_ = new_size;
            }
        }

    private:
        template<class ... Args>
        constexpr void push_back_impl(Args &&... args) {
            if (size_ == capacity_) {
                reserve(capacity_ == 0 ? 1 : capacity_ * 2);
            }
            alloc_.construct(buffer_ + size_, std::forward<Args>(args)...);
            ++size_;
        }

        template<class U>
        constexpr iterator insert_impl(const_iterator pos, U &&u) {
            auto idx_pos = std::distance(cbegin(), pos);
            if (size_ == capacity_) {
                // unnecessary actions. need to correct
                reserve(capacity_ == 0 ? 1 : capacity_ * 2);
            }
            if (size_ == 0) {
                alloc_.construct(buffer_, std::forward<U>(u));
                ++size_;
                return buffer_;
            }
            alloc_.construct(buffer_ + size_, std::move(buffer_[size_ - 1]));
            // can be assigned because the memory is the same
            for (size_type i = size_ - 1; i != idx_pos; --i) {
                buffer_[i] = std::move(buffer_[i - 1]);
            }
            buffer_[idx_pos] = std::forward<U>(u);
            ++size_;
            return buffer_ + idx_pos;
        }

        Allocator alloc_;
        size_type size_;
        size_type capacity_;
        pointer buffer_;

        using alloc_ptr = decltype(alloc_)::pointer;

        template<class ... Args>
        constexpr auto alloc_and_construct(size_type n_obj, Args &&... args) -> alloc_ptr {
            auto ptr = alloc_.allocate(n_obj);
            for (size_type i = 0; i < n_obj; ++i) {
                alloc_.construct(ptr + i, std::forward<Args>(args)...);
            }
            return ptr;
        }

        constexpr void destruct_and_dealloc(alloc_ptr ptr, size_type n_obj) {
            for (size_type i = 0; i < n_obj; ++i) {
                alloc_.destruct(ptr + i);
            }
            alloc_.deallocate(ptr, n_obj);
        }
    };

    // print

    template<class T>
    std::ostream &operator<<(std::ostream &os, const vector<T> &arr) {
        std::for_each(arr.begin(), arr.end(), [&os](const auto &val) { os << val << ' '; });
        return os;
    }
}