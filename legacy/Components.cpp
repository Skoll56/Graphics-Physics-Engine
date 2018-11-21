#include "Components.h"

PhysicsObj::PhysicsObj(float _mass, float _bounciness)
{
	m_mass = _mass;
	m_bounciness = _bounciness;
}

PhysicsObj::PhysicsObj()
{
	m_mass = 10.0f;
	m_bounciness = 0.0f;
}

glm::vec3 PhysicsObj::rungeKutta2(float _deltaTs, float _mass)
{
	glm::vec3 a = m_force / _mass;
	glm::vec3 k1 = _deltaTs * a; // Step one, ordinary Euler calculation at t= 0
	glm::vec3 k2 = (_deltaTs / 2.0f) * a + k1 / 2.0f;  // Evaluate again at t= 0.5 before adjusting the velocity
	m_velocity += k2;
	return (m_velocity * _deltaTs);
}




void PhysicsObj::resetCollisions()
{
	m_collisions.clear();
	m_collided = false;
}

Box::Box(std::string _texName, glm::vec3 _scale)
{
	m_vBOp = new VertexBuffer();
	m_vBOt = new VertexBuffer();
	m_vAO = new VertexArray();
	m_tex = new Texture();
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_size = glm::vec3(1.0f, 1.0f, 1.0f);
	m_scale = _scale;
	m_solid = true;
	m_tex->addTexture(_texName);
	m_vAO->loadObj("1b1cube.obj");
}

Plane::Plane(std::string _texName, glm::vec3 _scale, glm::vec3 _normal)
{
	m_vBOp = new VertexBuffer();
	m_vBOt = new VertexBuffer();
	m_vAO = new VertexArray();
	m_tex = new Texture();
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_scale = _scale;
	m_tex->addTexture(_texName);
	m_size = glm::vec3(1.0f, 0.0f, 1.0f);
	m_mass = INFINITY;
	m_solid = true;
	m_normal = _normal;
	m_vAO->loadObj("1b1plane.obj");
	m_tex->addTexture(_texName);
	

}

Sphere::Sphere(std::string _texName, float _radius)
{
	m_vBOp = new VertexBuffer();
	m_vBOt = new VertexBuffer();
	m_vAO = new VertexArray();
	m_tex = new Texture();
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_scale = glm::vec3(_radius, _radius, _radius);
	m_tex->addTexture(_texName);
	m_size = glm::vec3(1.0f, 1.0f, 1.0f);
	m_mass = INFINITY;
	m_solid = true;
	m_radius = _radius;
	m_vAO->loadObj("1b1sphere.obj");
	m_tex->addTexture(_texName);
	
}

Mesh::Mesh(std::string _texName, std::string _obj, glm::vec3 _scale, glm::vec3 _size)
{
	m_vBOp = new VertexBuffer();
	m_vBOt = new VertexBuffer();
	m_vAO = new VertexArray();
	m_tex = new Texture();
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_scale = _scale;
	m_tex->addTexture(_texName);
	m_size = _size;
	m_mass = INFINITY;
	m_solid = true;
	m_vAO->loadObj(_obj);
	m_tex->addTexture(_texName);
	
}
