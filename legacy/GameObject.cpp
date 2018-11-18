#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "GameObject.h"

/*! \brief Brief description.
*  GameObject class contains a mesh, a material, a position and an orientation information
*  about the game object. This should be a base class for different types of game object.
*
*/


GameObject::GameObject(glm::vec3 _startPos)
{	
	m_position = _startPos;	
	m_mass = INFINITY;
	m_solid = true;
	m_active = true;
	m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	m_tag = "NO TAG";
}

/*(GameObject::GameObject(glm::vec3 _startPos, glm::vec3 _scale, glm::vec3 _normal, int _i)
{
	float offset = 0.0f;
	glm::vec3 hScale = (_scale / 2.0f) + offset;
	m_position = _startPos;
	m_scale = _scale;
	m_normal = _normal;
	m_type = "face";

	if (_i == 0)
	{
		m_position.y += hScale.y; //Top
		m_normal = glm::vec3(0.0f, 1.0f, 0.0f);
		m_scale.y = 0.0f;
	}

	else if (_i == 1)
	{
		m_position.y -= hScale.y; //Bottom
		m_normal = glm::vec3(0.0f, 1.0f, 0.0f);
		m_scale.y = 0.0f;
		
	}

	else if (_i == 2)
	{
		m_position.x -= hScale.x; //Left
		m_normal = glm::vec3(1.0f, 0.0f, 0.0f);
		m_scale.x = 0.0f;
	}

	else if (_i == 3)
	{
		m_position.x += hScale.x; //Right
		m_normal = glm::vec3(1.0f, 0.0f, 0.0f);
		m_scale.x = 0.0f;
	}

	else if (_i == 4)
	{
		m_position.z -= hScale.z; //Towards
		m_normal = glm::vec3(0.0f, 0.0f, 1.0f);
		m_scale.z = 0.0f;
	}

	else if (_i == 5)
	{
		m_position.z += hScale.z; //Away
		m_normal = glm::vec3(0.0f, 0.0f, 1.0f);
		m_scale.z = 0.0f;
	}
} */

GameObject::~GameObject()
{
	// Do any clean up here
}

void GameObject::addPhysics(std::string _tag, float _mass, float _bounciness)
{
	m_rb = new PhysicsObj();
	m_physics = true;
	m_tag =  _tag;
	m_mass = _mass;
	m_bounciness = _bounciness;
	m_rb->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
}

void GameObject::removePhysics()
{
	m_physics = false;
	m_mass = INFINITY;
	m_bounciness = 0.0f;
	m_rb->clearForces();
	m_rb->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
	delete m_rb;
}

