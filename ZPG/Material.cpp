#include "Material.h"
#include <cstdarg>


Engine::Components::Graphics::Material::Material()
{
	Values = new Generic::Collection<MaterialValueBase*>();
}

Engine::Components::Graphics::Material::Material(Graphics::Shader* shader)
{
	Values = new Generic::Collection<MaterialValueBase*>();
	Shader = shader;
}


Engine::Components::Graphics::Material::~Material()
{
	Values->clear();
	delete Values;
}

Engine::Components::Graphics::Material* Engine::Components::Graphics::Material::SetShader(Graphics::Shader* shader)
{
	Shader = shader;
	return this;
}

/*template<typename T>
Engine::Components::Graphics::Material* Engine::Components::Graphics::Material::Add(Shader* shader, const GLchar* property, T* value)
{
	Values->Add(new MaterialValue<T>(shader, property, value));
	return this;
}*/

Engine::Components::Graphics::Material* Engine::Components::Graphics::Material::Use()
{
	if (Shader != nullptr)
	{
		Shader->Use();
		for (auto& value : *Values)
			value->Set(Shader);
	}
	return this;
}
