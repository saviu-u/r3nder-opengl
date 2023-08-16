#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <array>
#include <map>

class Screen;

class Object{
public:
// constructors
  Object();
  ~Object();
// methods
  std::vector<float> worldFacesVerticesBuffer() const;
  std::vector<std::array<glm::vec3, 3>> worldFaces() const;

  void moveTo(const glm::vec3 newPosition);
  void rotateTo(const glm::vec3 eulerAngles);
  void assignVAOandVBO(Screen* screen);
  void reassignVAOandVBO();

  unsigned int getVAO_address() { return VAO; }

protected:
  void Initialize();

  void verticeToWorld(glm::vec3 &vertice) const;
  void rotateVertice(glm::vec3 &vertice) const;
  void recalculateWorldVertices();

private:
  void refreshWorldVertices();
  void refreshRotationMatrix();
  void dupLocalVerticesToWorld();
  void cleanAllVerticesMemory();

// atributes
protected:
  glm::vec3 position = { 0, 0, 0 };
  glm::vec3 rotation = { 0, 0, 0 };

  std::vector<glm::vec3> localVertices;
  std::vector<glm::vec3> worldVertices;
  std::vector<std::array<unsigned int, 3>> localFaces;

private:
  glm::mat4 rotationMatrix;

  unsigned int VAO;
  unsigned int VBO;
};
