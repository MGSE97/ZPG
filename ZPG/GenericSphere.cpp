#define _USE_MATH_DEFINES
#include <cmath>
#include "GenericSphere.h"
#include "Assets/Models/2/spheref.h"
#include <glm/vec2.hpp>

Engine::Objects::GenericSphere::GenericSphere(float radius, unsigned rings, unsigned sectors)
{
	vertices = new std::vector<float>;
	normals = new std::vector<float>;
	texcoords = new std::vector<float>;
	array = new std::vector<float>;
	indices = new std::vector<unsigned short>;

	/*const float c = sqrt(2880);
	const float t = 1. / c;
	int u = 0, v = 0, a = 0;*/
	array->resize(2880 * 8);
	for(int i = 0; i < 17280; i++)
	{
		array->push_back(sphere[i]);
		if (i % 6 == 5)
		{
			/*if(u > c)
			{
				u = 0;
				v++;
			}
			array->push_back(u * t); 
			array->push_back(v * t);
			u++;*/
			auto uv = glm::vec2((atan2(sphere[i - 4], sphere[i - 5]) / M_PI + 1.0) *0.5, (asin(sphere[i - 3]) / M_PI + 0.5));
			array->push_back(uv.x);
			array->push_back(uv.y);
		}
	}
	return;

	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	int r, s;

	vertices->resize(rings * sectors * 3);
	normals->resize(rings * sectors * 3);
	texcoords->resize(rings * sectors * 2);
	array->reserve(rings * sectors * 8);
	for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
		float const y = sin(-M_PI + M_PI * r * R);
		float const x = cos(2.0 * M_PI * s * S) * sin(M_PI * r * R);
		float const z = sin(2.0 * M_PI * s * S) * sin(M_PI * r * R);
		/*const float y = -cos(M_PI * r * R);
		const float w = sqrt(1.0 - y*y);
		const float x = w * sin(2.0 * M_PI * s * S);
		const float z = w * cos(2.0 * M_PI * s * S);*/

		vertices->push_back(x*radius);
		vertices->push_back(y*radius);
		vertices->push_back(z*radius);

		normals->push_back(x);
		normals->push_back(y);
		normals->push_back(z);

		texcoords->push_back(s * S);
		texcoords->push_back(r * R);


		array->push_back(x*radius);
		array->push_back(y*radius);
		array->push_back(z*radius);

		array->push_back(x);
		array->push_back(y);
		array->push_back(z);

		array->push_back(s * S);
		array->push_back(r * R);

		/*array->push_back(*(vertices->end() - 3));
		array->push_back(*(vertices->end() - 2));
		array->push_back(*(vertices->end() - 1));

		array->push_back(*(normals->end() - 3));
		array->push_back(*(normals->end() - 2));
		array->push_back(*(normals->end() - 1));

		array->push_back(*(texcoords->end() - 2));
		array->push_back(*(texcoords->end() - 1));*/
	}

	indices->resize(rings * sectors * 4);
	auto i = indices->begin();
	for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
		*i++ = r * sectors + s;
		*i++ = r * sectors + (s + 1);
		*i++ = (r + 1) * sectors + (s + 1);
		*i++ = (r + 1) * sectors + s;
	}
}

Engine::Objects::GenericSphere::~GenericSphere()
{
	delete vertices;
	delete normals;
	delete texcoords;
	delete indices;
	delete array;
}
