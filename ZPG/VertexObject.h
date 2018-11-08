#pragma once
#include "VertexBufferObject.h"
#include "VertexAttributeObject.h"
#include "Program.h"
#include "Material.h"
#include "Transform.h"

namespace Engine
{
	namespace Components
	{
		namespace Objects
		{
			struct VAOConfig;

			class VertexObject
			{
			protected:
				/*VertexBufferObject* VBO;
				Generic::Collection<VertexAttributeObject*>* VAOs;*/
				int Dimensions;
				GLuint _VBO = 0;
				GLuint _VAO = 0;
				int _Id;
				int _attribute_id;
				int Size;
				static int _object_id;
				VertexObject* Add(int size, int offset);
			public:
				Transform* Transform;
				VertexObject(Graphics::Material* material, const float* points, int size, int dimensions, Generic::Collection<VAOConfig*>* configs = nullptr);
				~VertexObject();
				VertexObject* Draw();
				Graphics::Material* Material;
			};

			struct VAOConfig
			{
			public:
				VAOConfig();
				VAOConfig(int size, int offset);
				int Size;
				int Offset;
			};
		}
	}
}

