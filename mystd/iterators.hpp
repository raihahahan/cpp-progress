#include <iterator>
#include <concepts>
#include <algorithm>     // std::copy, std::distance
#include <iterator>      // std::iterator_traits, std::input_iterator, etc.
#include <cstddef>       // ptrdiff_t
#include <iostream>      // std::ostream
#pragma once


namespace mystd {
    template <typename T>
    struct InputIterator {
        using value_type = T;
        using different_type = std::ptrdiff_t;
        using reference = T&;
        using pointer = T*;
        using iterator_catgory = std::input_iterator_tag;

        T* i;

        // prefix ++it
        InputIterator& operator++() {
            ++i;
            return *this;
        }

        // postfix it++
        InputIterator operator++(int) {
            InputIterator temp = *this;
            ++i;
            return temp;
        }

        reference operator*() {
            return *i;
        }

        pointer operator->() {
            return i;
        }

        bool operator==(const InputIterator& other) {
            return i == other.i;
        }

        bool operator!=(const InputIterator& other) {
            return i != other.i;
        }
    };

    template <typename ElemType>
    struct NormalIterator {
        ElemType* m_buffer;
        size_t m_size;

        ElemType* begin() {
            return m_buffer;
        }

        ElemType* end() {
            return m_buffer + m_size;
        }

        const ElemType* begin() const {
            return m_buffer;
        }

        const ElemType* end() const {
            return m_buffer + m_size;
        }

        const ElemType* cbegin() const {
            return m_buffer;
        }

        const ElemType* cend() const {
            return m_buffer + m_size;
        }
    };

    template <typename Iter>
    struct RevIter {
        using Traits = std::iterator_traits<Iter>;
        using difference_type = typename Traits::difference_type;
        using value_type = typename Traits::value_type;
        using pointer = typename Traits::pointer;
        using reference = typename Traits::reference;
        using iterator_category = std::random_access_iterator_tag;

        Iter m_iter;

        reference operator*() const { return *(m_iter - 1); }
        pointer operator->() const { return m_iter - 1; }

        RevIter& operator++() { m_iter--; return *this; }
        RevIter& operator--() { m_iter++; return *this; }
        RevIter operator++(int) { return {m_iter--}; }
        RevIter operator--(int) { return {m_iter++}; }

        RevIter& operator+=(difference_type n) { m_iter -= n; return *this; }
        RevIter& operator-=(difference_type n) { m_iter += n; return *this; }

        RevIter operator+(difference_type n) const { return {m_iter - n}; }
        RevIter operator-(difference_type n) const { return {m_iter + n}; }

        difference_type operator-(RevIter other) const {
            return -(m_iter - other.m_iter);
        }

        auto operator<=>(const RevIter& o) const = default;
    };


    // --- Output Iterator: back_inserter ---
    template <typename Container>
    struct BackIns {
        Container* c;
        using iterator_category = std::output_iterator_tag;
        using difference_type = void;
        using value_type = void;
        using pointer = void;
        using reference = void;

        auto operator*() const { return *this; }
        auto operator++() { return *this; }
        auto operator++(int) { return *this; }

        template <typename T>
        BackIns& operator=(T&& v) {
            c->push_back(std::forward<T>(v));
            return *this;
        }
    };




}