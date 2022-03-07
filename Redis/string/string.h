#ifndef STRING_H_
#define STRING_H_

#include <iostream>

#include "../utility/utility.h"
#include"../vector/vector.h"

namespace myl
{
    class String
    {
    public:
        String();
        ~String();
        String(int); 
        String(unsigned int, char);
        String(const char* );
        String(const String &);
        String(String&&);
        String& operator=(const String& obj);
        String& operator=(String&& );
        String operator+(const String &)const;
        String operator+(const char);
        String operator+(const char*);
        String& operator+=(const String &);
        bool operator>(const String &) const;
        bool operator<(const String &) const;
        bool operator==(const String &) const;
        bool operator!=(const String &) const;
        bool operator>=(const String &) const;
        bool operator<=(const String &) const;
        void push_back(char symbol);
        char pop_back();
        void push_front(char symbol);
        char pop_front();
        char* c_str();
        void resize(const int ,char);
        String& erase(const int,int );
        char erase(const int );
        int find(const char) const;
        int find(const String) const;
        int find(const char*) const;
        int stoi()const;
        void insert(const int, char );
        void insert(const int, int, char);
        void insert(const int, const String &);
        void insert(const int , const char*);
        void clear();
        bool empty();
        void replace (char , int);
        void replace (int , const char*); 
        String substr(int , int ) const;
        
        char& operator[](const unsigned index);
        const char& operator[](const unsigned index) const;
        char& at(const unsigned index);
        const char& at(const unsigned index) const;
        inline int size() const {return m_size;}

    private:
        int m_capacity;
        char* m_buffer;
        int m_size;
        const static int LIM = 100;

    };

} // namespace myl

#include "string.hpp"

#endif //STRING_H_
