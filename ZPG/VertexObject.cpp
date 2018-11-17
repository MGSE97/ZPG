#include "VertexObject.h"
#include <vector>

int Engine::Components::Objects::VertexObject::_object_id = 0;

Engine::Components::Objects::VertexObject* Engine::Components::Objects::VertexObject::Add(int size, int offset)
{

	/*glEnableVertexAttribArray(_attribute_id); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glVertexAttribPointer(_attribute_id++, *Dimensions, GL_FLOAT, GL_FALSE, size * sizeof(float), (GLvoid*)offset);*/
	glEnableVertexAttribArray(_attribute_id);
	glVertexAttribPointer(_attribute_id, Dimensions, GL_FLOAT, GL_FALSE, size, (void*)offset);
	_attribute_id++;
	//VAOs->Add(new VertexAttributeObject(VAOi++, VBO, *Dimensions, size, offset));
	return this;
}

Engine::Components::Objects::VertexObject::VertexObject(Graphics::Material* material, const float* points, int size, int dimensions, Generic::Collection<VAOConfig*>* configs)
{
	Transform = new Objects::Transform();
	_attribute_id = 0;
	Dimensions = dimensions;
	Size = size/(dimensions*2);
	_Id = ++_object_id;
	/*glGenBuffers(1, &_VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

	glGenVertexArrays(1, &_VAO); //generate the VAO
	glBindVertexArray(_VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glVertexAttribPointer(_attribute_id, *Dimensions, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);
	_attribute_id++;*/

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), points, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3*sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));

	/*VBO = new VertexBufferObject(points, size);
	VAOs = new Generic::Collection<VertexAttributeObject*>();*/
	/*if (configs != nullptr)
		for(auto config: *configs)
		/*{
			glGenVertexArrays(1, &_VAO); //generate the VAO
			glBindVertexArray(_VAO); //bind the VAO
			glEnableVertexAttribArray(_attribute_id++); //enable vertex attributes
		}*/
		/*	Add(config->Size, config->Offset);
	/*_attribute_id = 0;
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	if (configs != nullptr)
		for (auto config : *configs)
		{
			glVertexAttribPointer(_attribute_id++, *Dimensions, GL_FLOAT, GL_FALSE, config->Size * sizeof(float), (GLvoid*)(config->Offset));
		}*/
	Material = material;
}

Engine::Components::Objects::VertexObject::~VertexObject()
{
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	/*delete _VBO;
	delete _VAO;*/
	delete Material;
}

Engine::Components::Objects::VertexObject* Engine::Components::Objects::VertexObject::Draw()
{
	// use material
	Material->Use();
	Transform->Use(Material->Program->Shaders->Get("vertex"), Material->Program);

	glStencilFunc(GL_ALWAYS, _VAO, 0xFF);
	glBindVertexArray(_VAO);
	// draw triangles
	glDrawArrays(GL_TRIANGLES, 0, Size);

	return this;
}

Engine::Components::Objects::VAOConfig::VAOConfig() : Size(0), Offset(0)
{
}

Engine::Components::Objects::VAOConfig::VAOConfig(int size, int offset) : Size(size), Offset(offset)
{
}
