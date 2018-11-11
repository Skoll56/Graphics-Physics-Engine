#ifndef _Texture_H_
#define _Texture_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <fstream>
#include <string>
#include "stb_image.h"


class Texture
{
public:
	Texture();
	~Texture() {};
	GLuint get() { return textureId; }
	void addTexture(std::string _image);

private:
	int w, h, channels;
	GLuint textureId;
};

#endif