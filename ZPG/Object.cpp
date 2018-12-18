#include "Object.h"
#include "IInputHandler.h"

int Engine::Components::Objects::Object::_id = 0;

Engine::Components::Objects::Object::Object(Application::Materials::StandartMaterial* material, aiMesh* mesh, int dimensions):
	VertexObject(material, mesh, dimensions)
{
	Clicked = false;
	Id = _id++;
}

Engine::Components::Objects::Object::Object(Application::Materials::StandartMaterial* material, std::vector<float>* points, int dimensions, bool normals, bool uvs, bool faces, std::vector<unsigned int>* indices) :
	VertexObject(material, points->data(), points->size()/(3+(normals?3:0)+(uvs?2:0)), dimensions, normals, uvs, faces, indices->data(), indices->size())
{
	Clicked = false;
	Id = _id++;
}

Engine::Components::Objects::Object::Object(Application::Materials::StandartMaterial* material, const float* points, int size, int dimensions, bool normals, bool uvs, bool faces, const unsigned int* indices, int indicesSize) :
	VertexObject(material, points, size, dimensions, normals, uvs, faces, indices, indicesSize)
{
	Clicked = false; 
	Id = _id++;
}

Engine::Components::Objects::Object::~Object()
= default;

Engine::Components::Objects::Object* Engine::Components::Objects::Object::ToggleClicked(GLuint* index)
{
	Clicked = (_VAO == *index);
	return this;
}

Engine::Components::Objects::Object* Engine::Components::Objects::Object::SetClicked(Generic::Dictionary<short, bool> mouseKeys)
{
	Clicked = mouseKeys[MK_L];
	return this;
}

bool Engine::Components::Objects::Object::IsClicked(GLuint* worldObjectId)
{
	return (_VBO == *worldObjectId);
}
