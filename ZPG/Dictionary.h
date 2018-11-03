#pragma once
#include <map>

namespace Generic
{
	template <typename TKey, class TValue>
	class Dictionary : public std::map<TKey, TValue>
	{
	public:
		Dictionary& Add(TKey key, TValue value)
		{
			auto pair = this->find(key);
			if (pair == this->end())
				this->insert(std::pair<TKey, TValue>(key, value));
			else
				pair->second = value;
			
			return *this;
		}

		TValue& Get(const TKey key, TValue _default = nullptr)
		{
			auto r = this->find(key);
			if(r != this->end())
				return r->second;
			return _default;
		}

		TValue& First(TValue _default = nullptr)
		{
			if (this->size() == 0)
				return _default;
			return this->begin()->second;
		}

		TValue& Last()
		{
			return this->end()->second;
		}

		TValue& operator[](TKey key)
		{
			return Get(key);
		}
	};
}
