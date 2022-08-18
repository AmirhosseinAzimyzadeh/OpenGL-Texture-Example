#include "Shader.h"
#include <iostream>

using namespace std;

Shader::Shader() {
  shaderID = 0;
  uniformProjection = 0;
  uniformModel = 0;
}

void Shader::createFromString(const char* vertexCode, const char* fragmentCode) {
  compileShader(vertexCode, fragmentCode);
}

void Shader::compileShader(
  const char* vertexCode,
  const char* fragmentCode
) {
  shaderID = glCreateProgram();

  if (!shaderID) {
    cout << "Error creating shader program" << endl;
    return;
  }
  addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
  addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

  GLint result = 0;
  GLchar errorLog[1024] = { 0 };

  glLinkProgram(shaderID);

  // check link status
  glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
  if (!result) {
    glGetProgramInfoLog(shaderID, sizeof(errorLog), NULL, errorLog);
    cout << "Error linking shader program: " << errorLog << endl;
    return;
  }

  // validate program
  glValidateProgram(shaderID);
  glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
  if (!result) {
    glGetProgramInfoLog(shaderID, sizeof(errorLog), NULL, errorLog);
    cout << "Error validating the program: " << errorLog << endl;
    return;
  }

  uniformModel = glGetUniformLocation(shaderID, "model");
  uniformProjection = glGetUniformLocation(shaderID, "projection");
}

void Shader::addShader(
  GLuint program,
  const char* shaderCode,
  GLenum shaderType
) {
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

void Shader::useShader() {
  glUseProgram(shaderID);
}

void Shader::clearShader() {
  if (shaderID != 0) {
    glDeleteProgram(shaderID);
    shaderID = 0;
  }

  uniformModel = 0;
  uniformProjection = 0;
}

GLuint Shader::getProjectionLocation() {
  return uniformProjection;
}

GLuint Shader::getModelLocation() {
  return uniformModel;
}

Shader::~Shader() {
  clearShader();
}