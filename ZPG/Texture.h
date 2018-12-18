#pragma once
#include <GL/glew.h>
#include <string>
#include "../Libraries/soil/src/SOIL.h"
#include "Dictionary.h"
#include "Shader.h"

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
				GLuint _unit;
				//static Generic::Dictionary<std::string, Texture*> _textures;
			public:
				static Texture* Load(std::string file, unsigned flags = SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
				Texture(std::string file, unsigned flags = SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
				Texture* Use(Shader* shader, std::string prefix);
			};

		}
	}
}
