#ifndef _COMPONENTS_H_
#define _COMPONENTS_H_

#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Collision.h"



class Component
{

};



class Shape : public Component
{
public:
	VertexArray * m_vAO; // The shape's mesh/obj
	VertexBuffer *m_vBOt; // The vertex buffer for texture co-ordinates
	VertexBuffer *m_vBOp; // The vertex buffer for object co-ordinates
	Texture *m_tex;

	bool isSolid() { return m_solid; }
	void setSolid(bool _solid) { m_solid = _solid; }
	glm::vec3 getSize() { return m_size; }

	void setScale(float _sX, float _sY, float _sZ) { m_scale.x = _sX; m_scale.y = _sY; m_scale.z = _sZ; }
	glm::vec3 getScale() { return m_scale; }
	float getMass() { return m_mass; }

	void rotate(glm::vec3 _change) { m_rotation += _change; }
	void setRotation(float _rotX, float _rotY, float _rotZ) { m_rotation.x = _rotX; m_rotation.y = _rotY; m_rotation.z = _rotZ; }
	glm::mat4 getModel() { return m_model; }
	void setModel(glm::mat4 _model) { m_model = _model; }


protected:
	
	glm::mat4 m_model;
	bool m_solid;
	float m_mass;
	glm::vec3 m_rotation;
	glm::vec3 m_size; // The size of the obj in generic units (ie: box objs are 1/1/1 units)
	glm::vec3 m_scale;
};


class Sphere : public Shape
{
public:
	Sphere(std::string _texName, float _radius);
	float getRadius() { return m_radius; }
	virtual void setScale(float _radius) { m_scale.x = _radius; m_scale.y = _radius; m_scale.z = _radius; }

private:
	float m_radius;

};



class Plane : public Shape
{
public:
	Plane(std::string _texName, glm::vec3 _scale, glm::vec3 _normal);
	glm::vec3 getNorm() { return m_normal; }
	void setNorm(glm::vec3 _norm) { m_normal = _norm; }
	
private:
	glm::vec3 m_normal;
};


class Box : public Shape
{
public:
	Box(std::string _texName, glm::vec3 _scale);

private:
	std::vector<Plane> m_face;
};


class Mesh : public Shape
{
public:
	Mesh(std::string _texName, std::string _obj, glm::vec3 _scale, glm::vec3 _size);

private:

};



class PhysicsObj : public Component
{
public:
	PhysicsObj(float _mass, float _bounciness);
	PhysicsObj();

	void addForce(glm::vec3 _force) { m_force += _force; }
	void clearForces() { m_force = glm::vec3(0.0f, 0.0f, 0.0f); }
	void euler(float _deltaTs);

	glm::vec3 rungeKutta2(float _deltaTs, float _mass);
	void rungeKutta4(float _deltaTs);

	void setForce(const glm::vec3 _force) {	m_force = _force;}
	glm::vec3 getVelocity() { return m_velocity; }
	void setVelocity(const glm::vec3 _vel) { m_velocity = _vel; }

	float getBounciness() { return m_bounciness; }
	void setBounciness(float _amt) { m_bounciness = _amt; }

	float getMass() { return m_mass; }
	void setMass(float _mass) { m_mass = _mass; }

	const glm::vec3 getForce() const { return m_force; }

	glm::vec3 getPermCP() { return m_permCP; }
	void setPermCP(glm::vec3 _pos) { m_permCP = _pos; }

	std::vector<Collision*> m_collisions;

	void setCollided(bool _val) { m_collided = _val; }
	bool collided() { return m_collided; }
	void resetCollisions();
	void startSimulation(bool _start) { m_start = _start; }

private:
	glm::vec3 m_permCP;
	float m_mass;
	float m_bounciness;
	glm::vec3 m_velocity;
	glm::vec3 m_force;
	bool m_collided;
	float m_resist;
	bool m_start;
};


#endif