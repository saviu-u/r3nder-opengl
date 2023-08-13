#include "prebuilt/cube.h"

Cube::Cube(float size_x, float size_y, float size_z)
{
  float edge_x = size_x / 2;
  float edge_y = size_y / 2;
  float edge_z = size_z / 2;

  localVertices = {
      // Back face
      new glm::vec3(-edge_x, -edge_y, -edge_z), // Bottom-left   0
      new glm::vec3(edge_x, -edge_y, -edge_z),  // Bottom-right  1
      new glm::vec3(edge_x, edge_y, -edge_z),   // Top-right     2
      new glm::vec3(-edge_x, edge_y, -edge_z),  // Top-left      3
      // Front face
      new glm::vec3(-edge_x, -edge_y, edge_z), // Bottom-left    4
      new glm::vec3(edge_x, -edge_y, edge_z),  // Bottom-right   5
      new glm::vec3(edge_x, edge_y, edge_z),   // Top-right      6
      new glm::vec3(-edge_x, edge_y, edge_z)   // Top-left       7
  };

  localFaces = {
    // Back faces
    { localVertices[0], localVertices[1], localVertices[2] },
    { localVertices[0], localVertices[2], localVertices[3] },
    // Front face
    { localVertices[4], localVertices[5], localVertices[6] },
    { localVertices[4], localVertices[6], localVertices[7] },
    // Left face
    { localVertices[3], localVertices[4], localVertices[0] },
    { localVertices[3], localVertices[4], localVertices[7] },
    // Right face
    { localVertices[2], localVertices[5], localVertices[1] },
    { localVertices[2], localVertices[5], localVertices[6] },
    // Top face
    { localVertices[3], localVertices[7], localVertices[6] },
    { localVertices[6], localVertices[2], localVertices[3] },
    // Bottom face
    { localVertices[0], localVertices[4], localVertices[5] },
    { localVertices[5], localVertices[1], localVertices[0] }
  };

  Initialize();
}
