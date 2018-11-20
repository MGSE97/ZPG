#pragma once
#include "VertexObject.h"

namespace Engine
{
	namespace Objects
	{
		class Object : public Components::Objects::VertexObject
		{
		protected:
			static int _id;
		public:
			bool Clicked;
			int Id;
			Object(Components::Graphics::Material* material, std::vector<float>* points, int dimensions, bool normals = false, bool uvs = false);
			Object(Components::Graphics::Material* material, const float* points, int size, int dimensions, bool normals = false, bool uvs = false);
			~Object();
			Object* ToggleClicked(GLuint* index);
			Object* SetClicked(Generic::Dictionary<short, bool> mouseKeys);
			bool IsClicked(GLuint* worldObjectId);
		};
	}
}
