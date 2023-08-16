#include "custom_cube.h"

void CustomCube::update(float deltaTime) {
  test += deltaTime * 90;

  rotateTo({ test, test, test });
}