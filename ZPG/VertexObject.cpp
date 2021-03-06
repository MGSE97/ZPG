#include "VertexObject.h"
#include <vector>
#include <winerror.h>

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

Engine::Components::Objects::VertexObject::VertexObject(Application::Materials::StandartMaterial* material, const float* points, int size, int dimensions, bool normals, bool uvs, bool faces, const unsigned int* indices, int indicesSize)
{
	Transform = new Objects::Transform();
	_Indices = new Generic::Collection<unsigned int>();
	_attribute_id = 0;
	Dimensions = dimensions;
	Size = size;
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

	const int partSize = 3 + (normals ? 3 : 0) + (uvs ? 2 : 0);

	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, size * partSize * sizeof(float), points, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, partSize * sizeof(float), (GLvoid*)0);

	if (normals)
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, partSize * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	}

	if (uvs)
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, partSize * sizeof(float), (GLvoid*)((partSize-2) * sizeof(float)));
	}

	if(faces && indices != nullptr)
	{
		for (int i = 0; i < indicesSize; i++)
			_Indices->Add(indices[i]);
	}
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

Engine::Components::Objects::VertexObject::VertexObject(Application::Materials::StandartMaterial* material, aiMesh* mesh, int dimensions)
{
	Transform = new Objects::Transform(); 
	_Indices = new Generic::Collection<unsigned int>();
	_attribute_id = 0;
	Dimensions = dimensions;
	Size = mesh->mNumVertices;
	_Id = ++_object_id;

	Vertex* pVertices = new Vertex[mesh->mNumVertices]();
	std::memset(pVertices, 0, sizeof(Vertex)* mesh->mNumVertices);

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		if (mesh->HasPositions())
		{
			pVertices[i].Position[0] = mesh->mVertices[i].x;
			pVertices[i].Position[1] = mesh->mVertices[i].y;
			pVertices[i].Position[2] = mesh->mVertices[i].z;
		}
		if (mesh->HasNormals())
		{
			pVertices[i].Normal[0] = mesh->mNormals[i].x;
			pVertices[i].Normal[1] = mesh->mNormals[i].y;
			pVertices[i].Normal[2] = mesh->mNormals[i].z;
		}
		if (mesh->HasTextureCoords(0))
		{
			pVertices[i].UV[0] = mesh->mTextureCoords[0][i].x;
			pVertices[i].UV[1] = mesh->mTextureCoords[0][i].y;
		}
		if(mesh->HasTangentsAndBitangents())
		{
			pVertices[i].Tangent[0] = mesh->mTangents[i].x;
			pVertices[i].Tangent[1] = mesh->mTangents[i].y;
			pVertices[i].Tangent[2] = mesh->mTangents[i].z;


			pVertices[i].Bitangent[0] = mesh->mTangents[i].x;
			pVertices[i].Bitangent[1] = mesh->mTangents[i].y;
			pVertices[i].Bitangent[2] = mesh->mTangents[i].z;
		}
	}

	if(mesh->HasFaces())
	{
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				_Indices->Add(face.mIndices[j]);
		}
	}

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh->mNumVertices * sizeof(Vertex), pVertices, GL_STATIC_DRAW);

	if (mesh->HasPositions())
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	}

	if (mesh->HasNormals())
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(float)));
	}

	if (mesh->HasTextureCoords(0))
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(float)));
	}

	if(mesh->HasTangentsAndBitangents())
	{
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(float)));

		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(11 * sizeof(float)));
	}

	Material = material;

	delete[] pVertices;
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
	Transform->Use(Material->Shader);

	glStencilFunc(GL_ALWAYS, _VAO, 0xFF);
	glBindVertexArray(_VAO);
	if(_Indices == nullptr || _Indices->empty())
		// draw triangles
		glDrawArrays(GL_TRIANGLES, 0, Size);
	else
		// draw faces
		glDrawElements(GL_TRIANGLES, _Indices->size(), GL_UNSIGNED_INT, _Indices->data());

	return this;
}

Engine::Components::Objects::VAOConfig::VAOConfig() : Size(0), Offset(0)
{
}

Engine::Components::Objects::VAOConfig::VAOConfig(int size, int offset) : Size(size), Offset(offset)
{
}
