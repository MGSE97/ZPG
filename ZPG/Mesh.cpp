#include "Mesh.h"
#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags
#include "StandartMaterial.h"

Engine::Components::Objects::Mesh::Mesh()
{
	Components = new Generic::Collection<VertexObject*>;
}

Engine::Components::Objects::Mesh* Engine::Components::Objects::Mesh::Load(std::string fileName)
{
	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate;
		/*  aiProcess_OptimizeMeshes              // slouèení malých plošek
		| aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodnì duplikuje
		| aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
		| aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy*/


	//aiProcess_GenNormals/ai_Process_GenSmoothNormals - vypocet normal s jemnych prechodem v pripade, ze objekt neobsahuje normaly

	const aiScene* scene = importer.ReadFile(fileName, importOptions);

	if (scene) { //pokud bylo nacteni uspesne
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)                      //Objects
		{
			aiMesh* mesh = scene->mMeshes[i];
			Application::Materials::StandartMaterial* material = new Application::Materials::StandartMaterial();
			material->Light.AmbientStrength = 0.2f;
			Components->Add(new VertexObject(material, mesh, 3));
		}
	}

	return this;
}


Engine::Components::Objects::Mesh::~Mesh()
{
}
