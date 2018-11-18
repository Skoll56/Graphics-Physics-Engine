#ifndef _SHAPES_H_
#define _SHAPES_H_

#include "GameObject.h"


class Sphere : public GameObject
{
public:
	Sphere(glm::vec3 _startPos, glm::vec3 _scale, std::string _texName);
	float getRadius() { return m_radius; }

private:
	float m_radius;
};



class Plane : public GameObject
{
public:
	Plane(glm::vec3 _startPos, glm::vec3 _scale, glm::vec3 _normal, std::string _texName);
	glm::vec3 getNorm() { return m_normal; }
	void setNorm(glm::vec3 _norm) { m_normal = _norm; }

private:
	glm::vec3 m_normal;
};



class Box : public GameObject
{
public:
	Box(glm::vec3 _startPos, glm::vec3 _scale, std::string _texName);

private:
	std::vector<Plane> m_face;
};

class Mesh : public GameObject
{
public:
	Mesh(glm::vec3 _startPos, glm::vec3 _scale, glm::vec3 _size, std::string _texName, std::string _obj);

private:
	
};

#endif