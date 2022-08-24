#include "glm/glm.hpp"
#include "gl/glew.h"

class Light {
  public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity);
    ~Light();

    useLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation);

  private:
    glm::vec3 color;
    GLfloat ambientIntensity;
};
