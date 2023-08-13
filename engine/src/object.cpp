#include <object.h>
#include <map>
#include <glm/gtx/euler_angles.hpp>

// constructors

Object::~Object() {  cleanAllVerticesMemory();}
Object::Object() { Initialize(); }

// public

std::vector<float> Object::worldFacesVerticesBuffer() const {
  std::vector<float> buffer;

  for(std::array<glm::vec3*, 3> face : worldFaces){
    for(glm::vec3* vertex : face){
      buffer.push_back(vertex->x);
      buffer.push_back(vertex->y);
      buffer.push_back(vertex->z);
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

  for(glm::vec3 *vertice : worldVertices){
    rotateVertice(*vertice);
    verticeToWorld(*vertice);
  }
}

// private

void Object::refreshWorldVertices()
{
  for(glm::vec3 *localVertice : localVertices)
    *(localVerticesToWorld[localVertice]) = *localVertice;
}

void Object::dupLocalVerticesToWorld(){
  // Assign new vertices for world vertices
  for(glm::vec3 *localVertice : localVertices)
  {
    glm::vec3 *newVertice = new glm::vec3();
    localVerticesToWorld[localVertice] = newVertice;

    // Create a link between them
    worldVertices.push_back(newVertice);
  }

  // Do the same reference with the world faces
  for(std::array<glm::vec3*, 3> &face : localFaces){
    std::array<glm::vec3*, 3> newFace;

    for(int i = 0; i < face.size() ; i++)
      newFace[i] = localVerticesToWorld[face[i]];

    worldFaces.push_back(newFace);
  }
}

void Object::cleanAllVerticesMemory(){
  for(glm::vec3 *localVertice : localVertices)
    delete localVertice;

  for(glm::vec3 *worldVertice : worldVertices)
    delete worldVertice;
}

void Object::refreshRotationMatrix()
{
  rotationMatrix = glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
}
