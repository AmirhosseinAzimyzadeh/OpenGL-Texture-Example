#include "Texture.h"

Texture::Texture() {
  resetProperties();
}

void Texture::resetProperties() {
  textureId = 0;
  width = 0;
  height = 0;
  bitDepth = 0;
  fileLocation = NULL;
}

Texture::Texture(char* filePath) {
  resetProperties();
  fileLocation = filePath;
}

void Texture::loadTexture() {
  unsigned char *data = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
  if (!data) {
    std::cout << "Loading Texture failed" << std::endl;
    return;
  }

  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(
    GL_TEXTURE_2D,
    0, // mip map level (if there is any level specify here)
    GL_RGBA, // format 
    width,
    height,
    0, // border (if any)
    GL_RGBA,
    GL_UNSIGNED_BYTE, // unsigned char = byte  
    data // data itself
  );

  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(data);
}

void Texture::useTexture() {
  glActiveTexture(GL_TEXTURE0); // texture unit
  glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::clearTexture() {
  glDeleteTextures(1, &textureId);
  resetProperties();
}

Texture::~Texture() {
  clearTexture();
}