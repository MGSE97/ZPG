#include "Material.h"



Engine::Components::Graphics::Material::Material(Graphics::Program* program)
{
	Values = new Generic::Collection<MaterialValueBase*>();
	Program = program;
}


Engine::Components::Graphics::Material::~Material()
{
	Values->clear();
	delete Values;
}

/*template<typename T>
Engine::Components::Graphics::Material* Engine::Components::Graphics::Material::Add(Shader* shader, const GLchar* property, T* value)
{
	Values->Add(new MaterialValue<T>(shader, property, value));
	return this;
}*/

Engine::Components::Graphics::Material* Engine::Components::Graphics::Material::Use()
{
	Program->Use();
	for (auto& value : *Values)
		value->Set(Program);
	return this;
}
