#version 330 core
layout(location = 0) in vec3 aPos;
out vec3 fragColor; // Color output to fragment shader
uniform mat4 view;
uniform mat4 projection;
void main() {
  gl_Position = projection * view * vec4(aPos, 1.0);
  fragColor = aPos + 0.5; // Use position as color offset
}