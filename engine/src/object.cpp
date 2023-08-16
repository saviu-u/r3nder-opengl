#include <map>
#include <glm/gtx/euler_angles.hpp>
#include "screen.h"
#include "object.h"

// constructors

Object::~Object() {}
Object::Object() {}

// public

std::vector<float> Object::worldFacesVerticesBuffer() const {
  std::vector<float> buffer;

  for(std::array<glm::vec3, 3> face : worldFaces()){
    for(glm::vec3 vertex : face){
      buffer.push_back(vertex.x);
      buffer.push_back(vertex.y);
      buffer.push_back(vertex.z);
    }
  }

  return buffer;
}

void Object::moveTo(const glm::vec3 newPosition){
  position = newPosition;
  recalculateWorldVertices();
}

void Object::rotateTo(const glm::vec3 eulerAngles){
  rotation = eulerAngles;
  refreshRotationMatrix();
  recalculateWorldVertices();
}


std::vector<std::array<glm::vec3, 3>> Object::worldFaces() const {
  std::vector<std::array<glm::vec3, 3>> worldFaces;

  for(std::array<unsigned int, 3> localFace : localFaces)
    worldFaces.push_back({ worldVertices[localFace[0]], worldVertices[localFace[1]], worldVertices[localFace[2]] });

  return worldFaces;
}

void Object::assignVAOandVBO(Screen *screen){
// Set up cube vertices and buffers
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  std::vector<float> vertices = worldFacesVerticesBuffer();

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

  // After linking the shader program
  int positionAttributeLocation = glGetAttribLocation(screen->getShaderProgramAddress(), "aPos");

  // Vertex positions
  glVertexAttribPointer(positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(positionAttributeLocation);

  glBindVertexArray(0);
}

void Object::reassignVAOandVBO(){
  std::vector<float> vertices = worldFacesVerticesBuffer();

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
  glBindVertexArray(0);
}

// protected

void Object::Initialize()
{
  dupLocalVerticesToWorld();
  refreshRotationMatrix();
  recalculateWorldVertices();
}

void Object::verticeToWorld(glm::vec3 &vertice) const {
  vertice += position;
}

void Object::rotateVertice(glm::vec3 &vertice) const {
  vertice = glm::vec4(vertice, 1.0f) * rotationMatrix;
}

void Object::recalculateWorldVertices() {
  refreshWorldVertices();

  for(glm::vec3 &vertice : worldVertices){
    rotateVertice(vertice);
    verticeToWorld(vertice);
  }

  reassignVAOandVBO();
}

// private

void Object::dupLocalVerticesToWorld(){
  worldVertices.clear();

  for(glm::vec3 localVertice : localVertices)
    worldVertices.push_back(localVertice);
}

void Object::refreshWorldVertices()
{
  for(int i = 0 ; i < localVertices.size() ; i++)
    worldVertices[i] = localVertices[i];
}

void Object::refreshRotationMatrix()
{
  rotationMatrix = glm::eulerAngleXYZ(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z));
}
