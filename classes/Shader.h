#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "gl/glew.h"

class Shader {
  public: Shader();
  ~Shader();

  void createFromString();

  private:
    GLuint shaderID, uniformProjection, uniformModel;
}
