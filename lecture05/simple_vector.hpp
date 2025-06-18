#include <algorithm>     // std::copy, std::distance
#include <iterator>      // std::iterator_traits, std::input_iterator, etc.
#include <cstddef>       // ptrdiff_t
#include <concepts>      // C++20 concepts
#include <iostream>      // std::ostream
#include "iterators.hpp"

template <typename ElemTy>
class SimpleVector {
private:
    ElemTy* m_buffer;
    size_t m_size;

public:
    #pragma region Constructors
    SimpleVector() : m_buffer{nullptr}, m_size{0} {}

    SimpleVector(const SimpleVector& other) : m_size{other.m_size} {
        m_buffer = new ElemTy[m_size];
        for (size_t i = 0; i < m_size; ++i) {
            m_buffer = other.m_buffer[i];
        }
    }

    SimpleVector& operator=(const SimpleVector& other) {
        SimpleVector copy{other};
        this->swap(copy);
        return *this;
    }

    SimpleVector(std::initializer_list<ElemTy> init) : m_size{init.size()} {
        m_buffer = new ElemTy[m_size];
        std::copy(init.begin(), init.end(), m_buffer);
    }

    ~SimpleVector() {
        delete[] m_buffer;
    }
    
    #pragma region Accessors
    size_t size() const { return m_size; }
    ElemTy& operator[](size_t i) { return m_buffer[i]; }
    const ElemTy& operator[](size_t i) const { return m_buffer[i]; }

    #pragma region Normal Iterator
    ElemTy* begin() { return m_buffer; }
    ElemTy* end() { return m_buffer + m_size; }
    const ElemTy* begin() const { return m_buffer; }
    const ElemTy* end() const { return m_buffer + m_size; }
    const ElemTy* cbegin() const { return m_buffer; }
    const ElemTy* cend() const { return m_buffer + m_size; }

    #pragma region Reverse Iterator
    lecture05::iterators::RevIter<ElemTy*> rbegin() { return {end()}; }
    lecture05::iterators::RevIter<ElemTy*> rend() { return {begin()}; }
    lecture05::iterators::RevIter<const ElemTy*> rbegin() const { return {end()}; }
    lecture05::iterators::RevIter<const ElemTy*> rend() const { return {begin()}; }
    lecture05::iterators::RevIter<const ElemTy*> crbegin() const { return {end()}; }
    lecture05::iterators::RevIter<const ElemTy*> crend() const { return {begin()}; }

    #pragma region Methods
    void swap(SimpleVector& other) {
        std::swap(m_buffer, other.m_buffer);
        std::swap(m_size, other.m_size);
    }

    friend void swap(SimpleVector& a, SimpleVector& b) {
        a.swap(b);
    }

    void push_back(const ElemTy& val) {
        ElemTy* new_buffer = new ElemTy[m_size + 1];
        std::copy(m_buffer, m_buffer + m_size, new_buffer);
        new_buffer[m_size] = val;
        delete[] m_buffer;
        m_buffer = new_buffer;
        m_size++;
    }

    void push_front(const ElemTy& val) {
        // TODO
        val;
    }

    ElemTy pop_back() {
        // TODO
        return nullptr;
    }

    ElemTy pop_front() {
        // TODO
        return nullptr;
    }

    lecture05::iterators::BackIns<SimpleVector> back_inserter() {
        return {this};
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

    #pragma region Operators
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
