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
				Transform* Use(Graphics::Shader* shader);
				Transform* Position(glm::vec3 position, bool set = false);
				Transform* Rotation(glm::vec3 rotation, bool set = false);
				Transform* Scale(glm::vec3 scale, bool set = false);
				Transform* Position(int x, int y, int z, bool set = false);
				Transform* Rotation(int x, int y, int z, bool set = false);
				Transform* Scale(int x, int y, int z, bool set = false);
				Transform* Scale(int scale, bool set = false);
				Transform* Position(float x, float y, float z, bool set = false);
				Transform* Rotation(float x, float y, float z, bool set = false);
				Transform* Scale(float x, float y, float z, bool set = false);
				Transform* Scale(float scale, bool set = false);
				Transform* Position(double x, double y, double z, bool set = false);
				Transform* Rotation(double x, double y, double z, bool set = false);
				Transform* Scale(double x, double y, double z, bool set = false);
				glm::vec3* GetPosition(); 
				glm::vec3* GetRotation();
				glm::vec3* GetScale();
				Transform* RotateAround(glm::vec3 point, float angle, glm::vec3 normal);
			};

		}
	}
}
