#pragma once
#include "Collection.h"

namespace Engine
{
	namespace Objects
	{
		static class GenericOctahedon
		{
		private:
			GenericOctahedon();
			~GenericOctahedon();
		public:
			std::vector<float>* vertices;
			std::vector<unsigned int>* indices;
			static GenericOctahedon* GetInstance();
		};
	}
}


