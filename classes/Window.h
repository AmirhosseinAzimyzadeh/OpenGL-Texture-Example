#include <iostream>
#include "gl/glew.h"
#include "glfw/glfw3.h"

class WindowHandler {
  public: WindowHandler();
  WindowHandler(GLint windowWidth, GLint windowHeight);

  int initialize();

  GLfloat getBufferWidth();
  GLfloat getBufferHeight();

  bool getShouldClose();

  void swapBuffers();

  ~WindowHandler();

  private:
    GLFWwindow *mainWindow;

    GLint width, height;
    GLint bufferWidth, bufferHeight;

    bool keys[1024];

    void initKeyArray();

    static void handleKey(GLFWwindow *window, int key, int scancode, int action, int mode);
};