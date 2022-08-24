#include "glm/glm.hpp"
#include "gl/glew.h"

class Light {
  public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity);
    ~Light();

    void useLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation);

  private:
    glm::vec3 color;
    GLfloat ambientIntensity;
};
