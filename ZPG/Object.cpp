#include "Object.h"
#include "Program.h"
#include "IInputHandler.h"

int Engine::Objects::Object::_id = 0;

Engine::Objects::Object::Object(Components::Graphics::Material* material, const float* points, int size, int dimensions, int startArrayIndex) :
	VertexObject(material, points, size, dimensions, &((new Generic::Collection<Components::Objects::VAOConfig*>())
		->Add(new Engine::Components::Objects::VAOConfig(0, startArrayIndex))
		))
{
	Clicked = false;
	Id = _id++;
	/*ModelMatrix = new glm::mat4(1.f);
	Material->Values->Add(new Engine::Components::Graphics::MaterialValue<glm::mat4>(
		Material->Program->Shaders->Get("vertex"), "modelMatrix", ModelMatrix
	));*/
}

Engine::Objects::Object::Object(Components::Graphics::Material* material, const float* points, int size, int dimensions, Generic::Collection<Components::Objects::VAOConfig*> configs) :
	VertexObject(material, points, size, dimensions, &configs)
{
	Clicked = false; 
	Id = _id++;
	/*ModelMatrix = new glm::mat4(1.f);
	Material->Values->Add(new Engine::Components::Graphics::MaterialValue<glm::mat4>(
		Material->Program->Shaders->Get("vertex"), "modelMatrix", ModelMatrix
	));*/
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

bool Engine::Objects::Object::IsClicked(GLuint* worldObjectId)
{
	return (_VBO == *worldObjectId);
}
