#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <array>
#include <map>

class Object{
public:
// constructors
  Object();
  ~Object();
// methods
  std::vector<float> worldFacesVerticesBuffer() const;
  void moveTo(const glm::vec3 newPosition);
  void rotateTo(const glm::vec3 eulerAngles);

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

  std::vector<glm::vec3*> localVertices;
  std::vector<std::array<glm::vec3*, 3>> localFaces;

private:
  glm::mat4 rotationMatrix;
  std::vector<glm::vec3*> worldVertices;
  std::vector<std::array<glm::vec3*, 3>> worldFaces;
  std::map<glm::vec3*, glm::vec3*> localVerticesToWorld;
};
