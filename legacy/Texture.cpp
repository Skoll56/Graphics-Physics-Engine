#include "Texture.h"

Texture::Texture()
{	

}


void Texture::addTexture(std::string _image)
{
	w = 0;
	h = 0;
	channels = 0;
	unsigned char *data = stbi_load(_image.c_str(), &w, &h, &channels, 4);
	if (!data) { throw std::exception(); }


	textureId = 0;
	glGenTextures(1, &textureId);
	if (!textureId) { throw std::exception(); }
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}