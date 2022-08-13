#include <iostream>
#include <string.h>
#include <cmath>

#include "gl/glew.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;

const GLint WIDTH = 800;
const GLint HEIGHT = 600;

// VAOs and VBOs ids
GLuint VAO;
GLuint VBO;
GLuint shader;
GLuint uniformModel;

bool direction = true;
float triangleOffset = 0.0f;
float triangleMaxOffset = 0.7f;
float triangleOffsetIncrement = 0.00005f;

float toRadian(float degree) {
  return degree * M_PI / 180.0f;
}

// create vertex shader
static const char* vShader = "\n\
#version 330\n\
\n\
layout (location = 0) in vec3 position;\n\
uniform mat4 model; \n\
\n\
void main()\n\
{\n\
  gl_Position = model * vec4(position, 1.0);\n\
}";

static const char* fShader = "\n\
#version 330\n\
\n\
out vec4 color;\n\
\n\
void main()\n\
{\n\
    color = vec4(1.0, 0.0, 1.0, 1.0);\n\
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

void addShader(GLuint program, const char* shaderCode, GLenum shaderType) {
  GLuint shader = glCreateShader(shaderType);

  const GLchar* code[1];
  code[0] = shaderCode;

  GLint codeLength[1];
  codeLength[0] = strlen(shaderCode);

  glShaderSource(shader, 1, code, codeLength);
  glCompileShader(shader);

  GLint result = 0;
  GLchar errorLog[1024] = { 0 };

  // check link status
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  if (!result) {
    glGetShaderInfoLog(shader, sizeof(errorLog), NULL, errorLog);
    cout << "Error compiling shader program: " << errorLog << endl;
    return;
  }

  glAttachShader(program, shader);
}


void compileShaders() {
  shader = glCreateProgram();

  if (!shader) {
    cout << "Error creating shader program" << endl;
    return;
  }
  addShader(shader, vShader, GL_VERTEX_SHADER);
  addShader(shader, fShader, GL_FRAGMENT_SHADER);

  GLint result = 0;
  GLchar errorLog[1024] = { 0 };

  glLinkProgram(shader);

  // check link status
  glGetProgramiv(shader, GL_LINK_STATUS, &result);
  if (!result) {
    glGetProgramInfoLog(shader, sizeof(errorLog), NULL, errorLog);
    cout << "Error linking shader program: " << errorLog << endl;
    return;
  }

  // validate program
  glValidateProgram(shader);
  glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
  if (!result) {
    glGetProgramInfoLog(shader, sizeof(errorLog), NULL, errorLog);
    cout << "Error validating the program: " << errorLog << endl;
    return;
  }

  uniformModel = glGetUniformLocation(shader, "model");
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

  createTriangle();
  compileShaders();
  
  while (!glfwWindowShouldClose(mainWindow)) {
    // handle inputs
    glfwPollEvents();

    // check direction
    if (direction) {
      triangleOffset += triangleOffsetIncrement;
    } else {
      triangleOffset -= triangleOffsetIncrement;
    }

    if (abs(triangleOffset) > triangleMaxOffset) {
      direction = !direction;
    }

    // clear window
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);

    // creating transform matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(triangleOffset, triangleOffset, 0.0f));
    model = glm::rotate(model, toRadian(triangleOffset * 100), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(0.1f, 0.5f, 1.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);

    glUseProgram(0);

    // swap buffers (what user sees with what we draw)
    glfwSwapBuffers(mainWindow);
  }
  
  return 0;
}
