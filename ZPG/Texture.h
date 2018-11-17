#pragma once
#include <GL/glew.h>
#include <string>
#include "../Libraries/soil/src/SOIL.h"
#include "Program.h"

namespace Engine
{
	namespace Components
	{
		namespace Graphics
		{
			class Texture
			{
			private:
				GLuint _texture;
			public:
				Texture(std::string file, unsigned flags = SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
				Texture* Use(Program* program, Shader* shader, std::string prefix);
			};

		}
	}
}