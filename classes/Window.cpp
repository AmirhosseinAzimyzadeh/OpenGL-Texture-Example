#include "Window.h"
#include <iostream>

using namespace std;

WindowHandler::WindowHandler() {
  width = 800;
  height = 600;
}

WindowHandler::WindowHandler(GLint windowWidth, GLint windowHeight) {
  width = windowWidth;
  height = windowHeight;
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
  return 0;
}

WindowHandler::~WindowHandler() {
  if (mainWindow) {
    glfwDestroyWindow(mainWindow);
  }
  glfwTerminate();
}