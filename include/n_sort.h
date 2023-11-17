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
}