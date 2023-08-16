#include "prebuilt/cube.h"

Cube::Cube(float size_x, float size_y, float size_z)
{
  float edge_x = size_x / 2;
  float edge_y = size_y / 2;
  float edge_z = size_z / 2;

  localVertices = {
      // Back face
      {-edge_x, -edge_y, -edge_z}, // Bottom-left   0
      {edge_x, -edge_y, -edge_z},  // Bottom-right  1
      {edge_x, edge_y, -edge_z},   // Top-right     2
      {-edge_x, edge_y, -edge_z},  // Top-left      3
      // Front face
      {-edge_x, -edge_y, edge_z}, // Bottom-left    4
      {edge_x, -edge_y, edge_z},  // Bottom-right   5
      {edge_x, edge_y, edge_z},   // Top-right      6
      {-edge_x, edge_y, edge_z}   // Top-left       7
  };

  localFaces = {
    // Back faces
    { 0, 1, 2 },
    { 0, 2, 3 },
    // Front face
    { 4, 5, 6 },
    { 4, 6, 7 },
    // Left face
    { 3, 4, 0 },
    { 3, 4, 7 },
    // Right face
    { 2, 5, 1 },
    { 2, 5, 6 },
    // Top face
    { 3, 7, 6 },
    { 6, 2, 3 },
    // Bottom face
    { 0, 4, 5 },
    { 5, 1, 0 }
  };

  Initialize();
}
