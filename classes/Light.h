#include "glm/glm.hpp"
#include "gl/glew.h"

class Light {
  public:
    Light();
    Light(
      GLfloat red,
      GLfloat green,
      GLfloat blue,
      GLfloat intensity,
      GLfloat xDir,
      GLfloat yDir,
      GLfloat zDir,
      GLfloat diffuseIntensityValue
    );
    ~Light();

    void useLight(
      GLfloat ambientIntensityLocation,
      GLfloat ambientColorLocation,
      GLfloat diffuseIntensityLocation,
      GLfloat directionLocation
    );

  private:
    glm::vec3 color;
    GLfloat ambientIntensity;

    glm::vec3 direction;
    GLfloat diffuseIntensity;
};
