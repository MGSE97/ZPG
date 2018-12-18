#include "GenericOctahedon.h"
#include <glm/vec3.hpp>


Engine::Objects::GenericOctahedon::GenericOctahedon()
{
		vertices = new std::vector<float>;
		indices = new std::vector<unsigned int>;

		// build vertex array

		// R
		vertices->push_back(1.f);
		vertices->push_back(0.f);
		vertices->push_back(0.f);

		// L
		vertices->push_back(-1.f);
		vertices->push_back(0.f);
		vertices->push_back(0.f);

		// T
		vertices->push_back(0.f);
		vertices->push_back(1.f);
		vertices->push_back(0.f);

		// Y
		vertices->push_back(0.f);
		vertices->push_back(-1.f);
		vertices->push_back(0.f);

		// B
		vertices->push_back(0.f);
		vertices->push_back(0.f);
		vertices->push_back(1.f);

		// F
		vertices->push_back(0.f);
		vertices->push_back(0.f);
		vertices->push_back(-1.f);

		// build index array linking sets of three vertices into triangles

		// RTB
		indices->push_back(0);
		indices->push_back(2);
		indices->push_back(4);

		// RBY
		indices->push_back(0);
		indices->push_back(4);
		indices->push_back(3);

		// RYF
		indices->push_back(0);
		indices->push_back(3);
		indices->push_back(5);

		// RFT
		indices->push_back(0);
		indices->push_back(5);
		indices->push_back(2);

		// LBT
		indices->push_back(1);
		indices->push_back(4);
		indices->push_back(2);

		// LTF
		indices->push_back(1);
		indices->push_back(2);
		indices->push_back(5);

		// LFY
		indices->push_back(1);
		indices->push_back(5);
		indices->push_back(3);

		// LYB
		indices->push_back(1);
		indices->push_back(3);
		indices->push_back(4);
}


Engine::Objects::GenericOctahedon::~GenericOctahedon()
{
	delete vertices;
	delete indices;
}

Engine::Objects::GenericOctahedon* Engine::Objects::GenericOctahedon::GetInstance()
{
	static GenericOctahedon _instance;
	return &_instance;
}
