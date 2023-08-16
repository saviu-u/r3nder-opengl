#include "screen.h"
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "object.h"

// Callback methods (not member method)

void frameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
  Screen* instance = static_cast<Screen*>(glfwGetWindowUserPointer(window));

  instance->screenHeight = height;
  instance->screenWidth = width;

  instance->aspectRatio = (float)width / height;

  glViewport(0, 0, width, height);
}

// Member methods

Screen::Screen() {
  aspectRatio = (float)screenWidth / screenHeight;

  initializeGL();
  compileShaders();
  initializeShaderProgram();
}

// public

void Screen::addObjectToScene(Object &object)
{
  object.assignVAOandVBO(this);
  sceneObjects.push_back(&object);
}

void Screen::eventLoop() {
  // Set up rendering loop
  while (!glfwWindowShouldClose(window))
  {
    // Clear the screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set model, view, and projection matrices
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 100.0f);

    // Use shader program and bind cube VAO
    glUseProgram(shaderProgramAddress);

    // Pass matrices to the shader
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramAddress, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramAddress, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    for(Object *object : sceneObjects){
      glBindVertexArray(object->getVAO_address());

      glDrawArrays(GL_TRIANGLES, 0, object->worldFacesVerticesBuffer().size() / 3);
    }

    // Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void Screen::close(){
  glfwTerminate();
}

// private

void Screen::initializeGL(){
  // Initialize GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  window = glfwCreateWindow(screenWidth, screenHeight, "r3nder-opengl", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glEnable(GL_DEPTH_TEST);

  // Set framebuffer size callback
  glfwSetWindowUserPointer(window, this);
  glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

  shaderProgramAddress = glCreateProgram();
}

void Screen::compileShaders(){
  shaderAddresses.clear();

  std::string shaderCodeVertex = importShader("vertex_shader.vert");
  std::string shaderCodeFragment = importShader("fragment_shader.frag");

  const char* vertexCode = shaderCodeVertex.c_str();
  const char* fragmentCode = shaderCodeFragment.c_str();

  unsigned int vertexShader, fragmentShader;

  // Vertex Shader
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexCode, nullptr);
  glCompileShader(vertexShader);

  // Fragment Shader
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentCode, nullptr);
  glCompileShader(fragmentShader);

  shaderAddresses.push_back(vertexShader);
  shaderAddresses.push_back(fragmentShader);
}

void Screen::initializeShaderProgram(){
  for(unsigned int shaderAddress : shaderAddresses)
    glAttachShader(shaderProgramAddress, shaderAddress);

  glLinkProgram(shaderProgramAddress);
}

std::string Screen::importShader(std::string filePath) const
{
  std::ifstream shaderFileSource("../shaders/" + filePath);
  std::string shaderCode((std::istreambuf_iterator<char>(shaderFileSource)), (std::istreambuf_iterator<char>()));

  shaderFileSource.close();

  return shaderCode;
}
