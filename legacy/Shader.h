#ifndef _SHADER_H_
#define _SHADER_H_
#include <vector>
#include <GL/glew.h>

class VertexArray;
class Texture;
class SpotLight;
class PointLight;
class DirLight;


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
	//Shader();
	Shader(std::string _vert, std::string _frag);
	void draw(VertexArray *vertexArray);
	void printShaderInfoLog(GLuint obj); //Reference Karsten
	void setUniform(std::string _uniform, glm::vec4 _value);
	void setUniform(std::string _uniform, float _value);
	void setUniform(std::string _uniform, int _value);
	void setUniform(std::string _uniform, Texture *_tex);
	void setUniform(std::string _uniform, glm::mat4 _value);
	void setUniform(std::string _uniform, glm::vec3 _value);
	GLuint getId();
};


#endif