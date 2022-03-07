#include "vector.h"

template<typename T>
myl::vector<T>::vector()
{
    _size = 0;
    _capacity = 1;
    arr = new T[1];
}

template<typename T>
myl::vector<T>::vector(int col)
{
    _size=col;
    _capacity = 2 *_size;
    arr = new T[_capacity];
}

template<typename T>
myl::vector<T>::vector(const std::initializer_list<T>& elems) 
{
    _size = elems._size();
    _capacity = _size * 2;
    arr = new T[_capacity];
    int i = 0;
    for(auto it = elems.begin(); it != elems.end(); ++it, ++i) 
    {
        arr[i] = *it;
    }
}

template<typename T>
myl::vector<T>::vector(int colum,const T& value)
{
    _size = colum;
    _capacity = _size * 2;
    arr = new T[_capacity];
    for(int i = 0; i < _size; i++) 
    {
        arr[i] = value;
    }
}

template<typename T>
myl::vector<T>::~vector()
{
    delete[] arr;
}

template<typename T>
void myl::vector<T>::push_back(const T& value) 
{
    if(_capacity == _size) 
    {
        T *tmp = new T[_capacity * 2];
        for(int i = 0; i < _capacity; ++i) 
        {
            tmp[i] = arr[i];
        }
        delete[] arr;
        arr = tmp;
        _capacity *= 2;
        tmp = nullptr;
    }
    arr[_size++] = value;
}

template<typename T>
void myl::vector<T>::pop_back() 
{
    T *tmp = new T[_capacity - 1];
    for(int i = 0; i < _size - 1; i++) 
    {
        tmp[i] = arr[i];
    }
    delete [] arr;
    arr = tmp;
    _capacity--;
    _size--;
}

template<typename T>
int myl::vector<T>::size() const
{
    return _size;
}

template<typename T>
int myl::vector<T>::capacity() const
{
    return _capacity;
}

template<typename T>
myl::vector<T>::vector(const vector & other)
{
    this->_size = other._size;
    this->_capacity = other._capacity;
    this->arr = new T [other._capacity];
    for(int i = 0;i < _size; i++) 
    {
        this->arr[i] = other.arr[i];
    }
}

template<typename T>
myl::vector<T>::vector(vector && other) noexcept
{
    arr = other.arr;
    this->_size = other._size;
    this->_capacity = other._capacity;
    other.arr = nullptr;
    this->_size = 0;
    this->_capacity = 0;
}

template<typename T>
myl::vector<T> & myl::vector<T>::operator=(const vector & other)
{
    if(this == &other) 
    {
        return * this;
    }
    delete [] arr;
    this->_size = other._size;
    this->_capacity = other._capacity;
    this->arr = new T [other._capacity];
    for(int i = 0;i < _size; i++){
    
        this->arr[i] = other.arr[i];
    }
    return *this;
}

template<typename T>
myl::vector<T> & myl::vector<T>::operator=(vector && other) noexcept
{
    if(this == &other) 
    {
        return *this;
    }
    delete[] arr;
    this->_size = other._size;
    this->_capacity = other._capacity;
    this->arr = other.arr;
    other.arr = nullptr;
    return *this;
}

template<typename T>
T& myl::vector<T>::operator[](int index) 
{
    return arr[index];
}

template<typename T>
const T& myl::vector<T>::operator[](int index) const
{
    return arr[index];
}


template<typename T>
void myl::vector<T>::shrink_to_fit() 
{
    _capacity = _size;
}

template<typename T>
void myl::vector<T>::insert(myl::vector<T>::iterator& iter,const T& value) 
{
    if(_size < _capacity) 
    {
        for(iterator i = this->end(); i != iter; --i) 
        {
            *i = *(i - 1);
        }
        *iter = value;
    }
    else
    {
        _capacity *= 2;
        T* tmp = new T [_capacity];
        int j = 0;
        for(auto i = this->begin();i != iter;++i )
        {
            tmp[j++] = *i;
        }
        tmp[j] = value;
        for(;iter != this->end(); ++iter)
        {
            tmp[++j] = *iter;
        }
        delete[] arr;
        arr = tmp;
    }
    _size++;
}

template<typename T>
void myl::vector<T>::erease(myl::vector<T>::iterator& iter) 
{
    T *tmp = new T[_capacity];
    int i = 0;
    for(i = 0; i < _size; i++) 
    {
        if(arr[i] == *iter) 
        {
            break;
        } 
        tmp[i] = arr[i];
    }
    for(int j = i + 1;j < _size; ++j) 
    {
        tmp[i] = arr[j];
        i++;
    }
    delete [] arr;
    arr = tmp;
    tmp = nullptr;
    _size--;
}

template<typename T>
typename myl::vector<T>::iterator myl::vector<T>::begin() 
{
    myl::vector<T>::iterator it(arr);
    return it;
}

template<typename T>
typename myl::vector<T>::iterator myl::vector<T>::end() 
{
    myl::vector<T>::iterator it(arr + _size);
    return it;
}

template <typename T>
myl::vector<T>::iterator::iterator(T * p)
{
    iter = p;
}

template <typename T>
myl::vector<T>::iterator::iterator(const iterator& r)
{
    iter = r.iter;
}

template <typename T>
typename myl::vector<T>::iterator & myl::vector<T>::iterator::operator=(const iterator& r)
{
    if(this == &r) { return *this; }
    this->iter = r.iter;
    return *this;
}

template <typename T>
typename myl::vector<T>::iterator myl::vector<T>::iterator::operator+(int add)
{
    iterator it;
    it.iter = iter + add;
    return it;
}

template <typename T>
typename myl::vector<T>::iterator myl::vector<T>::iterator::operator-(int sub)
{
    iterator it;
    it.iter = iter - sub;
    return it;
}


template <typename T>
typename myl::vector<T>::iterator& myl::vector<T>::iterator::operator+=(int add) 
{
    this->iter += add;
    return *this;
}

template <typename T>
typename myl::vector<T>::iterator& myl::vector<T>::iterator::operator-=(int sub) 
{
    this->iter -= sub;
    return *this;
}

template <typename T>
T& myl::vector<T>::iterator::operator++() 
{
    ++iter;
    return *iter;
}

template <typename T>
T& myl::vector<T>::iterator::operator++(int) 
{
    T *tmp = iter;
    ++iter;
    return *tmp;
}

template <typename T>
T& myl::vector<T>::iterator::operator--() 
{
    --iter;
    return *iter;
}

template <typename T>
T& myl::vector<T>::iterator::operator--(int) 
{
    T *tmp = iter;
    --iter;
    return *tmp;
}

template <typename T>
bool myl::vector<T>::iterator::operator!=(const iterator& other) const 
{
    return this->iter != other.iter;
}

template <typename T>
bool myl::vector<T>::iterator::operator==(const iterator& other) const 
{
    return this->iter == other.iter;
}

template <typename T>
T& myl::vector<T>::iterator::operator*() const 
{
    return *iter;
}

template<typename T>
void myl::vector<T>::clear()
{
    delete []arr;
    _size = 0;
    _capacity = 1;
    arr = new T[_capacity];
}