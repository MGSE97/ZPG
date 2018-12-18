#pragma once
#include "Shader.h"
#include <list>
#include <vector>

namespace Generic
{
	template <class T>
	class Collection : public std::vector<T>
	{
	public:
		Collection<T>& Add(T value)
		{
			this->push_back(value);
			return *this;
		}
		T First()
		{
			return this->front();
		}
	};
}
