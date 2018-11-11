#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <fstream>
#include <string>
#include <vector>
#include "Texture.h"
#include "VertexArray.h"


class VertexArray;

struct Sampler
{
	GLint m_id;
	Texture *m_tex;
};

class Shader
{
private:
	GLuint m_id;
	std::vector<Sampler> m_sampler;
public:
	Shader();
	Shader(std::string _vert, std::string _frag);
	void draw(VertexArray *vertexArray);
	void setUniform(std::string _uniform, glm::vec4 _value);
	void setUniform(std::string _uniform, float _value);
	void setUniform(std::string _uniform, Texture *_tex);
	void setUniform(std::string _uniform, glm::mat4 _value);
	GLuint getId();
};


