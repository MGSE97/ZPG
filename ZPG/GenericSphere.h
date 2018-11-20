#pragma once
#include <vector>

namespace Engine
{
	namespace Objects
	{
		class GenericSphere
		{
		public:
			std::vector<float>* vertices;
			std::vector<float>* normals;
			std::vector<float>* texcoords;
			std::vector<float>* array;
			std::vector<unsigned short>* indices;
			GenericSphere(float radius, unsigned int rings, unsigned int sectors);
			~GenericSphere();
		};
	}
}

