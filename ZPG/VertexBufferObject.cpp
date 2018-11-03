#include "VertexBufferObject.h"
#include <cstddef>

int Engine::Components::Objects::VertexBufferObject::_id = 0;

Engine::Components::Objects::VertexBufferObject::VertexBufferObject(float* points, int size)
{
	_Id = ++_id;
	glGenBuffers(_Id, &_VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), points, GL_STATIC_DRAW);
}


Engine::Components::Objects::VertexBufferObject::~VertexBufferObject()
{
	delete &_Id;
	delete &_VBO;
}

GLuint Engine::Components::Objects::VertexBufferObject::Get()
{
	return _VBO;
}

int Engine::Components::Objects::VertexBufferObject::GetId()
{
	return _Id;
}
