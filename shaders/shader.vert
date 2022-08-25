#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture;
layout (location = 2) in vec3 norm;

out vec4 vertexColor;
out vec2 vertexTexture;
out vec3 normal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
  gl_Position = projection * view * model * vec4(position, 1.0f);
  vertexColor = vec4(clamp(position, 0.0f, 1.0f), 1.0f);

  vertexTexture = texture;

  normal = mat3(transpose(inverse(model))) * norm;
}