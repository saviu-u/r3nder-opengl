#include <map>
#include <glm/gtx/euler_angles.hpp>
#include "screen.h"
#include "object.h"

// constructors

Object::~Object() {}
Object::Object() {}

// public
void Object::renderToGPU() {
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  std::vector<std::array<glm::vec3, 3>> faces = worldFaces();

  for(int i = 0 ; i < faces.size() ; i++){
    std::array<glm::vec3, 3> face = faces[i];
    u_int faceSize = face.size() * sizeof(glm::vec3);

    glBufferSubData(GL_ARRAY_BUFFER, i * faceSize, faceSize, face.data());
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  GPUrefreshed = true;
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

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, localFaces.size() * 3 * sizeof(glm::vec3), (void *)0, GL_DYNAMIC_DRAW);

  // After linking the shader program
  int positionAttributeLocation = glGetAttribLocation(screen->getShaderProgramAddress(), "aPos");

  // Vertex positions
  glVertexAttribPointer(positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(positionAttributeLocation);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  GPUrefreshed = false;
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

  GPUrefreshed = false;
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
