#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "gl/glew.h"

class Shader {
  public: Shader();

  void createFromString(const char* vertexCode, const char* fragmentCode);

  GLuint getProjectionLocation();
  GLuint getModelLocation();

  void useShader();
  void clearShader();

  ~Shader();

  private:
    GLuint shaderID, uniformProjection, uniformModel;

    void compileShader(const char* vertexCode, const char* fragmentCode);
    void addShader(GLuint program, const char* shaderCode, GLenum shaderType);
};
