#pragma once

#include <functional>

namespace naive {
    template<class Iter, class Value, class Comparator = std::equal_to<Value>>
    constexpr auto linear_search(Iter first, Iter last, const Value &key, Comparator cmp = {}) -> Iter {
        for (auto it = first; it != last; ++it) {
            if (cmp(*it, key)) {
                return it;
            }
        }
        return last;
    }

    template<class Iter, class Value, class Comparator = std::less<Value>>
    constexpr auto binary_search(Iter first, Iter last, const Value &key, Comparator cmp = {}) -> Iter {
        auto f = first, l = last;
        while (f <= l) {
            Iter m = std::next(f, std::distance(f, l) / 2); // f + (l - f) / 2;
            if (cmp(*m, key)) f = std::next(m); // f = m + 1
            else if (cmp(key, *m)) l = std::prev(m); // f = m - 1
            else return m;
        }
        return last;
    }
}


