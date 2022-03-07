#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "../vector/vector.h"
#include "../string/string.h"

class Parser
{
public:
    Parser() = default;
    ~Parser() = default;
    void parse_code(const myl::String&);
    void parse_code_com(const myl::String&);
    myl::vector<myl::String> get_tokens() const ;
private:
    myl::vector<myl::String> tokens;
};

void Parser::parse_code(const myl::String& m_str)
{
    myl::String bar ;
    tokens.clear();
    for(int i = 0; i <= m_str.size(); ++i) 
    {    
        if( m_str[i] == '\0' || m_str[i] == ' ' ) {
            if(bar.size() != 0) {
                tokens.push_back(bar);
                bar.clear();
            }
        } else {
            bar.push_back(m_str[i]);
        }
    }
}

void Parser::parse_code_com(const myl::String& m_str)
{
    tokens.clear();
    myl::String tmp;
    int32_t count = 0;
    int32_t pos = 0;
    for(int i = 0; i < m_str.size(); ++i) 
    {
        if( m_str[i] == '\0' || m_str[i] == ' ' ) {
            if(tmp.size() != 0) {
                tokens.push_back(tmp);
                tmp.clear();
                ++count;
            }
            if(count == 2) {
                pos = i;
                break;
            }
        } else {
            tmp.push_back(m_str[i]);
        }
    }
    tmp.clear();
    bool t = true;
    for(int i = pos; i < m_str.size(); ++i) 
    {
        while (m_str[i] == ' ' and t)
        {
            ++i;
        }
        t = false;
        tmp.push_back(m_str[i]);
    }
    tokens.push_back(tmp);
}

myl::vector<myl::String> Parser::get_tokens() const
{
    return tokens;
}

#endif
