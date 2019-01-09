
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <fstream>
#include <string>
#include "stb_image.h"
#include "Texture.h"

Texture::Texture()
{	

}


void Texture::addTexture(std::string _image)
{
	m_w = 0;
	m_h = 0;
	m_channels = 0;
	_image = "../Textures/" + _image;
	unsigned char *data = stbi_load(_image.c_str(), &m_w, &m_h, &m_channels, 4);
	if (!data) { throw std::exception(); }


	m_textureId = 0;
	glGenTextures(1, &m_textureId);
	if (!m_textureId) { throw std::exception(); }
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_w, m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}