#pragma once

#include <vector>
#include <n_vector.h>

namespace naive {
    // use vector instead of std::deque<T> like in stl

    template<class T, class Container = std::vector<T>>
    class stack {
    public:
        using container_type = Container;
        using value_type = Container::value_type;
        using size_type = Container::size_type;
        using reference = Container::reference;
        using const_reference = Container::const_reference;

        stack() : container_() {}

        explicit stack(const Container &container) : container_(container) {}

        explicit stack(Container &&container) : container_(std::move(container)) {}


        // element access

        constexpr reference top() {
            return container_.back();
        }

        constexpr const_reference top() const {
            return container_.back();
        }

        // capacity

        constexpr bool empty() const {
            return container_.empty();
        }

        constexpr size_type size() const {
            return container_.size();
        }

        // modifiers

        constexpr void push(const value_type &value) {
            container_.push_back(value);
        }

        constexpr void push(value_type &&value) {
            container_.push_back(std::move(value));
        }

        template<class ... Args>
        constexpr decltype(auto) emplace(Args &&... args) {
            return container_.emplace_back(std::forward<Args>(args)...);
        }

        constexpr void pop() {
            container_.pop_back();
        }

    private:
        Container container_;
    };
}