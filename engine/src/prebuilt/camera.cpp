#include "prebuilt/camera.h"
#include "screen.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : Object() {
  refreshMatrices();
}

// public

void Camera::refreshAttributes(Screen *screen) {
  aspectRatio = screen->aspectRatio;

  refreshMatrices();
}

void Camera::moveTo(const glm::vec3 newPosition){
  Object::moveTo(newPosition);

  refreshMatrices();
}

void Camera::rotateTo(const glm::vec3 newRotation){
  Object::rotateTo(newRotation);

  refreshMatrices();
}

// protected

void Camera::refreshMatrices() {
  glm::mat4 positionInMat4 = glm::translate(glm::mat4(1.0f), position);

  viewMatrix = getRotationMatrix() * positionInMat4;
  perspectiveMatrix = glm::perspective(glm::radians(fovY), aspectRatio, nearPlane, farPlane);
}