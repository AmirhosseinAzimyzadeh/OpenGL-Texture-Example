#include "Camera.h"

Camera::Camera(
  glm::vec3 startPosition,
  glm::vec3 startUp,
  GLfloat startYaw,
  GLfloat startPitch
) {
  position = startPostion;
  up = startUp;
  yaw = startYaw;
  pitch = startPitch;
}

Camera::~Camera() {

}
