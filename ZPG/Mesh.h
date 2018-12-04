#pragma once
#include "Collection.h"
#include "VertexObject.h"

namespace Engine
{
	namespace Components
	{
		namespace Objects
		{
			class Mesh
			{
			public:
				Generic::Collection<VertexObject*>* Components;
				Mesh();
				Mesh* Load(std::string fileName);
				~Mesh();
			};
		}
	}
}

