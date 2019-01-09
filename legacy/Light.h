#include <glm/glm.hpp>



struct PointLight
{
	PointLight() {};
	PointLight(glm::vec3 _pos, glm::vec3 _diffuse, float _specular, float _radius, float _quadratic)
	{
		m_pos = _pos;
		m_diffuse = _diffuse;
		m_specIntens = _specular;
		m_radius = _radius;
		m_quadratic = _quadratic;
		
	}
	glm::vec3 getPos() { return m_pos; }
	glm::vec3 getDif() { return m_diffuse; }
	float getSpec() { return m_specIntens; }

	glm::vec3 m_pos;
	glm::vec3 m_diffuse;
	float m_specIntens;
	float getRadius() { return m_radius; }
	float getQuad() { return m_quadratic; }
	float m_radius;
	float m_quadratic;
};

struct DirLight
{

	DirLight(glm::vec3 _diffuse, float _specular, glm::vec3 _ambient, glm::vec3 _direction)
	{
		m_diffuse = _diffuse;
		m_specIntens = _specular;
		m_ambient = _ambient;
		m_direction = _direction;
	}

	glm::vec3 getDif() { return m_diffuse; }
	float getSpec() { return m_specIntens; }

	glm::vec3 m_diffuse;
	float m_specIntens;
	glm::vec3 getDirection() { return m_direction; }
	glm::vec3 getAmb() { return m_ambient; }


	glm::vec3 m_direction;
	glm::vec3 m_ambient;
};

struct SpotLight
{
	SpotLight(glm::vec3 _pos, glm::vec3 _diffuse, float _specular, float _angle, float _fadeAngle, float _radius, float _quadratic, glm::vec3 _direction)
	{
		m_pos = _pos;
		m_diffuse = _diffuse;
		m_specIntens = _specular;
		m_angle = _angle;
		m_direction = _direction;
		m_fadeAngle = _fadeAngle;
		m_radius = _radius;
		m_quadratic = _quadratic;
		m_antiLight = 0;
	}
	float getAngle() { return m_angle; }
	float getFangle() { return m_fadeAngle; }
	glm::vec3 getDirection() { return m_direction; }
	glm::vec3 getPos() { return m_pos; }
	glm::vec3 getDif() { return m_diffuse; }
	float getSpec() { return m_specIntens; }
	float getRadius() { return m_radius; }
	float getQuad() { return m_quadratic; }
	int m_antiLight;
	glm::vec3 m_pos;
	glm::vec3 m_diffuse;
	float m_specIntens;
	float m_angle;
	float m_fadeAngle;
	float m_radius;
	float m_quadratic;
	glm::vec3 m_direction;
};