#version 330

layout (location = 0) in vec3 position;
out vec4 vertexColor;
uniform mat4 model;
uniform mat4 projection;

void main() {
  gl_Position = projection * model * vec4(position, 1.0);
  vertexColor = vec4(clamp(position, 0.0, 1.0), 1.0);
}