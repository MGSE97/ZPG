#include "Mesh.h"
#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags
#include "StandartMaterial.h"
#include "Texture.h"
#include <GLFW/glfw3.h>
#include <iostream>
#define DEBUG

Engine::Components::Objects::Mesh::Mesh()
{
	Components = new Generic::Collection<Object*>;
}

Engine::Components::Objects::Mesh* Engine::Components::Objects::Mesh::Load(std::string directoryName, std::string fileName, int importOptions)
{
	Assimp::Importer importer;
	/*unsigned int importOptions = aiProcess_Triangulate;
		/*  aiProcess_OptimizeMeshes              // slouèení malých plošek
		| aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodnì duplikuje
		| aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
		| aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy*/


	//aiProcess_GenNormals/ai_Process_GenSmoothNormals - vypocet normal s jemnych prechodem v pripade, ze objekt neobsahuje normaly

	auto start = glfwGetTime();
	#ifdef DEBUG
		std::cout << "Mesh.Load " << fileName << " "<< glfwGetTime() << " s\t> Begin" << std::endl;
	#endif
	const aiScene* scene = importer.ReadFile(directoryName+fileName, importOptions);
	#ifdef DEBUG
		std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> File readed" << std::endl;
	#endif
	if (scene) { //pokud bylo nacteni uspesne
		auto materials = new Generic::Collection<Application::Materials::StandartMaterial*>();
		for (unsigned int i = 0; i < scene->mNumMaterials; i++)                       //Materials
		{
			const aiMaterial* mat = scene->mMaterials[i];


			aiString name;
			aiGetMaterialString(mat, AI_MATKEY_NAME, &name);
			
			#ifdef DEBUG
				std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> Material " << i << " " << name.C_Str() << std::endl;
			#endif

			aiColor4D d;

			float shininess;
			if (AI_SUCCESS != aiGetMaterialFloat(mat, AI_MATKEY_SHININESS, &shininess))
				shininess = 32.f;
			#ifdef DEBUG
				std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> Material " << i << " Shininess "<< shininess << std::endl;
			#endif

			glm::vec3 ambient = glm::vec3(1.f, 1.f, 1.f);
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &d))
				ambient = glm::vec3(d.r, d.g, d.b);
			#ifdef DEBUG
				std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> Material " << i << " Ambient" << std::endl;
			#endif

			glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
				diffuse = glm::vec3(d.r, d.g, d.b);
			#ifdef DEBUG
				std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> Material " << i << " Diffuse" << std::endl;
			#endif

			glm::vec3 specular = glm::vec3(1.f, 1.f, 1.f);
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &d))
				specular = glm::vec3(d.r, d.g, d.b);
			#ifdef DEBUG
				std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> Material " << i << " Specular" << std::endl;
			#endif

			glm::vec3 emissive = glm::vec3(1.f, 1.f, 1.f);
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_EMISSIVE, &d))
				emissive = glm::vec3(d.r, d.g, d.b); 
			#ifdef DEBUG
				std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> Material " << i << " Emissive" << std::endl;
			#endif

				int mode;
				if (AI_SUCCESS != aiGetMaterialInteger(mat, AI_MATKEY_SHADING_MODEL, &mode))
					mode = 1;
				#ifdef DEBUG
					std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> Material " << i << " Illumination mode " << mode << std::endl;
				#endif

			auto sm = new Application::Materials::StandartMaterial();
			sm->Light.AmbientColor = ambient;
			sm->Light.DiffuseColor = diffuse;
			sm->Light.SpecularColor = specular;
			sm->Light.SpecularSize = shininess;
			sm->Light.AmbientStrength = 0.01f;
			if(mode == 0)
			{
				sm->Light.UseLighting = false;
				sm->Color = glm::vec4(diffuse, 1.0);
			}
			for (unsigned int j = 0; j < mat->GetTextureCount(aiTextureType_DIFFUSE); j++)
			{
				#ifdef DEBUG
					std::cout << "Mesh.Load " << fileName<<" " << glfwGetTime() << " s\t> Material " << i << " Texture Diffuse "<<j << std::endl;
				#endif

				aiString str;
				mat->GetTexture(aiTextureType_DIFFUSE, j, &str);
				if(str.length > 0)
				{
					#ifdef DEBUG
						std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> Material " << i << " Texture Diffuse " << j << " '" << str.C_Str() << "'" << " Loading" << std::endl;
					#endif

					auto texture = Graphics::Texture::Load(directoryName + str.C_Str());
					#ifdef DEBUG
						std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> Material " << i << " Texture Diffuse " << j << " '" << str.C_Str() << "'" << " Loaded" << std::endl;
					#endif

					sm->HasDiffuseTexture = true;
					sm->Textures->Add("diffuse", texture);
				}
				break;
			}
			for (unsigned int j = 0; j < mat->GetTextureCount(aiTextureType_HEIGHT); j++)
			{
				#ifdef DEBUG
					std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> Material " << i << " Texture Normals " << j << std::endl;
				#endif

				aiString str;
				mat->GetTexture(aiTextureType_HEIGHT, j, &str);
				if (str.length > 0)
				{
					#ifdef DEBUG
						std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> Material " << i << " Texture Normals " << j << " '" << str.C_Str() << "'" << " Loading" << std::endl;
					#endif

					auto texture = Graphics::Texture::Load(directoryName + str.C_Str());
					#ifdef DEBUG
						std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> Material " << i << " Texture Normals	 " << j << " '" << str.C_Str() << "'" << " Loaded" << std::endl;
					#endif

					sm->HasNormalTexture = true;
					sm->Textures->Add("normal", texture);
				}
				break;
			}
			materials->Add(sm);
		}
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)                      //Objects
		{
			#ifdef DEBUG
				std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> Mesh " << i << std::endl;
			#endif

			aiMesh* mesh = scene->mMeshes[i];
			#ifdef DEBUG
				std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> Mesh " << i << " Loading"<< std::endl;
			#endif

			Components->Add(new Object(materials->at(mesh->mMaterialIndex), mesh, 3));
			#ifdef DEBUG
				std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> Mesh " << i << " Loaded" << std::endl;
			#endif
		}
		#ifdef DEBUG
			std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> End" << std::endl;
		#endif
		std::cout << "Mesh.Load " << fileName << " " << glfwGetTime() << " s\t> Finished in " << glfwGetTime() - start << " s" << std::endl;
	}

	return this;
}


Engine::Components::Objects::Mesh::~Mesh()
{
}
