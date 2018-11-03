#include "VertexAttributeObject.h"
#include <cstddef>
#include "VertexBufferObject.h"


Engine::Components::Objects::VertexAttributeObject::VertexAttributeObject(int index, VertexBufferObject* VBO, int dimensions, int size, int offset)
{
	Dimensions = dimensions;
	Index = index;
	Offset = offset;
	Size = size;
	if (index == 0)
	{
		glGenVertexArrays(VBO->GetId(), &_VAO); //generate the VAO
		glBindVertexArray(_VAO); //bind the VAO
		glBindBuffer(GL_ARRAY_BUFFER, VBO->Get());
	};
	glEnableVertexAttribArray(index); //enable vertex attributes
	glVertexAttribPointer(index, dimensions, GL_FLOAT, GL_FALSE, size*sizeof(float), (GLvoid*)offset);
}


Engine::Components::Objects::VertexAttributeObject::~VertexAttributeObject()
{
	delete &_VAO;
	delete &Dimensions;
	delete &Index;
	delete &Offset;
	delete &Size;
}

GLuint Engine::Components::Objects::VertexAttributeObject::Get()
{
	return _VAO;
}
