#include "Sphere.h"
#include "VertexAttributeObject.h"

Engine::Objects::Sphere::~Sphere()
{
	Object::~Object();
}

Engine::Objects::Sphere::Sphere(Application::Materials::StandartMaterial* material, const float* points, int size, int dimensions):
	Object(material, points, size, dimensions, true)
{
	
}

Engine::Objects::Sphere* Engine::Objects::Sphere::Draw()
{
	Object::Draw();
	return this;
}
