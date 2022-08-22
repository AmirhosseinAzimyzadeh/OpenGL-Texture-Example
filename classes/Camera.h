#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glfw/glfw3.h"

class Camera {
  public:
    Camera();
    Camera(
      glm::vec3 startPosition,
      glm::vec3 startUp,
      GLfloat startYaw,
      GLfloat startPitch,
      GLfloat startMoveSpeed,
      GLfloat startTurnSpeed
    );

    void keyHandler(bool* keys, GLfloat deltaTime);

    glm::mat4 getViewMatrix();

    ~Camera();
  
  private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw;
    GLfloat pitch;

    GLfloat moveSpeed;
    GLfloat turnSpeed;

    void update();
};
