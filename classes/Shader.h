#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "gl/glew.h"

class Shader {
  public: Shader();

  void createFromString(const char* vertexCode, const char* fragmentCode);
  void createFromSources(const char* vertexSource, const char* fragmentSource);

  GLuint getProjectionLocation();
  GLuint getModelLocation();
  GLuint getViewLocation();

  void useShader();
  void clearShader();

  ~Shader();

  private:
    GLuint shaderID, uniformProjection, uniformModel, uniformView;

    void compileShader(const char* vertexCode, const char* fragmentCode);
    void addShader(GLuint program, const char* shaderCode, GLenum shaderType);
};
