#include "Object.h"
#include "IInputHandler.h"

int Engine::Objects::Object::_id = 0;

Engine::Objects::Object::Object(Components::Graphics::Material* material, std::vector<float>* points, int dimensions, bool normals, bool uvs) :
	VertexObject(material, points->data(), points->size()/(3+(normals?3:0)+(uvs?2:0)), dimensions, normals, uvs)
{
	Clicked = false;
	Id = _id++;
}

Engine::Objects::Object::Object(Components::Graphics::Material* material, const float* points, int size, int dimensions, bool normals, bool uvs) :
	VertexObject(material, points, size, dimensions, normals, uvs)
{
	Clicked = false; 
	Id = _id++;
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
