#pragma once

#include "prebuilt/cube.h"

class CustomCube : public Prebuilt::Cube
{
public:
  CustomCube(float size_x, float size_y, float size_z) : Prebuilt::Cube(size_x, size_y, size_z) {}
  void update(float deltaTime) override;

private:
  float test = 0;
};