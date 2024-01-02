#include <n_allocator.h>

namespace naive {

    template<class T, class Allocator = naive::allocator<T>>
    class array_raw_buffer {
    protected:
        using value_type = Allocator::value_type;
        using size_type = Allocator::size_type;
        using pointer = Allocator::pointer;

        Allocator alloc_;
        size_type size_ = 0;
        pointer buffer_ = nullptr;

        constexpr array_raw_buffer() = default;

        constexpr array_raw_buffer(size_type size) : size_(size), buffer_(alloc_.allocate(size)) {}

        constexpr array_raw_buffer(size_type size, const Allocator &alloc) : alloc_(alloc), size_(size),
                                                                             buffer_(alloc_.allocate(size)) {}

        constexpr array_raw_buffer(array_raw_buffer &&other) noexcept: size_(other.size_), buffer_(other.buffer_) {
            other.size_ = 0;
            other.buffer_ = nullptr;
        }

        constexpr array_raw_buffer &operator=(array_raw_buffer &&other) noexcept {
            // intentionally left check this == &other
            std::swap(size_, other.size_);
            std::swap(buffer_, other.buffer_);
            return *this;
        }

        constexpr array_raw_buffer(const array_raw_buffer &) = delete;

        constexpr array_raw_buffer &operator=(const array_raw_buffer &) = delete;

        constexpr ~array_raw_buffer() {
            for (size_type i = 0; i < size_; ++i) {
                alloc_.destroy(buffer_ + i);
            }
            alloc_.deallocate(buffer_, size_);
        }
    };
}