#include <iostream>
#include <string.h>

#include "gl/glew.h"
#include "glfw/glfw3.h"

using namespace std;

const GLint WIDTH = 800;
const GLint HEIGHT = 600;

// VAOs and VBOs ids
GLuint VAO;
GLuint VBO;
GLuint shader;

// create vertex shader
static const char* vShader = "\n\
#version 330 core\n\
\n\
layout (location = 0) in vec3 position;\n\
\n\
void main()\n\
{\n\
    gl_Position = vec4(0.5 * position.x, 0.5 * position.y, position.z, 1.0);\n\
}";

static const char* fShader = "\n\
#version 330 core\n\
\n\
out vec4 color;\n\
\n\
void main()\n\
{\n\
    color = vec4(0.1, 0.0, 1.0, 1.0);\n\
}";

void createTriangle() {
  GLfloat vertices[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
  };

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER,  sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_FALSE, // is dynamic?
    0, // skip
    0 // offset
  );
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // unbind VAO
  glBindVertexArray(0);
}


int main() {
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
  GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "OPEN_GL", NULL, NULL);
  if (!mainWindow) {
    cout << "Failed to create GLFW window" << endl;
    glfwTerminate();
    return 1;
  }

  // buffer size information
  int bufferWidth;
  int bufferHeight;
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

  // set up viewport
  glViewport(0, 0, bufferWidth, bufferHeight);

  
  while (!glfwWindowShouldClose(mainWindow)) {
    // handle inputs
    glfwPollEvents();

    // clear window
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // swap buffers (what user sees with what we draw)
    glfwSwapBuffers(mainWindow);
  }
  
  return 0;
}
