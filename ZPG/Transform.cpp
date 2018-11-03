
#include "Transform.h"

glm::mat4 Transform::GetMatrix() {

	return
		// Velikost
		glm::scale(
			// Rotace Z
			glm::rotate(
				// Rotace Y
				glm::rotate(
					// Rotace X
					glm::rotate(
						// Posun na pozici
						glm::translate(
							glm::mat4(1.f),
							Position
						),
						Rotation.x,
						glm::vec3(1, 0, 0)
					),
					Rotation.y,
					glm::vec3(0, 1, 0)
				),
				Rotation.z,
				glm::vec3(0, 0, 1)
			),
			Scale
		);
}

 Transform::Transform() {

}

 Transform::~Transform() {

}

