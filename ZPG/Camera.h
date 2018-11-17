#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Observable.h"
#include <map>

namespace Engine
{
	namespace Components
	{
		class Scene;

		class Camera : public Observable<Camera>
		{
		public:
			Camera();
			~Camera();
			glm::vec3* Position;
			glm::vec3* Direction;
			glm::vec3* Up;
			glm::vec3* Right;
			glm::vec3* Front;
			glm::mat4* Projection;
			glm::mat4* Get();
			Camera* UpdateVectors();
			Camera* Update();
			Camera* SetPosition(glm::vec3* position);
			Camera* SetDirection(glm::vec3* direction);
			Camera* SetUp(glm::vec3* up);
			Camera* SetActive(Scene* scene);
			Camera* Use(Graphics::Shader* program);
			glm::mat4* Value;
		};
	}
}

