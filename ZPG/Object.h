#pragma once
#include "VertexObject.h"

namespace Engine
{
	namespace Components
	{
		namespace Objects
		{
			class Object : public VertexObject
			{
			protected:
				static int _id;
			public:
				bool Clicked;
				int Id;
				Object(Application::Materials::StandartMaterial* material, aiMesh* mesh, int dimensions);
				Object(Application::Materials::StandartMaterial* material, std::vector<float>* points, int dimensions, bool normals = false, bool uvs = false, bool faces = false, std::vector<unsigned int>* indices = nullptr);
				Object(Application::Materials::StandartMaterial* material, const float* points, int size, int dimensions, bool normals = false, bool uvs = false, bool faces = false, const unsigned int* indices = nullptr, int indicesSize = 0);
				~Object();
				Object* ToggleClicked(GLuint* index);
				Object* SetClicked(Generic::Dictionary<short, bool> mouseKeys);
				bool IsClicked(GLuint* worldObjectId);
			};
		}
	}
}
