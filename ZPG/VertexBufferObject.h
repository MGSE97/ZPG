#pragma once
#include <GL/glew.h>
#include <vector>

namespace Engine
{
	namespace Components
	{
		namespace Objects
		{
			class VertexBufferObject
			{
			public:
				VertexBufferObject(float* points, int size);
				~VertexBufferObject();
				GLuint Get();
				int GetId();
			private:
				GLuint _VBO = 0;
				int _Id;
				static int _id;
			};
		}
	}
}
