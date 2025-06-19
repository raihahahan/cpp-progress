#include <algorithm>     // std::copy, std::distance
#include <iterator>      // std::iterator_traits, std::input_iterator, etc.
#include <cstddef>       // ptrdiff_t
#include <concepts>      // C++20 concepts
#include <iostream>      // std::ostream
#include "iterators.hpp"
#pragma once

namespace mystd {
    template <typename ElemTy>
    class SimpleVector {
    private:
        ElemTy* m_buffer;
        size_t m_size;

    public:
        // constructors
        SimpleVector() : m_buffer{nullptr}, m_size{0} {}

         SimpleVector(std::initializer_list<ElemTy> init) : m_size{init.size()} {
            m_buffer = new ElemTy[m_size];
            std::copy(init.begin(), init.end(), m_buffer);
        }

        // copy constructor
        SimpleVector(const SimpleVector& other) : m_size{other.m_size} {
            m_buffer = new ElemTy[m_size];
            for (size_t i = 0; i < m_size; ++i) {
                m_buffer = other.m_buffer[i];
            }
        }
        
        // copy-assignment
        SimpleVector& operator=(const SimpleVector& other) {
            SimpleVector copy{other};
            this->swap(copy);
            return *this;
        }

        // move constructor
        SimpleVector(SimpleVector&& other) noexcept : m_buffer{other.m_buffer}, m_size{other.m_size} {
            other.m_buffer = nullptr;
            other.m_size = 0;
        }

        // move-assignment
        SimpleVector& operator=(SimpleVector&& other) {
            auto moved = SimpleVector{std::move(other)};
            this->swap(moved);
            return *this;
        }

        // destructor
        ~SimpleVector() {
            delete[] m_buffer;
        }

        // alternative: rule of 4.5 by 
        // having by-value assignment operator instead of
        // both move and copy assignment
        /*
        SimpleVector& operator=(SimpleVector other) {
            this->swap(other);
            return *this;
        }
        */
        
        // accessors
        size_t size() const { return m_size; }
        ElemTy& operator[](size_t i) { return m_buffer[i]; }
        const ElemTy& operator[](size_t i) const { return m_buffer[i]; }

        // iterators
        ElemTy* begin() { return m_buffer; }
        ElemTy* end() { return m_buffer + m_size; }
        const ElemTy* begin() const { return m_buffer; }
        const ElemTy* end() const { return m_buffer + m_size; }
        const ElemTy* cbegin() const { return m_buffer; }
        const ElemTy* cend() const { return m_buffer + m_size; }

        mystd::RevIter<ElemTy*> rbegin() { return {end()}; }
        mystd::RevIter<ElemTy*> rend() { return {begin()}; }
        mystd::RevIter<const ElemTy*> rbegin() const { return {end()}; }
        mystd::RevIter<const ElemTy*> rend() const { return {begin()}; }
        mystd::RevIter<const ElemTy*> crbegin() const { return {end()}; }
        mystd::RevIter<const ElemTy*> crend() const { return {begin()}; }

        // methods
        void swap(SimpleVector& other) {
            std::swap(m_buffer, other.m_buffer);
            std::swap(m_size, other.m_size);
        }

        friend void swap(SimpleVector& a, SimpleVector& b) {
            a.swap(b);
        }

        void push_back(ElemTy val) {
            // param is passed by value
            // to support both lvalues and rvalues efficiently
            // 1. lvalue: copy into parameter then move to buffer
            // 2. rvalue: move into parameter, then move again
            // 3. prvalue: constructed in-place, then moved into buffer
            auto new_buffer = make_new_buffer(m_size + 1);
            new_buffer[m_size] = std::move(val);
            delete[] m_buffer;
            m_buffer = new_buffer;
            ++m_size;
        }

        void push_front(const ElemTy& val) {
            // TODO
            val;
        }

        ElemTy pop_back() {
            assert(m_size > 0);
            auto new_buffer = make_new_buffer(m_size - 1);

            ElemTy last_elem = std::move(m_buffer[m_size - 1]);
            --m_size;

            delete[] m_buffer;
            m_buffer = new_buffer;

            return last_elem;
        }

        ElemTy pop_front() {
            // TODO
            return nullptr;
        }

        mystd::BackIns<SimpleVector> back_inserter() {
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

        // non-member methods
        friend std::ostream& operator<<(std::ostream& os, const SimpleVector& v) {
            os << "[";
            for (size_t i = 0; i < v.size(); ++i) {
                os << v[i];
                if (i + 1 < v.size()) os << ", ";
            }
            os << "]";
            return os;
        }
    
    private:
        ElemTy* make_new_buffer(size_t new_size) {
            ElemTy* new_buffer = new ElemTy[new_size];
            for (size_t i = 0; i < std::min(new_size, m_size); ++i) {
                new_buffer[i] = std::move(m_buffer[i]);
            }

            return new_buffer;
        }
    };


}
