#ifndef SET_H
#define SET_H

#include "tree.h"

#include <initializer_list>

namespace myl {
    template <typename T>
    class set
    {
    public:
        set() = default;
        set(const set&);
        set(set&&);
        set& operator=(const set&);
        set& operator=(set&&);
        set(const std::initializer_list<T>&);
        set& operator=(const std::initializer_list<T>&);
    public:
        const T& find(const T&) const;
        void insert(const T&);
        void erase(const T&);
        void clear();
        size_t size() const;
        void copy_str(String &) ;
        bool is_empty();
    private:
        myl::AVLtree<T> head;
        size_t _size;
    };
}

#include "set.hpp"

#endif