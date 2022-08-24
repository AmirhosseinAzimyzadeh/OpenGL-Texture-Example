#version 330

in vec4 vertexColor;
in vec2 vertexTexture;

struct DirectionalLight {
    vec3 color;
    float ambientIntensity;
};

out vec4 color;

uniform sampler2D textureSampler;
uniform DirectionalLight directionalLight;

void main() {
    vec4 ambientColor = vec4(directionalLight.color, 1.0f) * directionalLight.ambientIntensity;
    color = texture(textureSampler, vertexTexture) * ambientColor;
}
