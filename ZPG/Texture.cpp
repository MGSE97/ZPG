#include "Texture.h"
#include <iostream>

Engine::Components::Graphics::Texture* Engine::Components::Graphics::Texture::Load(std::string file, unsigned flags)
{
	static Generic::Dictionary<std::string, Texture*> _textures;
	auto texture = _textures.Get(file);
	if (texture == nullptr)
	{
		texture = new Texture(file, flags);
		_textures.Add(file, texture);
	}

	return texture;
}

Engine::Components::Graphics::Texture::Texture(std::string file, unsigned int flags)
{
	_texture = SOIL_load_OGL_texture(file.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, flags);
	if(_texture == 0)
	{
		fprintf(stderr, "Texture loading from %s failed!", file.c_str());
	}
	else {
		glEnable(GL_TEXTURE_2D);
		_unit = _texture-1;
	}
}

Engine::Components::Graphics::Texture* Engine::Components::Graphics::Texture::Use(Shader* shader, std::string prefix)
{
	glActiveTexture(GL_TEXTURE0 + _unit);
	glBindTexture(GL_TEXTURE_2D, _texture);
	shader->SendUniform(prefix + "Texture", reinterpret_cast<int*>(&_unit));
	return this;
}
