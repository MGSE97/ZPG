#ifndef _TRANSFORM_H
#define _TRANSFORM_H


class Transform {
  public:
    glm::vec3 Position;

    glm::vec3 Rotation;

    glm::vec3 Scale;

    glm::mat4 GetMatrix();

     Transform();

     ~Transform();

};
#endif
