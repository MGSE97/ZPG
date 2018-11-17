#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x2.hpp>
#include "Program.h"

namespace Engine
{
	namespace Components
	{
		namespace Objects
		{
			class Transform
			{
				glm::vec3 _position;
				glm::vec3 _rotation;
				glm::vec3 _scale;
				glm::mat4 _modelMatrix;
				bool _changed;
			public:
				Transform();
				void Use(Graphics::Shader* shader);
				void Position(glm::vec3 position, bool set = false);
				void Rotation(glm::vec3 rotation, bool set = false);
				void Scale(glm::vec3 scale, bool set = false);
				void Position(int x, int y, int z, bool set = false);
				void Rotation(int x, int y, int z, bool set = false);
				void Scale(int x, int y, int z, bool set = false);
				void Scale(int scale, bool set = false);
				void Position(float x, float y, float z, bool set = false);
				void Rotation(float x, float y, float z, bool set = false);
				void Scale(float x, float y, float z, bool set = false);
				void Scale(float scale, bool set = false);
				glm::vec3* GetPosition(); 
				glm::vec3* GetRotation();
				glm::vec3* GetScale();
			};

		}
	}
}
