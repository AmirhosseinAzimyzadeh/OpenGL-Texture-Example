#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>

#include "gl/glew.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "classes/Mesh.cpp"
#include "classes/Shader.cpp"
#include "classes/Window.cpp"
#include "classes/Camera.cpp"

using namespace std;

const GLint WIDTH = 900;
const GLint HEIGHT = 800;

WindowHandler mainWindow = WindowHandler(WIDTH, HEIGHT);

Camera camera = Camera(
  glm::vec3(0.0f, 0.0f, 5.0f),
  glm::vec3(0.0f, 1.0f, 0.0f),
  -90.0f,
  0.0f,
  5.0f,
  0.3f
);

std::vector<Mesh*> meshes;
std::vector<Shader*> shaders;

const char* vertexShaderSource = "../../shaders/shader.vert";
const char* fragmentShaderSource = "../../shaders/shader.frag";

void createTriangle() {

  unsigned int indices[] = {
    0, 3, 1,
    1, 3, 2,
    2, 3, 0,
    0, 1, 2
  };

  GLfloat vertices[] = {
    -1.0f, -1.0f, 0.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
  };

  Mesh *obj1 = new Mesh();
  obj1->createMesh(vertices, indices, 12, 12);
  meshes.push_back(obj1);

  Mesh *obj2 = new Mesh();
  obj2->createMesh(vertices, indices, 12, 12);
  meshes.push_back(obj2);
}

void createShaders() {
  Shader *shader1 = new Shader();
  shader1->createFromSources(vertexShaderSource, fragmentShaderSource);
  shaders.push_back(shader1);
}

int main() {
  mainWindow.initialize();

  createTriangle();
  createShaders();
  
  GLuint uniformModel = shaders[0]->getModelLocation();
  GLuint uniformProjection = shaders[0]->getProjectionLocation();
  GLuint uniformView = shaders[0]->getViewLocation();

  glm::mat4 projection = glm::perspective(
    45.0f,
    (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(),
    0.1f,
    100.0f
  );

  while (!mainWindow.getShouldClose()) {
    // handle inputs
    glfwPollEvents();

    // delta time
    GLfloat deltaTime = utils::getDeltaTime();

    // clear window
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaders[0]->useShader();

    camera.keyHandler(mainWindow.getPressedKeys(), deltaTime);
    camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

    // creating transform matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -0.5f, -3.0f));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));

    meshes[0]->renderMesh();


    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, -3.0f));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    meshes[1]->renderMesh();


    glUseProgram(0);

    // swap buffers (what user sees with what we draw)
    mainWindow.swapBuffers();
  }
  
  return 0;
}
