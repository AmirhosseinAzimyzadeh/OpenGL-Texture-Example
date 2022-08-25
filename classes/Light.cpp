#include "Light.h"
#include <iostream>
using namespace std;

Light::Light() {
  color = glm::vec3(1.0f, 1.0f, 1.0f);
  ambientIntensity = 1.0f;
  direction = glm::vec3(0.0f, -1.0f, 0.0f);
  diffuseIntensity = 1.0f;
}

Light::Light(
  GLfloat red,
  GLfloat green,
  GLfloat blue,
  GLfloat intensity,
  GLfloat xDir,
  GLfloat yDir,
  GLfloat zDir,
  GLfloat diffuseIntensityValue
) {
  color = glm::vec3(red, green, blue);
  ambientIntensity = intensity;
  direction = glm::vec3(xDir, yDir, zDir);
  diffuseIntensity = diffuseIntensityValue;
}

void Light::useLight(
  GLfloat ambientIntensityLocation,
  GLfloat ambientColorLocation,
  GLfloat diffuseIntensityLocation,
  GLfloat directionLocation
) {
  glUniform3f(ambientColorLocation, color.x, color.y, color.z);
  glUniform1f(ambientIntensityLocation, ambientIntensity);
  glUniform1f(diffuseIntensityLocation, diffuseIntensity);
  glUniform3f(directionLocation, direction.x, direction.y, direction.z);
}

Light::~Light() {

}
