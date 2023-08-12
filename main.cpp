#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char *vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    out vec3 fragColor; // Color output to fragment shader
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    void main() {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
        fragColor = aPos + 0.5; // Use position as color offset
    }
)";

const char *fragmentShaderSource = R"(
    #version 330 core
    in vec3 fragColor;
    out vec4 FragColor;
    void main() {
        FragColor = vec4(fragColor, 1.0);
    }
)";

float cubeVertices[] = {
    // Back face
    -0.5f, -0.5f, -0.5f, // Bottom-left
    0.5f, -0.5f, -0.5f,  // Bottom-right
    0.5f, 0.5f, -0.5f,   // Top-right
    0.5f, 0.5f, -0.5f,   // Top-right
    -0.5f, 0.5f, -0.5f,  // Top-left
    -0.5f, -0.5f, -0.5f, // Bottom-left
    // Front face
    -0.5f, -0.5f, 0.5f, // Bottom-left
    0.5f, -0.5f, 0.5f,  // Bottom-right
    0.5f, 0.5f, 0.5f,   // Top-right
    0.5f, 0.5f, 0.5f,   // Top-right
    -0.5f, 0.5f, 0.5f,  // Top-left
    -0.5f, -0.5f, 0.5f, // Bottom-left
    // Left face
    -0.5f, 0.5f, 0.5f,   // Top-right
    -0.5f, 0.5f, -0.5f,  // Top-left
    -0.5f, -0.5f, -0.5f, // Bottom-left
    -0.5f, -0.5f, -0.5f, // Bottom-left
    -0.5f, -0.5f, 0.5f,  // Bottom-right
    -0.5f, 0.5f, 0.5f,   // Top-right
                                            // Right face
    0.5f, 0.5f, 0.5f,     // Top-left
    0.5f, 0.5f, -0.5f,    // Top-right
    0.5f, -0.5f, -0.5f,   // Bottom-right
    0.5f, -0.5f, -0.5f,   // Bottom-right
    0.5f, -0.5f, 0.5f,    // Bottom-left
    0.5f, 0.5f, 0.5f,     // Top-left
    // Bottom face
    -0.5f, -0.5f, -0.5f, // Top-right
    0.5f, -0.5f, -0.5f,  // Top-left
    0.5f, -0.5f, 0.5f,   // Bottom-left
    0.5f, -0.5f, 0.5f,   // Bottom-left
    -0.5f, -0.5f, 0.5f,  // Bottom-right
    -0.5f, -0.5f, -0.5f, // Top-right
    // Top face
    -0.5f, 0.5f, -0.5f, // Bottom-left
    0.5f, 0.5f, -0.5f,  // Bottom-right
    0.5f, 0.5f, 0.5f,   // Top-right
    0.5f, 0.5f, 0.5f,   // Top-right
    -0.5f, 0.5f, 0.5f,  // Top-left
    -0.5f, 0.5f, -0.5f  // Bottom-left
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

int main()
{
  // Initialize GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Cube", nullptr, nullptr);
  if (window == nullptr)
  {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Set framebuffer size callback
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Load GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // Enable depth testing
  glEnable(GL_DEPTH_TEST);

  // Compile shaders and create shader program
  unsigned int vertexShader, fragmentShader, shaderProgram;

  // Vertex Shader
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  // Check for compilation errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    std::cerr << "Vertex shader compilation failed\n"
              << infoLog << std::endl;
  }

  // Fragment Shader
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);

  // Check for compilation errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
    std::cerr << "Fragment shader compilation failed\n"
              << infoLog << std::endl;
  }

  // Shader Program
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // Check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cerr << "Shader program linking failed\n"
              << infoLog << std::endl;
  }

  // Set up cube vertices and buffers
  unsigned int VBO, cubeVAO;
  glGenVertexArrays(1, &cubeVAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(cubeVAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

  // Vertex positions
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  // Set up rendering loop
  while (!glfwWindowShouldClose(window))
  {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // Clear the screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use shader program and bind cube VAO
    glUseProgram(shaderProgram);
    glBindVertexArray(cubeVAO);

    glm::mat4 model(1.0f);

    // Set model, view, and projection matrices
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float) width / height, 0.1f, 100.0f);

    // Calculate model matrix for rotation
    model = glm::rotate(model, (float)(glfwGetTime() * M_PI / 2), glm::vec3(0.0f, 1.0f, 0.0f));

    // Pass matrices to the shader
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Draw the cube
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Terminate GLFW
  glfwTerminate();
  return 0;
}
