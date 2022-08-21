#include "Camera.h"

Camera::Camera(
  glm::vec3 startPosition,
  glm::vec3 startUp,
  GLfloat startYaw,
  GLfloat startPitch,
  GLfloat startMoveSpeed,
  GLfloat startTurnSpeed
) {
  position = startPostion;
  up = startUp;
  yaw = startYaw;
  pitch = startPitch;
  front = glm::vec3(0.0f, 0.0f, -1.0f);

  moveSpeed = startMoveSpeed;
  turnSpeed = startTurnSpeed;

  update();
}

void Camera::update() {
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(front);
}

Camera::~Camera() {

}
