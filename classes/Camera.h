#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
  public:
    Camera(
      glm::vec3 startPosition,
      glm::vec3 startUp,
      GLfloat startYaw,
      GLfloat startPitch
    );
    ~Camera();
  
  private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw;
    GLfloat pitch;

    void update();
};
