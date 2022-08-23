#version 330

in vec4 vertexColor;
in vec2 vertexTexture;

out vec4 color;

uniform sampler2D textureSampler;

void main() {
    color = texture(textureSampler, vertexTexture) * vertexColor;
}
