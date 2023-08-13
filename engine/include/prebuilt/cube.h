#pragma once

#include <object.h>

class Cube : public Object
{
public:
  Cube(float size_x, float size_y, float size_z);
  Cube(glm::vec3 size) : Cube(size.x, size.y, size.z) {}
  Cube(float size): Cube(size, size, size) {}
};