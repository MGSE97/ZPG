#include "Sphere.h"
#include "VertexAttributeObject.h"

Engine::Objects::Sphere::~Sphere()
{
	Object::~Object();
}

Engine::Objects::Sphere::Sphere(Components::Graphics::Material* material, const float* points, int size, int dimensions):
	Object(material, points, size, dimensions, (new Generic::Collection<Components::Objects::VAOConfig*>())
		->Add(new Components::Objects::VAOConfig(dimensions*2, 0))
		.Add(new Components::Objects::VAOConfig(dimensions*2, dimensions))
	)
{
	
}

Engine::Objects::Sphere* Engine::Objects::Sphere::Draw()
{
	Object::Draw();
	return this;
}
