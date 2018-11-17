#include "Transform.h"
#include <glm/ext/matrix_transform.hpp>

Engine::Components::Objects::Transform::Transform()
{
	_position = glm::vec3(0, 0, 0);
	_rotation = glm::vec3(0, 0, 0);
	_scale = glm::vec3(1, 1, 1);
	_changed = true;
}

void Engine::Components::Objects::Transform::Use(Graphics::Shader* shader)
{
	// Build new Model matrix
	if(_changed)
		_modelMatrix =
		glm::scale(
			glm::translate(
				glm::rotate(
					glm::rotate(
						glm::rotate(
							glm::mat4(1), glm::radians(_rotation.x), glm::vec3(1,0,0)
						), glm::radians(_rotation.y), glm::vec3(0, 1, 0)
					), glm::radians(_rotation.z), glm::vec3(0, 0, 1)
				), _position
			),	_scale
		);

	shader->SendUniform("modelMatrix", &_modelMatrix);
}

void Engine::Components::Objects::Transform::Position(glm::vec3 position, bool set)
{
	if (set)
		_position = position;
	else
		_position += position;
	_changed = true;
}

void Engine::Components::Objects::Transform::Rotation(glm::vec3 rotation, bool set)
{
	if (set)
		_rotation = rotation;
	else
		_rotation += rotation;
	_changed = true;
}

void Engine::Components::Objects::Transform::Scale(glm::vec3 scale, bool set)
{
	if (set)
		_scale = scale;
	else
		_scale += scale;
	_changed = true;
}

void Engine::Components::Objects::Transform::Position(int x, int y, int z, bool set)
{
	Position(glm::vec3(x, y, z), set);
}

void Engine::Components::Objects::Transform::Rotation(int x, int y, int z, bool set)
{
	Rotation(glm::vec3(x, y, z), set);
}

void Engine::Components::Objects::Transform::Scale(int x, int y, int z, bool set)
{
	Scale(glm::vec3(x, y, z), set);
}

void Engine::Components::Objects::Transform::Scale(int scale, bool set)
{
	Scale(glm::vec3(scale), set);
}

void Engine::Components::Objects::Transform::Scale(float scale, bool set)
{
	Scale(glm::vec3(scale), set);
}

glm::vec3* Engine::Components::Objects::Transform::GetPosition()
{
	return &_position;
}

glm::vec3* Engine::Components::Objects::Transform::GetRotation()
{
	return &_rotation;
}

glm::vec3* Engine::Components::Objects::Transform::GetScale()
{
	return &_scale;
}

void Engine::Components::Objects::Transform::Position(float x, float y, float z, bool set)
{
	Position(glm::vec3(x, y, z), set);
}

void Engine::Components::Objects::Transform::Rotation(float x, float y, float z, bool set)
{
	Rotation(glm::vec3(x, y, z), set);
}

void Engine::Components::Objects::Transform::Scale(float x, float y, float z, bool set)
{
	Scale(glm::vec3(x, y, z), set);
}
