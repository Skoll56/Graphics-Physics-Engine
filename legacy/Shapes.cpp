#include "Shapes.h"

/*
GameObject owns:
-Rotation
-Position
-Scale
-Size
-Type
-Tag
-Solid
-Active
-Mass

*/


Sphere::Sphere(glm::vec3 _startPos, glm::vec3 _scale, std::string _texName)
{
	m_vBOp = new VertexBuffer();
	m_vBOt = new VertexBuffer();
	m_vAO = new VertexArray();
	m_tex = new Texture();
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_position = _startPos;
	m_scale = _scale;
	m_tex->addTexture(_texName);
	m_size = glm::vec3(1.0f, 1.0f, 1.0f);
	m_mass = INFINITY;
	m_type = "sphere";
	m_solid = true;
	m_active = true;
	m_radius = _scale.y;
	m_vAO->loadObj("1b1sphere.obj");
}

Plane::Plane(glm::vec3 _startPos, glm::vec3 _scale, glm::vec3 _normal, std::string _texName)
{
	m_vBOp = new VertexBuffer();
	m_vBOt = new VertexBuffer();
	m_vAO = new VertexArray();
	m_tex = new Texture();
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_position = _startPos;
	m_scale = _scale;
	m_tex->addTexture(_texName);
	m_size = glm::vec3(1.0f, 1.0f, 1.0f);
	m_mass = INFINITY;
	m_type = "plane";
	m_solid = true;
	m_active = true;
	m_normal = _normal;
	m_vAO->loadObj("1b1plane.obj");
}


Box::Box(glm::vec3 _startPos, glm::vec3 _scale, std::string _texName)
{
	m_vBOp = new VertexBuffer();
	m_vBOt = new VertexBuffer();
	m_vAO = new VertexArray();
	m_tex = new Texture();
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_position = _startPos;
	m_scale = _scale;
	m_tex->addTexture(_texName);
	m_size = glm::vec3(1.0f, 1.0f, 1.0f);
	m_mass = INFINITY;
	m_type = "box";
	m_solid = true;
	m_active = true;
	m_vAO->loadObj("1b1cube.obj");
}

Mesh::Mesh(glm::vec3 _startPos, glm::vec3 _scale, glm::vec3 _size, std::string _texName, std::string _obj)
{
	m_vBOp = new VertexBuffer();
	m_vBOt = new VertexBuffer();
	m_vAO = new VertexArray();
	m_tex = new Texture();
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_position = _startPos;
	m_scale = _scale;
	m_tex->addTexture(_texName);
	m_size = _size;
	m_mass = INFINITY;
	m_type = "mesh";
	m_solid = true;
	m_active = true;
	m_vAO->loadObj(_obj);
}