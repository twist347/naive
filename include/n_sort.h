#pragma once

#include <functional>

namespace naive {
    template<class Iter, class Comparator = std::less<typename std::iterator_traits<Iter>::value_type>>
    constexpr auto bubble_sort(Iter first, Iter last, Comparator cmp = {}) -> void {
        bool swapped;
        do {
            swapped = false;
            for (auto it = first, end_it = std::prev(last); it != end_it; ++it) {
                if (cmp(*(it + 1), *it)) {
                    std::iter_swap(it, it + 1);
                    swapped = true;
                }
            }
        } while (swapped);
    }

    template<class Iter, class Comparator = std::less<typename std::iterator_traits<Iter>::value_type>>
    constexpr void selection_sort(Iter first, Iter last, Comparator cmp = {}) {
        for (auto it_i = first, end_it = std::prev(last); it_i != end_it; std::advance(it_i, 1)) {
            auto min_el_it = it_i;
            for (auto it_j = std::next(it_i); it_j != last; std::advance(it_j, 1)) {
                if (cmp(*it_j, *min_el_it)) {
                    min_el_it = it_j;
                }
            }
            if (min_el_it != it_i) {
                std::iter_swap(it_i, min_el_it);
            }
        }
    }

    template<class Iter, class Comparator = std::less<typename std::iterator_traits<Iter>::value_type>>
    constexpr void insertion_sort(Iter first, Iter last, Comparator cmp = {}) {
        for (auto it_i = std::next(first); it_i != last; std::advance(it_i, 1)) {
            auto key = *it_i;
            auto it_j = std::prev(it_i);
            while (it_j >= first && cmp(key, *it_j)) {
                *(std::next(it_j)) = *it_j;
                std::advance(it_j, -1);
            }
            *(std::next(it_j)) = key;
        }
    }

    template<class Iter>
    constexpr void counting_sort(Iter first, Iter last) {
        auto max_el = *std::max_element(first, last);
        auto min_el = *std::min_element(first, last);

        auto offset = (min_el < 0) ? -min_el : 0;

        std::vector<size_t> count(max_el - min_el + 1 + offset, 0);
        for (auto it = first; it != last; std::advance(it, 1)) {
            ++count[*it + offset];
        }
        auto it = first;
        for (size_t i = min_el + offset; i <= max_el + offset; ++i) {
            while (count[i] != 0) {
                *it = i - offset;
                ++it;
                --count[i];
            }
        }
    }
}