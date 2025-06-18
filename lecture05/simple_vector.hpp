#include <algorithm>     // std::copy, std::distance
#include <iterator>      // std::iterator_traits, std::input_iterator, etc.
#include <cstddef>       // ptrdiff_t
#include <concepts>      // C++20 concepts
#include <iostream>      // std::ostream
#include "iterators.hpp"

template <typename ElemTy>
class SimpleVector {
private:
    ElemTy* m_buffer = nullptr;
    size_t m_size = 0;

public:
    SimpleVector() = default;

    SimpleVector(std::initializer_list<ElemTy> init) {
        m_size = init.size();
        m_buffer = new ElemTy[m_size];
        std::copy(init.begin(), init.end(), m_buffer);
    }

    ~SimpleVector() {
        delete[] m_buffer;
    }

    size_t size() const { return m_size; }

    ElemTy& operator[](size_t i) { return m_buffer[i]; }
    const ElemTy& operator[](size_t i) const { return m_buffer[i]; }

    ElemTy* begin() { return m_buffer; }
    ElemTy* end() { return m_buffer + m_size; }
    const ElemTy* begin() const { return m_buffer; }
    const ElemTy* end() const { return m_buffer + m_size; }
    const ElemTy* cbegin() const { return m_buffer; }
    const ElemTy* cend() const { return m_buffer + m_size; }

    // --- Reverse Iterator Support ---
    lecture05::iterators::RevIter<ElemTy*> rbegin() { return {end()}; }
    lecture05::iterators::RevIter<ElemTy*> rend() { return {begin()}; }
    lecture05::iterators::RevIter<const ElemTy*> rbegin() const { return {end()}; }
    lecture05::iterators::RevIter<const ElemTy*> rend() const { return {begin()}; }
    lecture05::iterators::RevIter<const ElemTy*> crbegin() const { return {end()}; }
    lecture05::iterators::RevIter<const ElemTy*> crend() const { return {begin()}; }

    // --- insert_back using concepts and traits ---
    void push_back(const ElemTy& val) {
        ElemTy* new_buffer = new ElemTy[m_size + 1];
        std::copy(m_buffer, m_buffer + m_size, new_buffer);
        new_buffer[m_size] = val;
        delete[] m_buffer;
        m_buffer = new_buffer;
        m_size++;
    }

    lecture05::iterators::BackIns<SimpleVector> back_inserter() {
        return {this};
    }
    
    template <typename InputIt>
    // requires std::input_iterator<InputIt>
    void insert_back(InputIt begin, InputIt end) {
        std::copy(begin, end, back_inserter());
    }

    template <typename ForwardIt>
    requires std::forward_iterator<ForwardIt>
    void insert_back(ForwardIt begin, ForwardIt end) {
        size_t num_elems = static_cast<size_t>(std::distance(begin, end));
        ElemTy* new_buffer = new ElemTy[m_size + num_elems];

        std::copy(m_buffer, m_buffer + m_size, new_buffer);
        std::copy(begin, end, new_buffer + m_size);

        delete[] m_buffer;
        m_buffer = new_buffer;
        m_size += num_elems;
    }

    friend std::ostream& operator<<(std::ostream& os, const SimpleVector& v) {
        os << "[";
        for (size_t i = 0; i < v.size(); ++i) {
            os << v[i];
            if (i + 1 < v.size()) os << ", ";
        }
        os << "]";
        return os;
    }
};
