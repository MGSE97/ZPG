#pragma once
#include <GL/glew.h>
#include "VertexBufferObject.h"
#include "ReadOnlyProperty.h"

namespace Engine
{
	namespace Components
	{
		namespace Objects
		{
			class VertexAttributeObject
			{
			public:
				VertexAttributeObject(int index, VertexBufferObject * VBO, int dimensions, int size, int offset);
				~VertexAttributeObject();
				GLuint Get();
				int Dimensions;
				int Index;
				int Offset;
				int Size;
			private:
				GLuint _VAO = 0;
			};
		}
	}
}

