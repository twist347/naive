#pragma once

#include <n_utils.h>
#include <n_allocator.h>
#include <algorithm>

namespace naive {

    template<class T, class Alloc = naive::allocator<T>>
    class vector {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = value_type *;
        using const_pointer = const pointer;
        using iterator = pointer;
        using const_iterator = const pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using difference_type = std::ptrdiff_t;

        constexpr vector() : size_(naive::utils::to<size_type>(0)),
                             capacity_(naive::utils::to<size_type>(0)),
                             buffer_(call_alloc_and_construct(naive::utils::to<size_type>(0))) {}

        constexpr explicit vector(size_type size) :
                size_(size), capacity_(size_), buffer_(call_alloc_and_construct(size_)) {}

        constexpr vector(size_type size, const_reference val) :
                size_(size), capacity_(size_), buffer_(alloc.allocate(size_)) {
            for (size_type i = 0; i < size_; ++i) {
                alloc.construct(buffer_ + i, val);
            }
        }

        constexpr vector(std::initializer_list<value_type> il) :
                size_(il.size()), capacity_(il.size()), buffer_(alloc.allocate(size_)) {
            auto it = il.begin();
            for (size_type i = 0; i < size_; ++i) {
                alloc.construct(buffer_ + i, *(it++));
            }
        }

        constexpr vector(const vector &other) : size_(other.size_), capacity_(other.capacity_) {
            auto new_buffer = alloc.allocate(capacity_);
            for (size_type i = 0; i < size_; ++i) {
                alloc.construct(new_buffer + i, other.buffer_[i]);
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
            call_destruct_and_dealloc(buffer_, capacity_);
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
                alloc.destruct(buffer_ + i);
            }
            alloc.deallocate(buffer_, capacity_);
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

        constexpr void reserve(size_type new_cap) {
            if (new_cap <= capacity_) {
                return;
            }
            auto new_buffer = alloc.allocate(new_cap);
            for (size_type i = 0; i < size_; ++i) {
                alloc.construct(new_buffer + i, std::move(buffer_[i]));
                alloc.destruct(buffer_ + i);
            }
            deallocate(buffer_, size_);
            capacity_ = new_cap;
            buffer_ = new_buffer;
        }

        constexpr void shrink_to_fit() {
            if (capacity_ == size_) {
                return;
            }
            auto new_buffer = alloc.allocate(size_);
            for (size_type i = 0; i < size_; ++i) {
                alloc.construct(new_buffer + i, std::move(buffer_[i]));
                alloc.destruct(buffer_ + i);
            }
            alloc.deallocate(buffer_, capacity_);
            buffer_ = new_buffer;
            capacity_ = size_;
        }

        // modifiers

        constexpr void resize(size_type new_size) {
            if (size_ == new_size) {
                return;
            } else if (new_size > size_) {
                auto new_buffer = alloc.allocate(new_size);
                for (size_type i = 0; i < size_; ++i) {
                    alloc.construct(new_buffer + i, std::move(buffer_[i]));
                    alloc.destruct(buffer_ + i);
                }
                for (size_type i = size_; i < new_size; ++i) {
                    alloc.construct(new_buffer + i);
                }
                alloc.deallocate(buffer_, capacity_);
                size_ = new_size;
                capacity_ = new_size;
                buffer_ = new_buffer;
            } else {
                for (size_type i = new_size; i < size_; ++i) {
                    alloc.destruct(buffer_ + i);
                }
                size_ = new_size;
            }
        }

    private:

        template<class ... Args>
        pointer call_alloc_and_construct(size_type n_obj, Args &&... args) {
            auto ptr = alloc.allocate(n_obj);
            for (size_type i = 0; i < n_obj; ++i) {
                alloc.construct(ptr + i, std::forward<Args>(args)...);
            }
            return ptr;
        }

        void call_destruct_and_dealloc(pointer ptr, size_type n_obj) {
            for (size_type i = 0; i < n_obj; ++i) {
                alloc.destruct(ptr + i);
            }
            alloc.deallocate(ptr, n_obj);
        }

//        pointer allocate(size_type size) {
//            return size == 0 ? nullptr : static_cast<pointer>(::operator new(size * sizeof(value_type)));
//        }
//
//        constexpr void deallocate(pointer ptr, size_type size) {
//            operator delete[](ptr);
//        }
//
//        template<class ... Args>
//        constexpr void construct(pointer ptr, Args &&... args) {
//            new(ptr) value_type(std::forward<Args>(args)...);
//        }
//
//        constexpr void destruct(pointer ptr) {
//            ptr->~value_type();
//        }
//
//        template<class FwdIter>
//        void destruct(FwdIter first, FwdIter last) noexcept {
//            while (first++ != last) {
//                destruct(&*first);
//            }
//        }

        Alloc alloc;
        size_type size_;
        size_type capacity_;
        pointer buffer_;
    };

    // print

    template<class T>
    std::ostream &operator<<(std::ostream &os, const vector<T> &arr) {
        std::for_each(arr.begin(), arr.end(), [&os](const auto &val) { os << val << ' '; });
        return os;
    }
}