#pragma once

#include "object.h"

class Screen;

class Camera : public Object {
// Constructors
public:
  Camera();

// Methods
public:
  void refreshAttributes(Screen *screen);
  void moveTo(const glm::vec3 newPosition);
  void rotateTo(const glm::vec3 eulerAngles);

  glm::mat4 getViewMatrix() const { return viewMatrix; }
  glm::mat4 getPerspectiveMatrix() const { return perspectiveMatrix; }

protected:
  void refreshMatrices();

// Attributes
private:
  float fovY = 90;
  float aspectRatio = 1.0f;

  float nearPlane = 0.1f;
  float farPlane = 100.0f;

  glm::mat4 viewMatrix;
  glm::mat4 perspectiveMatrix;
};
