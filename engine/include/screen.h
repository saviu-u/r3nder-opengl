#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Object;

class Screen
{
public:
  // constructors
  Screen();

  // methods
public:
  unsigned int getShaderProgramAddress() const { return shaderProgramAddress; }
  void addObjectToScene(Object &object);

  void eventLoop();
  void close();

private:
  void initializeGL();
  void compileShaders();
  void initializeShaderProgram();
  std::string importShader(std::string filePath) const;

  // attributes
public:
  unsigned int screenWidth = 800;
  unsigned int screenHeight = 600;
  float aspectRatio;
protected:
  std::vector<Object*> sceneObjects;
private:
  GLFWwindow *window;

  unsigned int shaderProgramAddress;

  std::vector<unsigned int> shaderAddresses;
};
