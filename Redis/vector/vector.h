#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <iterator>

namespace myl {

    template<typename T>
    class vector
    {
    public:
        vector();
        vector(int colum,const T& value);
        vector(int col);
        vector(const vector & other);
        vector(vector && other) noexcept;
        vector & operator=(const vector & other);
        vector & operator=(vector && other) noexcept;
        T& operator[] (int index);
        const T& operator[] (int index) const;
        ~vector();
        vector(const std::initializer_list<T>& elems);
    public:
        void push_back(const T& value);
        void pop_back();
        int size() const;
        int capacity() const;
        void shrink_to_fit();
    public:
        class iterator : public std::iterator<std::random_access_iterator_tag,T>
        {
        public:
            iterator(T * p = nullptr);
            iterator(const iterator& it);
            iterator & operator= (const iterator& it);
            iterator operator+(int add);
            iterator operator-(int sub);
            iterator& operator+=(int add);
            iterator& operator-=(int sub);
            T& operator++();
            T& operator++(int);
            T& operator--();
            T& operator--(int);
            bool operator!=(const iterator& other) const;
            bool operator==(const iterator& other) const;
            T& operator*() const;
        private:
            T * iter;
        };

        iterator begin();
        iterator end();
        void insert(iterator& iter,const T& value);
        void erease(iterator& iter);
        void clear();
        const T * data() const { return arr; }

    private:
        T * arr;
        int _size;
        int _capacity;
    };

}

#include "vector.hpp"

#endif