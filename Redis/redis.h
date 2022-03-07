#ifndef RED_H
#define RED_H

#include <iostream>

#include "./string/string.h"
#include "./list/list.h"
#include "./unordered_map/Unordered_map.h"
#include "./set/set.h"
#include"./Priority_queue/P_Queue.h"

namespace myl
{
    class Redis
    {
    public:
       Redis();
       Redis(const Redis&) = delete;
       Redis& operator=(const Redis&) = delete;
       Redis(Redis&&) = delete;
       Redis& operator=(Redis&&) = delete;
       ~Redis()=default;
 
       String lpush(const vector<String>&);
       String rpush(const vector<String>&);
       String get_list(const vector<String>&);
       String clear_list(const vector<String>&);
       String um_push(const vector<String>&);
       String get_um(const vector<String>&);
       String clear_um(const vector<String>&);
       String str_push(const vector<String>&);
       String get_str(const vector<String>&);
       String clear_str(const vector<String>&);
       String set_push(const vector<String>&);
       String get_set(const vector<String>&);
       String clear_set(const vector<String>&);
       String get_queue(const vector<String>&);
       String get_queue_top(const vector<String>&);
       String set_queue(const vector<String>&);
       String clear_queue(const vector<String>&);
       String Redis_work(const vector<String>&);
       String Help(const vector<String>&);
    private:
       Unordered_map<String, myl::list<String>> um_sl;
       Unordered_map<String, String> um_ss;
       Unordered_map<String, Unordered_map<String, String>> um_umss; 
       Unordered_map<String, myl::set<String>> um_sset;
       Unordered_map<String, myl::P_Queue<String>> um_sq;
       myl::Unordered_map<String,String(Redis::*)(const myl::vector<myl::String>&)> u_map;
    };
} 

myl::Redis::Redis()
{
    u_map["LPUSH"] = &Redis::lpush;
    u_map["RPUSH"] = &Redis::rpush;
    u_map["GET_LIST"] = &Redis::get_list;
    u_map["CLEAR_LIST"] = &Redis::clear_list;
    u_map["UM_PUSH"] = &Redis::um_push;
    u_map["GET_UM"] = &Redis::get_um;
    u_map["CLEAR_UM"] = &Redis::clear_um;
    u_map["STR_PUSH"] = &Redis::str_push;
    u_map["GET_STR"] = &Redis::get_str;
    u_map["CLEAR_STR"] = &Redis::clear_str;
    u_map["SET_PUSH"] = &Redis::set_push;
    u_map["GET_SET"] = &Redis::get_set;
    u_map["CLEAR_SET"] = &Redis::clear_set;
    u_map["SET_QUEUE"] = &Redis::set_queue;
    u_map["GET_QUEUE"] = &Redis::get_queue;
    u_map["GET_QUEUE_TOP"] = &Redis::get_queue_top;
    u_map["CLEAR_QUEUE"] = &Redis::clear_queue;
    u_map["HELP"] = &Redis::Help;
}

myl::String myl::Redis::Redis_work(const vector<String>& text)
{
    if(text.size() >= 1 and u_map.bool_find(text[0])) {
       return (this->*u_map[text[0]])(text);
    }
    return "Invalid command\nTry HELP";
}

myl::String myl::Redis::Help(const vector<String>& text)
{
 return "\t___________________________________________________________________________________"
        "\n\t_________________________________________HELP______________________________________\n"
        "\t___________________________________________________________________________________\n"
        "LPUSH         -> Adds element(s) in the front of the List           \"E.G. LPUSH List_name value\"\n"
        "RPUSH         -> Adds element(s) in the end of the List             \"E.G. RPUSH List_name value\"\n"
        "GET_LIST      -> Returns all elements of the List                   \"E.G. GET_LIST List_name\"\n"
        "CLEAR_LIST    -> Deletes all elements of the List                   \"E.G. CLEAR_LIST List_name\"\n"
        "UM_PUSH       -> Adds elements into Unordered_map                   \"E.G. UM_PUSH Unordered_map_name key value\"\n"
        "GET_UM        -> Returns element from Unordered_map                 \"E.G. GET_UM Unordered_map_name key\"\n"
        "CLEAR_UM      -> Deletes all elements of Unordered_map              \"E.G. CLEAR_UM Unordered_map_name\"\n"
        "STR_PUSH      -> Adds element to String                             \"E.G. STR_PUSH String_name value\"\n"
        "GET_STR       -> Returns all elements of the String                 \"E.G. GET_STR String_name\"\n"
        "CLEAR_STR     -> Deletes all elements of the String                 \"E.G. CLEAR_STR String name\"\n"
        "SET_PUSH      -> Adds element in Set                                \"E.G. SET_PUSH Set_name value\"\n"
        "GET_SET       -> Returns all elements of Set                        \"E.G. GET_SET Set_name\"\n"
        "CLEAR_SET     -> Deletes all elements of Set                        \"E.G. CLEAR_SET Set_name\"\n"
        "SET_QUEUE     -> Adds element in Priority_Queue                     \"E.G. SET_QUEUE Queue_name value priority\"\n"
        "GET_QUEUE     -> Returns all elements of Priority_Queue             \"E.G. GET_QUEUE Queue_name\"\n"
        "GET_QUEUE_TOP -> Returns the top element of Priority_Queue          \"E.G. GET_QUEUE_TOP Queue_name\"\n"
        "CLEAR_QUEUE   -> Deletes all elements from Priority_Queue           \"E.G. CLEAR_QUEUE Queue_name\"\n";
}

myl::String myl::Redis::lpush(const vector<String>& text)
{
    if(text.size() > 2) {
        for(int i = 2; i < text.size(); ++i) {
           um_sl[text[1]].push_front(text[i]);
        }
        return "Complate LPUSH !\n";
    }
    if(text.size() == 2) {
        um_sl[text[1]];
        return  "Empty list created !\n";
    }
    return "Invalid command\nTry HELP\n";
}

myl::String myl::Redis::rpush(const vector<String>& text)
{
    if(text.size() > 2) {
        for(int i = 2; i < text.size(); ++i) {
           um_sl[text[1]].push_back(text[i]);
        }
        return "Compleat RPUSH!\n";
    }
    if(text.size() == 2) {
        um_sl[text[1]];
        return  "Empty list creating\n";
    }
    return "Invalid command\nTry HELP\n";
}

myl::String myl::Redis::get_list(const vector<String>& text)
{
    if(text.size() == 2 and !(um_sl[text[1]].is_empty())) {
        String str{};
        for(auto it=um_sl[text[1]].begin();it!=um_sl[text[1]].end();++it) {
            str = str + (*it) +'\n';
        }
        return str;
    }
    if(text.size() >= 3 and text.size() < 5) {
        String str{};
        int32_t beg = 0;
        int32_t end = um_sl[text[1]].size() - 1;
        for(auto it = um_sl[text[1]].begin(); it != um_sl[text[1]].end(); ++it) {
            if(text[2].stoi() >= beg){
                if(text[3].stoi() <= end) {
                    str = str + (*it) + '\n';
                } else { 
                    --end;
                }
            } else {
                ++beg;
            }
        }
        return str;
    }
    return "This list empty !\n";
}

myl::String myl::Redis::clear_list(const vector<String>&text)
{
    if(text.size() == 2 ) {
        if(um_sl[text[1]].size()) {
            um_sl[text[1]].clear();
            return (text[1] + " named list is cleaned\n");
        }
        return text[1] + " named list is already empty\n";
    }
    return "Invalid command\nTry HELP\n";
}

myl::String myl::Redis::um_push(const vector<String>&text)
{

    if(text.size() % 2 == 0 and text.size() > 2) {
        for(int i = 2;i < text.size();i += 2) {
            um_umss[text[1]].emplace(text[i], text[i + 1]);
        }
        return "Complate push in U_map\n";
    }
    return "Invalid command\nTry HELP\n";
}

myl::String myl::Redis::get_um(const vector<String>&text)
{
    if(text.size() == 3) {
        if(!um_umss[text[1]][text[2]].empty()) {
           return um_umss[text[1]][text[2]];
        }
        return "Invalid command\nTry HELP\n";
    }
    if(text.size() > 3) {
        myl::String str;
        for(int i = 2; i < text.size(); ++i) {
            str = str + text[i] + " - " + um_umss[text[1]][text[i]] + '\n';
        }
        return  str;
    }
    return "Invalid command\nTry HELP\n";
}

myl::String myl::Redis::clear_um(const vector<String>& text) //?
{
    if(text.size() == 2) {
        um_umss[text[1]].clear();
        return text[1] + " named U_map cleaning\n";
    }
    return "Invalid command\nTry HELP\n";
}

myl::String myl::Redis::set_queue(const vector<String>& text)
{
    if(text.size() == 2) {
        um_sq[text[1]];
        return "Empty prior_queue created !\n";
    }
    if(text.size() % 2 == 0) {
        for(int i = 2; i < text.size(); i += 2) {
            um_sq[text[1]].push(text[i], text[i + 1].stoi());
        }
        return "Complete push in Queue\n";
    }
    return "Invalid command\nTry HELP\n";
}

myl::String myl::Redis::get_queue(const vector<String>& text)
{
    if(text.size() == 2) {
        if(!um_sq[text[1]].is_empty()) {
            String str;
            um_sq[text[1]].print(str);
            return str;
        }
        return text[1] + " named Prior_Queue already empty !\n";
    }
    return "Invalid command\nTry HELP\n";
}

myl::String myl::Redis::get_queue_top(const vector<String>& text)
{
    if(text.size() == 2  ) {
        if(!(um_sq[text[1]].is_empty())) {
            return um_sq[text[1]].top();
        }
        return text[1] + " named Prior_Queue already empty !\n";
    }
    return "Invalid command\nTry HELP\n";
}

myl::String myl::Redis::clear_queue(const vector<String>&text)
{
    if(text.size() == 2) {
        um_sq[text[1]].clear();
        return text[1] + " nemed Queue cleaned\n";
    }
    return "Invalid command\nTry HELP\n";
}

myl::String myl::Redis::str_push(const vector<String>& text)
{
    if(text.size() == 2) {
        um_ss[text[1]];
        return "Empty String ready !\n";
    }
    if(text.size() > 2) {
        for(int32_t i = 2; i < text.size(); ++i) {
            um_ss[text[1]] = um_ss[text[1]] + text[i];
        }
        return "Complete push on String !\n";
    }
    return "Invalid command\nTry HELP\n";
}

myl::String myl::Redis::get_str(const vector<String>& text)
{
    if(text.size() == 2) {
        if(!um_ss[text[1]].empty()) {
            return um_ss[text[1]];
        }
        return text[1] + " named String empty !\n";
    }
    return "Invalid command\nTry HELP\n";
}

myl::String myl::Redis::clear_str(const vector<String>& text)
{
    if(text.size() == 2 ) {
        if(!um_ss[text[1]].empty()) {
            um_ss[text[1]].clear();
            return text[1] + " named String cleaned !\n";
        }
        return text[1] + " named String already empty !\n";
    }
    return "Invalid command\nTry HELP\n";
}

myl::String myl::Redis::set_push(const vector<String>& text)
{
    if(text.size() == 2) {
        um_sset[text[1]];
        return "Empty Set ready !\n";
    }
    if(text.size() >= 3){
        for(int i = 2; i < text.size(); ++i) {
            um_sset[text[1]].insert(text[i]);
        }
        return "Complete push on Set\n";
    }
    return "Invalid command\nTry HELP\n";
}

myl::String myl::Redis::get_set(const vector<String>& text)
{
    if(text.size() == 2 ) {
        if(!um_sset[text[1]].is_empty()) {
            String str{};
            um_sset[text[1]].copy_str(str);
            return str;
        }
        return "Set is empty !\n";
    }
    return "Invalid command\nTry HELP\n";
}

myl::String myl::Redis::clear_set(const vector<String>& text)
{
    if(text.size() == 2) {
        if(!um_sset[text[1]].is_empty()) {
            um_sset[text[1]].clear();
            return text[1] + " named Set is celaned !\n";
        }
        return text[1] + " named Set is already empty\n";
    }
    return "Invalid command\nTry HELP\n";
}

#endif