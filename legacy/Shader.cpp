#include "Shader.h"


Shader::Shader()
{
	std::string vertShader;
	std::string fragShader;
	std::ifstream file("../shaders/vert.txt");
	if (!file.is_open()) { throw std::exception(); }
	else
	{
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			vertShader += line + "\n";

		}
	}
	file.close();

	file.open("../shaders/frag.txt");
	if (!file.is_open()) { throw std::exception(); }
	else
	{
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			fragShader += line + "\n";

		}
	}
	file.close();

	const char *vertex = vertShader.c_str();
	const char *fragment = fragShader.c_str();
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertex, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success) { throw std::exception(); }

	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragment, NULL);
	glCompileShader(fragmentShaderId);
	success = 0;
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		throw std::exception();
	}

	m_id = glCreateProgram();
	glAttachShader(m_id, vertexShaderId);
	glAttachShader(m_id, fragmentShaderId);
	glBindAttribLocation(m_id, 0, "in_Position");
	glBindAttribLocation(m_id, 1, "in_Color");
	glBindAttribLocation(m_id, 2, "in_TexCoord");

	glLinkProgram(m_id);
	success = 0;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success) { throw std::exception(); }

	glDetachShader(m_id, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(m_id, fragmentShaderId);
	glDeleteShader(fragmentShaderId);

}

Shader::Shader(std::string _vert, std::string _frag)
{
	std::string vertShader;
	std::string fragShader;

	std::ifstream file(_vert);
	if (!file.is_open()) { throw std::exception(); }
	else
	{
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			vertShader += line + "\n";

		}
	}
	file.close();

	file.open(_frag);
	if (!file.is_open()) { throw std::exception(); }
	else
	{
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			fragShader += line + "\n";

		}
	}
	file.close();

	const char *vertex = vertShader.c_str();
	const char *fragment = fragShader.c_str();

	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertex, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success) { throw std::exception(); }

	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragment, NULL);
	glCompileShader(fragmentShaderId);
	success = 0;
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		throw std::exception();
	}

	m_id = glCreateProgram();
	glAttachShader(m_id, vertexShaderId);
	glAttachShader(m_id, fragmentShaderId);
	glBindAttribLocation(m_id, 0, "in_Position");
	glBindAttribLocation(m_id, 1, "in_Color");
	glBindAttribLocation(m_id, 2, "in_TexCoord");

	glLinkProgram(0);
	success = 0;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success) { throw std::exception(); }

	glDetachShader(m_id, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(m_id, fragmentShaderId);
	glDeleteShader(fragmentShaderId);

}

void Shader::draw(VertexArray *_vertexArray)
{
	glUseProgram(m_id);
	glBindVertexArray(_vertexArray->getId());
	//glUniform4f(colorUniformId, 0, 1, 0, 1);

	for (size_t i = 0; i < m_sampler.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		if (m_sampler.at(i).m_tex)
		{
			glBindTexture(GL_TEXTURE_2D, m_sampler.at(i).m_tex->get());
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	}
	glDrawArrays(GL_TRIANGLES, 0, _vertexArray->getVertexCount());

	for (size_t i = 0; i < m_sampler.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glBindVertexArray(0);
	glUseProgram(0);

}

void Shader::setUniform(std::string _uniform, glm::vec4 _value)
{
	GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());
	if (uniformId == -1) { throw std::exception(); }

	glUseProgram(m_id);
	glUniform4f(uniformId, _value.x, _value.y, _value.z, _value.w);
	glUseProgram(0);
}

void Shader::setUniform(std::string _uniform, glm::mat4 _value)
{
	GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());
	if (uniformId == -1) { throw std::exception(); }

	glUseProgram(m_id);
	glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(_value));
	glUseProgram(0);
}

void Shader::setUniform(std::string _uniform, float _value)
{
	GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());
	if (uniformId == -1) { throw std::exception(); }

	glUseProgram(m_id);
	glUniform1f(uniformId, _value);
	glUseProgram(0);
}

void Shader::setUniform(std::string _uniform, Texture *_tex)
{
	GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());
	if (uniformId == -1) { throw std::exception(); }

	for (size_t i = 0; i < m_sampler.size(); i++)
	{
		if (m_sampler.at(i).m_id == uniformId)
		{
			m_sampler.at(i).m_tex = _tex;
			glUseProgram(m_id);
			glUniform1f(uniformId, i);
			glUseProgram(0);
			return;
		}

	}

	Sampler s;
	s.m_id = uniformId;
	s.m_tex = _tex;
	m_sampler.push_back(s);

	glUseProgram(m_id);
	glUniform1f(uniformId, m_sampler.size() -1);
	glUseProgram(0);
}

/*void Shader::setUniform(std::string _uniform, int _value)
{
	GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());
	if (uniformId == -1) { throw std::exception(); }


	glUseProgram(m_id);
	glUniform1i(uniformId, _value);
	glUseProgram(0);
} */

GLuint Shader::getId()
{
	return m_id;
}
