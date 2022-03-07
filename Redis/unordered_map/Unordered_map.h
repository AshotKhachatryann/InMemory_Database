#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

// #include <list>
#include <exception>
#include <stdexcept>

#include "../list/list.h"
#include "../string/string.h"
#include "../vector/vector.h"

namespace myl
{
	template<typename Key, typename Val>
	struct pair
	{
		Key first {};
		Val second {};
		pair() {};
		pair(Key _k, Val _v) :first(_k), second(_v) {};
		pair(const pair<Key,Val> &other);
		pair(pair<Key,Val>&& other);
		void swap(pair<Key, Val>& ob);
		pair<Key,Val>& operator=(const pair<Key,Val>& other);
		pair<Key,Val>& operator=(pair<Key,Val>&& other);

		bool operator==(const pair<Key,Val>& oth);

		~pair() = default;
	};

	template<typename K,typename V>
	myl::pair<K,V> make_pair(const K& key,const V& val)
	{
		myl::pair<K,V> tmp(key,val);
		return tmp;
	}

	struct hesh
	{
		hesh() = default;
		uint32_t operator()(const myl::String& ob, const uint32_t& tabel_size) const
		{
			uint32_t h = 0, rand_number_1 = 12343, rand_number_2 = 58457;
			for (int32_t i=0; i != ob.size(); ++i)
			{
				h = (rand_number_1 * h + static_cast<int>(ob[i])) % tabel_size;
				rand_number_1 = ((rand_number_1 * rand_number_2) % (tabel_size - 1));
			}
			return h < 0 ? h + tabel_size : h;
		}
	};

	template <typename Key,typename Val,typename Hesh_method = hesh>
	class Unordered_map
	{
	private:
		Hesh_method hesh_str;
		vector<myl::list<myl::pair<Key, Val>>> obj;

	public:
		Unordered_map() ;
		~Unordered_map() = default;
		Unordered_map(const Key& , const Val& );
		Unordered_map(const Unordered_map<Key, Val, Hesh_method>& );
		Unordered_map(Unordered_map<Key, Val, Hesh_method>&& );
		Unordered_map& operator=(const Unordered_map& );
		Unordered_map& operator=(const Unordered_map&& ) ;

		Val& operator[](const Key&);
		void insert(myl::pair<Key, Val>);
		void emplace(const Key&, const Val&);
		void erase(const Key&);
		bool bool_find(const Key&);
		Val& at(const Key&) ;
		void clear();
	};

} // myl namespace

#include "Unordered_map.hpp"

#endif //UNORDERED_MAP_H