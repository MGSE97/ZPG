#pragma once
#include "Collection.h"
#include <assimp/postprocess.h>
#include "Object.h"

namespace Engine
{
	namespace Components
	{
		namespace Objects
		{
			class Mesh
			{
			public:
				Generic::Collection<Object*>* Components;
				Mesh();
				Mesh* Load(std::string directoryName, std::string fileName, int importOptions = aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace | aiProcess_RemoveRedundantMaterials);
				~Mesh();
			};
		}
	}
}

