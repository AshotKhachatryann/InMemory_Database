#ifndef P_QUEUE_H
#define P_QUEUE_H

#include"../string/string.h"

namespace myl
{
    template <typename T>
    class P_Queue
    {
    public:
        P_Queue();
        ~P_Queue();
        P_Queue(const P_Queue&);
        P_Queue& operator=(const P_Queue &);
        P_Queue(P_Queue &&) noexcept;
        P_Queue& operator=(P_Queue &&) noexcept;
    public:
        void push(T , int);
        T pop();
        T top();
        int size() {return _size;}
        void print(String&);
        void clear();
        bool is_empty() { return _size==0;}
    private:
        T* buffer;
        int* p;
        int _size;
    };
    
    template <typename T>
    myl::P_Queue<T>::P_Queue() : buffer{}, p{}, _size{} {}

    template <typename T>
    myl::P_Queue<T>::P_Queue::~P_Queue()
    {
        if(_size > 0) {
            delete[] buffer;
            delete[] p;
        }
    }

    template <typename T>
    myl::P_Queue<T>::P_Queue(P_Queue<T> && rhs) noexcept
    {
        if(_size > 0) {
            delete[] buffer;
            delete[] p;
        }
        _size = rhs._size;
        this->buffer = rhs.buffer;
        this->p = rhs.p;
        rhs.buffer = nullptr;
        rhs.p = nullptr;
        rhs._size = 0;
    }

    template <typename T>
    myl::P_Queue<T>::P_Queue(const P_Queue<T> & rhs) 
    {
        this->buffer = new T[rhs._size];
        this->p = new int[rhs._size];
        this->_size = rhs._size;

        for(int i {}; i < _size; ++i) {
            this->buffer[i] = rhs.buffer[i];
            this->p[i] = rhs.p[i];
        }
    }

    template <typename T>
    P_Queue<T>& myl::P_Queue<T>::operator=(const P_Queue<T>& rhs) 
    {
        if(this == &rhs) {
            return *this;
        }
        if(_size > 0) {
            delete[] this->buffer;
            delete[] this->p;
            this->_size = 0;
        }

        this->buffer = new T[rhs._size];
        this->p = new int[rhs._size];
        this->_size = rhs._size;

        for(int i {}; i < _size; ++i) {
            this->buffer[i] = rhs.buffer[i];
            this->p[i] = rhs.p[i];
        }
        return *this;
    }

    template <typename T>
    P_Queue<T>& myl::P_Queue<T>::operator=(P_Queue<T> && rhs) noexcept 
    {
        if(this == &rhs) {
            return *this;
        }
        if(_size > 0) {
            delete[] buffer;
            delete[] p;
        }
        buffer = rhs.buffer;
        p = rhs.p;
        _size = rhs._size;
        rhs.buffer = nullptr;
        rhs.p = nullptr;
        return *this;
    }

    template <typename T>
    void myl::P_Queue<T>::push(T elem, int priority) 
    {
        T* buffer2;
        int* p2;
        buffer2 = new T[_size + 1];
        p2 = new int[_size + 1];

        int pos;

        if(_size == 0) {
            pos = 0;
        }
        else {
            pos = 0;
            while (pos < _size) {
                if (p[pos] <= priority) {
                    while(p[pos] == priority) {
                        pos++;
                    }
                    break;
                }
                ++pos;
            }
        }

        for(int i = 0; i < pos; ++i) {
            buffer2[i] = buffer[i];
            p2[i] = p[i];
        }

        buffer2[pos] = elem;
        p2[pos] = priority;
        
        for(int i = pos + 1; i < _size + 1; ++i) {
            buffer2[i] = buffer[i - 1];
            p2[i] = p[i - 1];
        }

        if(_size > 0) {
            delete[] buffer;
            delete[] p;
        }

        buffer = buffer2;
        p = p2;

        ++_size;
        
    }
    
    template <typename T>
    T myl::P_Queue<T>::pop() 
    {
        if(_size == 0) {
            return _size;
        }

        T* buffer2;
        int* p2;

        buffer2 = new T[_size - 1];
        p2 = new int[_size - 1];

        T item = buffer[0];

        for(int i = 0; i < _size - 1; ++i) {
            buffer2[i] = buffer[i + 1];
            p2[i] = p[i + 1];
        }

        if(_size > 0) {
            delete[] buffer;
            delete[] p;
        }

        --_size;
        buffer = buffer2;
        p = p2;

        return item;
    }
    
    template <typename T>
    T myl::P_Queue<T>::top() 
    {
        return buffer[0];
    }

    template <typename T>
    void myl::P_Queue<T>::print(String& buf) 
    {
        for(int i = 0; i < _size; ++i) {
            buf=buf+buffer[i];
            buf=buf+'\n';
        }
    }

    template<typename T>
    void myl::P_Queue<T>::clear()
    {
        delete[]buffer;
        delete[]p;
        buffer=new T[_size];
        p=new int[_size];
    }

} // namespace myl

#endif //P_QUEUE_H
