#include "Camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Scene.h"


Engine::Components::Camera::Camera()
{
	Position = new glm::vec3(1.f, 1.f, 1.f);
	Direction = new glm::vec3(0.f, 0.f, 0.f);
	Up = new glm::vec3(0.f, 0.f, 1.f);
	Front = new glm::vec3(1.0, 1.0, 0.0);
	Right = new glm::vec3(0.0, 1.0, 1.0);
	Value = Get();
}


Engine::Components::Camera::~Camera()
{
	delete Value;
}

glm::mat4* Engine::Components::Camera::Get()
{
	return new glm::mat4(lookAt(*Position, *Direction, *Up));
}

Engine::Components::Camera* Engine::Components::Camera::UpdateVectors()
{
	/*Front->x = Direction->x;
	Front->z = Direction->z;
	Front->y = Position->y;*/
	/**Up = *Position + glm::normalize(*Up - *Position);
	*Direction = *Position + glm::normalize(*Direction - *Position);*/
	*Front = glm::normalize(*Position - *Direction);

	*Right = glm::normalize(glm::cross(*Up, *Front));

	return this;
}

Engine::Components::Camera* Engine::Components::Camera::Update()
{
	*Value = *Get();
	UpdateVectors();
	Notify();
	return this;
}

Engine::Components::Camera* Engine::Components::Camera::SetPosition(glm::vec3* position)
{
	*Position = *position;
	Update();
	return this;
}

Engine::Components::Camera* Engine::Components::Camera::SetDirection(glm::vec3* direction)
{
	*Direction = *direction;
	Update();
	return this;
}

Engine::Components::Camera* Engine::Components::Camera::SetUp(glm::vec3* up)
{
	*Up = *up;
	Update();
	return this;
}

Engine::Components::Camera* Engine::Components::Camera::SetActive(Scene* scene)
{
	scene->SetActiveCamera(this);
	return this;
}

Engine::Components::Camera* Engine::Components::Camera::Use(Graphics::Shader* shader)
{
	if (shader != nullptr)
	{
		shader->SendUniform("viewMatrix", Value);
		shader->SendUniform("projectionMatrix", Projection);
		shader->SendUniform("cameraPos", Position);
	}
	return this;
}
