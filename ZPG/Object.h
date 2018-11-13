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
			//glm::mat4* ModelMatrix;
			bool Clicked;
			int Id;
			//Generic::Dictionary<short, bool>* mouseKeys;
			Object(Components::Graphics::Material* material, const float* points, int size, int dimensions = 3, int startArrayIndex = 0);
			Object(Components::Graphics::Material* material, const float* points, int size, int dimensions, Generic::Collection<Components::Objects::VAOConfig*> configs);
			~Object();
			Object* ToggleClicked(GLuint* index);
			Object* SetClicked(Generic::Dictionary<short, bool> mouseKeys);
			bool IsClicked(GLuint* worldObjectId);
		};
	}
}
