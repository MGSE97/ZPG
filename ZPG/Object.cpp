#include "Object.h"
#include "Program.h"

Engine::Objects::Object::Object(Components::Graphics::Material* material, const float* points, int size, int dimensions, int startArrayIndex): 
	VertexObject(material, points, size, dimensions, &((new Generic::Collection<Components::Objects::VAOConfig*>())
		->Add(new Engine::Components::Objects::VAOConfig(0, startArrayIndex))
	))
{
	ModelMatrix = new glm::mat4(1.f);
	Material->Values->Add(new Engine::Components::Graphics::MaterialValue<glm::mat4>(
		Material->Program->Shaders->Get("vertex"), "modelMatrix", ModelMatrix
	));
}

Engine::Objects::Object::Object(Components::Graphics::Material* material, const float* points, int size, int dimensions, Generic::Collection<Components::Objects::VAOConfig*> configs) :
	VertexObject(material, points, size, dimensions, &configs)
{
	ModelMatrix = new glm::mat4(1.f);
	Material->Values->Add(new Engine::Components::Graphics::MaterialValue<glm::mat4>(
		Material->Program->Shaders->Get("vertex"), "modelMatrix", ModelMatrix
	));
}

Engine::Objects::Object::~Object()
= default;
