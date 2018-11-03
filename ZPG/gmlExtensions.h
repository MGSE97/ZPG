#pragma once
#include <glm/vec3.hpp>


namespace glm
{
	inline float simplify(float vector, float value = 1.f)
	{
		if (vector > 0)
			return value;
		if (vector < 0)
			return -value;
		return 0.f;
	}

	inline vec3 simplify(glm::vec3 vector, float value = 1.f)
	{
		auto v = vector;
		v.x = simplify(v.x,value);
		v.y = simplify(v.y, value);
		v.z = simplify(v.z, value);
		return v;
	}
	inline vec2 simplify(glm::vec2 vector, float value = 1.f)
	{
		auto v = vector;
		v.x = simplify(v.x, value);
		v.y = simplify(v.y, value);
		return v;
	}

	inline vec2 rotateAround(vec2 center, vec2 point, float angle) {

		return vec2(cos(angle) * (point.x - center.x) - sin(angle) * (point.y - center.y) + center.x,
					sin(angle) * (point.x - center.x) + cos(angle) * (point.y - center.y) + center.y);
	}

	vec3 Up(0, 1, 0);
	vec3 Down(0, -1, 0);
	vec3 Left(-1, 0, 0);
	vec3 Right(1, 0, 0);
	vec3 Front(0, 0, -1);
	vec3 Back(0, 0, 1);
}

