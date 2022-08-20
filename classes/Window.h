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

  bool* getPressedKeys();

  GLfloat getXChange();
  GLfloat getYChange();

  void swapBuffers();

  ~WindowHandler();

  private:
    GLFWwindow *mainWindow;

    GLint width, height;
    GLint bufferWidth, bufferHeight;

    bool keys[1024];

    // move handler properties
    GLfloat lastX;
    GLfloat lastY;
    GLfloat xChange;
    GLfloat yChange;
    bool isFirstMove;

    void initKeyArray();

    static void handleKey(GLFWwindow *window, int key, int scancode, int action, int mode);
    static void handleMouseMove(GLFWwindow *window, double xpos, double ypos);
};