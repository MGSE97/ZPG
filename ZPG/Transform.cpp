#define GLM_ENABLE_EXPERIMENTAL
#include "Transform.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>

Engine::Components::Objects::Transform::Transform()
{
	_position = glm::vec3(0, 0, 0);
	_rotation = glm::vec3(0, 0, 0);
	_scale = glm::vec3(1, 1, 1);
	_changed = true;
}

Engine::Components::Objects::Transform* Engine::Components::Objects::Transform::Use(Graphics::Shader* shader)
{
	// Build new Model matrix
	if (_changed)
	{
		auto rotationMatrix =
			glm::rotate(glm::mat4(1), glm::radians(_rotation.x), glm::vec3(1, 0, 0)) *
			glm::rotate(glm::mat4(1), glm::radians(_rotation.y), glm::vec3(0, 1, 0)) *
			glm::rotate(glm::mat4(1), glm::radians(_rotation.z), glm::vec3(0, 0, 1));
		_modelMatrix =
			glm::translate(glm::mat4(1), _position) *
			rotationMatrix *
			glm::scale(glm::mat4(1), _scale);
	}

	shader->SendUniform("modelMatrix", &_modelMatrix);

	return this;
}

Engine::Components::Objects::Transform* Engine::Components::Objects::Transform::Position(glm::vec3 position, bool set)
{
	if (set)
		_position = position;
	else
		_position += position;
	_changed = true;
	return this;
}

Engine::Components::Objects::Transform* Engine::Components::Objects::Transform::Rotation(glm::vec3 rotation, bool set)
{
	if (set)
		_rotation = rotation;
	else
		_rotation += rotation;
	_changed = true;
	return this;
}

Engine::Components::Objects::Transform* Engine::Components::Objects::Transform::Scale(glm::vec3 scale, bool set)
{
	if (set)
		_scale = scale;
	else
		_scale += scale;
	_changed = true;
	return this;
}

Engine::Components::Objects::Transform* Engine::Components::Objects::Transform::Position(int x, int y, int z, bool set)
{
	Position(glm::vec3(x, y, z), set);
	return this;
}

Engine::Components::Objects::Transform* Engine::Components::Objects::Transform::Rotation(int x, int y, int z, bool set)
{
	Rotation(glm::vec3(x, y, z), set);
	return this;
}

Engine::Components::Objects::Transform* Engine::Components::Objects::Transform::Scale(int x, int y, int z, bool set)
{
	Scale(glm::vec3(x, y, z), set);
	return this;
}

Engine::Components::Objects::Transform* Engine::Components::Objects::Transform::Scale(int scale, bool set)
{
	Scale(glm::vec3(static_cast<float>(scale)), set);
	return this;
}

Engine::Components::Objects::Transform* Engine::Components::Objects::Transform::Scale(float scale, bool set)
{
	Scale(glm::vec3(scale), set);
	return this;
}

Engine::Components::Objects::Transform* Engine::Components::Objects::Transform::Position(double x, double y, double z, bool set)
{
	Position(glm::vec3(x, y, z), set);
	return this;
}

Engine::Components::Objects::Transform* Engine::Components::Objects::Transform::Rotation(double x, double y, double z, bool set)
{
	Rotation(glm::vec3(x, y, z), set);
	return this;
}

Engine::Components::Objects::Transform* Engine::Components::Objects::Transform::Scale(double x, double y, double z, bool set)
{
	Scale(glm::vec3(x, y, z), set);
	return this;
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

Engine::Components::Objects::Transform* Engine::Components::Objects::Transform::RotateAround(glm::vec3 point, float angle, glm::vec3 axis)
{
	auto dir = _position - point;
	auto rot = glm::angleAxis(glm::radians(angle), axis);
	dir = rot * dir;
	auto myRot = glm::quat(glm::radians(_rotation));
	_rotation = glm::degrees(glm::eulerAngles(myRot*(glm::inverse(myRot)*rot*myRot)));
	//_rotation += axis * angle;
	Position(point + dir, true);
	return this;
}

Engine::Components::Objects::Transform* Engine::Components::Objects::Transform::Position(float x, float y, float z, bool set)
{
	Position(glm::vec3(x, y, z), set);
	return this;
}

Engine::Components::Objects::Transform* Engine::Components::Objects::Transform::Rotation(float x, float y, float z, bool set)
{
	Rotation(glm::vec3(x, y, z), set);
	return this;
}

Engine::Components::Objects::Transform* Engine::Components::Objects::Transform::Scale(float x, float y, float z, bool set)
{
	Scale(glm::vec3(x, y, z), set);
	return this;
}
