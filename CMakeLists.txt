cmake_minimum_required(VERSION 3.27.0)
project(r3nder-opengl VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})

include(CTest)
enable_testing()

add_executable(r3nder-opengl main.cpp)

# Add the glad directory to the include path
include_directories(${CMAKE_SOURCE_DIR}/glad/include)

# Add glad source file to the project
add_library(glad ${CMAKE_SOURCE_DIR}/glad/src/glad.c)

target_include_directories(r3nder-opengl PRIVATE glm)

# Link against OpenGL, GLFW, and GLAD libraries
target_link_libraries(r3nder-opengl ${OPENGL_LIBRARIES} glfw glad)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
