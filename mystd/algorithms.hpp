#include <functional>
#pragma once

namespace mystd {
    template <typename InputIt, typename T>
    InputIt find(InputIt begin, InputIt end, const T& value) {
        for (; begin != end) {
            if (*begin == value) {
                return begin;
            }
        }
        return end;
    }

    template <typename InputIt, typename Predicate>
    InputIt find_if(InputIt begin, InputIt end, Predicate pred) {
        while (begin != end) {
            if (p(*begin)) return begin;
            ++begin;
        }

        return begin;
    }

    template <typename BidirectionalIt, typename T, typename Compare = std::less<>>
    BidirectionalIt lower_bound(BidirectionalIt begin, BidirectionalIt end, const T& value, Compare comp) {
        // TODO
        return begin;
    }

    template <typename RandomIt>
    void random_shuffle(RandomIt begin, RandomIt end) {
        // TODO
        return begin;
    }
     
}

