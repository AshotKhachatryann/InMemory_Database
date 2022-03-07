#include "set.h"

template <typename T>
myl::set<T>::set(const set<T>& r)
{
    this->head = r.head;
    this->_size = r._size;
}

template <typename T>
myl::set<T>::set(set<T>&& r): head{ std::move(r.head) }, _size{r._size}
{}

template <typename T>
myl::set<T>& myl::set<T>::operator=(const set<T>& r)
{
    if(this == &r)
        return *this;
    this->head.deleter();
    this->head = r.head;
    this->_size = r._size;
    return *this;
}

template <typename T>
myl::set<T>& myl::set<T>::operator=(set<T>&& r)
{
    if(this == &r)
        return *this;
    this->head.deleter();
    this->head = std::move(r.head);
    this->_size = r._size;
    return *this;
}

template <typename T>
const T& myl::set<T>::find(const T& elem) const
{
    return head.find(elem);
}

template <typename T>
void myl::set<T>::insert(const T& elem) 
{
    head.insert(elem);
    ++_size;
}

template <typename T>
void myl::set<T>::erase(const T& elem) 
{
    head.erase(elem);
    --_size;
}

template <typename T>
void myl::set<T>::clear() 
{
    head.deleter();
    _size = 0;
}

template <typename T>
size_t myl::set<T>::size() const
{
    return _size;
}

template <typename T>
void myl::set<T>::copy_str(String& st) 
{
    this->head.inorder(st);
}

template<typename T>
bool myl::set<T>::is_empty()
{
    return _size==0;
}

template <typename T>
myl::set<T>::set(const std::initializer_list<T>& init)
{
    for(const auto& i: init)
    {
        head.insert(i);
    }
    _size = init.size();
}

template <typename T>
myl::set<T>& myl::set<T>::operator=(const std::initializer_list<T>& init)
{
    head.deleter();
    for(const auto& i: init)
    {
        head.insert(i);
    }
    _size = init.size();
}
