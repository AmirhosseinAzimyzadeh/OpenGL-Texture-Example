#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "gl/glew.h"

class Shader {
  public: Shader();
  ~Shader();

  void createFromString();

  GLuint getProjectionLocation();
  GLuint getModelLocation();

  void useShader();
  void clearShader();

  private:
    GLuint shaderID, uniformProjection, uniformModel;

    void compileShader();
    void addShader();
}
