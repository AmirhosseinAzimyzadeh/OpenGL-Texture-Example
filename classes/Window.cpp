#include "Window.h"
#include <iostream>

using namespace std;

WindowHandler::WindowHandler() {
  width = 800;
  height = 600;
  initKeyArray();
  isFirstMove = true;
}

WindowHandler::WindowHandler(GLint windowWidth, GLint windowHeight) {
  width = windowWidth;
  height = windowHeight;
  initKeyArray();
  isFirstMove = true;
}

GLfloat WindowHandler::getBufferWidth() { return bufferWidth; }

GLfloat WindowHandler::getBufferHeight() { return bufferHeight; }

bool WindowHandler::getShouldClose() { return glfwWindowShouldClose(mainWindow); }

void WindowHandler::swapBuffers() { glfwSwapBuffers(mainWindow); }

int WindowHandler::initialize() {
  if (!glfwInit()) {
    cout << "Failed to initialize GLFW" << endl;
    glfwTerminate();
    return 1;
  }

  // set version to 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // we dont want to use deprecated features of OpenGL & Allow forward compatibility
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // create the main window
  mainWindow = glfwCreateWindow(width, height, "OPEN_GL", NULL, NULL);
  if (!mainWindow) {
    cout << "Failed to create GLFW window" << endl;
    glfwTerminate();
    return 1;
  }

  // buffer size information
  glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

  // setting context for the GLEW
  glfwMakeContextCurrent(mainWindow);

  // Allow modern extension features
  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK) {
    cout << "Failed to initialize GLEW" << endl;
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    return 1;
  }

  glEnable(GL_DEPTH_TEST);

  // set up viewport
  glViewport(0, 0, bufferWidth, bufferHeight);

  glfwSetWindowUserPointer(mainWindow, this);

  glfwSetKeyCallback(mainWindow, handleKey);
  glfwSetCursorPosCallback(mainWindow, handleMouseMove);

  // glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  return 0;
}

void WindowHandler::initKeyArray() {
  for (int i = 0; i < 1024; i++) {
    keys[i] = false;
  }
}

void WindowHandler::handleKey(
  GLFWwindow *window,
  int key,
  int scancode,
  int action,
  int mode
)
{
  WindowHandler* theWindow = static_cast<WindowHandler*>(glfwGetWindowUserPointer(window));

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }

  if (key >=0 && key < 1024) {
    if (action == GLFW_PRESS) {
      theWindow->keys[key] = true;
    } else if (action == GLFW_RELEASE) {
      theWindow->keys[key] = false;
    }
  }
}

void WindowHandler::handleMouseMove(GLFWwindow *window, double x, double y) {
  WindowHandler* theWindow = static_cast<WindowHandler*>(glfwGetWindowUserPointer(window));
  
  if (theWindow->isFirstMove) {
    theWindow->lastX = x;
    theWindow->lastY = y;
    theWindow->isFirstMove = false;
  }

  theWindow->xChange = x - theWindow->lastX;
  theWindow->yChange = theWindow->lastY - y;
  theWindow->lastX = x;
  theWindow->lastY = y;
}

WindowHandler::~WindowHandler() {
  if (mainWindow) {
    glfwDestroyWindow(mainWindow);
  }
  glfwTerminate();
}