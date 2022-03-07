
template<typename Key, typename Val,typename Hesh_method >
myl::Unordered_map<Key, Val, Hesh_method>::Unordered_map():obj(800) {};

template<typename Key, typename Val, typename Hesh_method >
myl::Unordered_map<Key, Val, Hesh_method>::Unordered_map(const Key& k, const Val& v):obj(800)
{
	uint32_t index = hesh_str(k, obj.size());
	obj[index].push_back(make_pair(k, v));
	
}

template<typename Key, typename Val, typename Hesh_method >
myl::Unordered_map<Key, Val, Hesh_method>::Unordered_map(const Unordered_map<Key, Val, Hesh_method>& other)
{
	this->obj = other.obj;
}

template<typename Key, typename Val, typename Hesh_method >
myl::Unordered_map<Key, Val, Hesh_method>::Unordered_map(Unordered_map<Key, Val, Hesh_method>&& oth) 
{
	this->obj = oth.obj;
}

template<typename Key, typename Val, typename Hesh_method >
Val& myl::Unordered_map<Key, Val, Hesh_method>::operator[](const Key& ki)
{
	uint32_t ind = hesh_str(ki, obj.size());

	if(obj[ind].begin() != nullptr){
	for (auto it = obj[ind].begin(); it != obj[ind].end(); ++it)
	{
		if (it->first == ki)
			return it->second;
	}
	}

	obj[ind].push_back(make_pair(ki,Val()));
	typename myl::list<myl::pair<Key,Val>>::iterator itr = obj[ind].begin();
	itr->first = ki;
	return itr->second;
}
 


template<typename Key, typename Val, typename Hesh_method >
myl::Unordered_map<Key, Val, Hesh_method>& myl::Unordered_map<Key, Val, Hesh_method>::operator=(const Unordered_map& other)
{
	this->obj = other.obj;
	return *this;
}

template<typename Key, typename Val, typename Hesh_method >
myl::Unordered_map<Key, Val, Hesh_method>& myl::Unordered_map<Key, Val, Hesh_method>::operator=(const Unordered_map&& oth)
{
	this->obj = oth.obj;
	return *this;
}

template<typename Key, typename Val, typename Hesh_method >
void myl::Unordered_map<Key, Val, Hesh_method>::insert(myl::pair<Key, Val>ob)
{
	uint32_t ind = hesh_str(ob.first, obj.size());
	obj[ind].push_back(make_pair(ob.first, ob.second));
}

template<typename Key, typename Val, typename Hesh_method >
void myl::Unordered_map<Key, Val, Hesh_method>::emplace(const Key& ki, const Val& va)
{
	uint32_t ind = hesh_str(ki, obj.size());
	obj[ind].push_back(make_pair(ki, va));
}

template<typename Key, typename Val, typename Hesh_method >
void myl::Unordered_map<Key, Val, Hesh_method>::erase(const Key& ki)
{
	uint32_t ind = hesh_str(ki, obj.size());
	if(obj[ind].begin() != nullptr){
		for (auto it = obj[ind].cbegin(); it != obj[ind].cend(); ++it)
		{
			if (it->first == ki)
			{
				obj[ind].erase(it);
				break;
			}
		}
	}

}

template<typename Key, typename Val, typename Hesh_method >
Val& myl::Unordered_map<Key, Val, Hesh_method>::at(const Key& ob) 
{
	uint32_t ind = hesh_str(ob, obj.size());
	try
	{
		if(obj[ind].begin() != nullptr){
		    for (auto it = obj[ind].begin(); it != obj[ind].end(); ++it)
			{
				if (it->first == ob)
					return it->second;
			}
		}
	throw std::out_of_range("out of range");
	
	}
	catch (const std::out_of_range& obe)
	{
		obe.what();
		abort();
	}
}

template<typename Key, typename Val, typename Hesh_method >
bool myl::Unordered_map<Key, Val, Hesh_method>::bool_find(const Key& ob) 
{
	uint32_t ind = hesh_str(ob, obj.size());
	if(obj[ind].begin() != nullptr){
		for (auto it = obj[ind].begin(); it != obj[ind].end(); ++it)
		{
			if (it->first == ob)
				return  true;
		}
	}
	return false;
}


template<typename Key, typename Val, typename Hesh_method >
void myl::Unordered_map<Key,Val,Hesh_method>::clear()
{
	for(int32_t i = 0; i < obj.size(); ++i){
		obj[i].clear();
	}

}


template <typename Key, typename Val>
myl::pair<Key,Val>::pair(const myl::pair<Key,Val> &other)
{
	this->first = other.first;
	this->second = other.second;
}

template <typename Key, typename Val>
myl::pair<Key,Val>::pair(myl::pair<Key,Val> &&other)
{
	this->first = other.first;
	this->second = other.second;
}

template <typename Key, typename Val>
void myl::pair<Key,Val>::swap(pair<Key, Val>& ob)
{
	pair<Key, Val>_tmp;
	_tmp.first = first;
	_tmp.second = second;
	first = ob.first;
	second = ob.second;
	ob.first = _tmp.first;
	ob.second = _tmp.second;
}

template <typename Key, typename Val>
myl::pair<Key,Val>& myl::pair<Key,Val>::operator=(const pair<Key, Val>& other)
{
	this->first = other.first;
	this->second = other.second;
	return *this;
}

template <typename Key, typename Val>
myl::pair<Key,Val>& myl::pair<Key,Val>::operator=(pair<Key, Val>&& other)
{
	this->first = other.first;
	this->second = other.second;
	other.first = {};
	other.second = {};
	return *this;
}

template <typename Key, typename Val>
bool myl::pair<Key,Val>::operator==(const pair<Key, Val>& oth)
{
	return (this->first == oth.first and this->secondconst == oth.second);
}
