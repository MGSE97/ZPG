#include "Object.h"
#include "Program.h"
#include "IInputHandler.h"

Engine::Objects::Object::Object(Components::Graphics::Material* material, const float* points, int size, int dimensions, int startArrayIndex) :
	VertexObject(material, points, size, dimensions, &((new Generic::Collection<Components::Objects::VAOConfig*>())
		->Add(new Engine::Components::Objects::VAOConfig(0, startArrayIndex))
		))
{
	Clicked = false;
	/*ModelMatrix = new glm::mat4(1.f);
	Material->Values->Add(new Engine::Components::Graphics::MaterialValue<glm::mat4>(
		Material->Program->Shaders->Get("vertex"), "modelMatrix", ModelMatrix
	));*/
	_colorId = glm::vec4(
		((_VAO & 0x000000FF) >> 0) / 255.0,
		((_VAO & 0x0000FF00) >> 8) / 255.0,
		((_VAO & 0x00FF0000) >> 16) / 255.0,
	1);
	Material->Add(Material->Program->Shaders->Get("fragment"), "colorId", &_colorId);
}

Engine::Objects::Object::Object(Components::Graphics::Material* material, const float* points, int size, int dimensions, Generic::Collection<Components::Objects::VAOConfig*> configs) :
	VertexObject(material, points, size, dimensions, &configs)
{
	Clicked = false;
	/*ModelMatrix = new glm::mat4(1.f);
	Material->Values->Add(new Engine::Components::Graphics::MaterialValue<glm::mat4>(
		Material->Program->Shaders->Get("vertex"), "modelMatrix", ModelMatrix
	));*/
	_colorId = glm::vec4(
		((_VAO & 0x000000FF) >> 0) / 255.0,
		((_VAO & 0x0000FF00) >> 8) / 255.0,
		((_VAO & 0x00FF0000) >> 16) / 255.0,
	1);
	Material->Add(Material->Program->Shaders->Get("fragment"), "colorId", &_colorId);
}

Engine::Objects::Object::~Object()
= default;

Engine::Objects::Object* Engine::Objects::Object::ToggleClicked(GLuint* index)
{
	Clicked = (_VAO == *index);
	return this;
}

Engine::Objects::Object* Engine::Objects::Object::SetClicked(Generic::Dictionary<short, bool> mouseKeys)
{
	Clicked = mouseKeys[MK_L];
	return this;
}

bool Engine::Objects::Object::IsClicked(glm::vec4 world_object)
{
	return (_colorId == world_object);
}
