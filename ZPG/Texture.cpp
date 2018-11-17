#include "Texture.h"
#include <iostream>

Engine::Components::Graphics::Texture::Texture(std::string file, unsigned int flags)
{
	_texture = SOIL_load_OGL_texture(file.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, flags);
	if(_texture == 0)
	{
		fprintf(stderr, "Texture loading from %s failed!", file.c_str());
	}
}

Engine::Components::Graphics::Texture* Engine::Components::Graphics::Texture::Use(Shader* shader, std::string prefix)
{
	shader->SendUniform(prefix + "Texture", reinterpret_cast<int*>(&_texture));
	return this;
}
