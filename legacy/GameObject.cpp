#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "GameObject.h"

/*! \brief Brief description.
*  GameObject class contains a mesh, a material, a position and an orientation information
*  about the game object. This should be a base class for different types of game object.
*
*/


GameObject::GameObject(glm::vec3 _startPos, glm::vec3 _scale, std::string _texName, std::string _type, std::string _tag)
{
	m_vBOp = new VertexBuffer();
	m_vBOt = new VertexBuffer();
	m_vAO = new VertexArray();
	m_tex = new Texture();
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_position = _startPos;
	m_scale = _scale;
	m_tex->addTexture(_texName);
	m_normal = glm::vec3(0.0f, 1.0f, 0.0f);
	m_mass = INFINITY;
	m_type = _type;
	m_tag = _tag;
	m_solid = true;
	m_active = true;
}

GameObject::~GameObject()
{
	// Do any clean up here
}

void GameObject::update(float _dTime, std::vector <GameObject*> _objects)
{
	
}


void GameObject::activate()
{
	m_active = true;
}

bool GameObject::isActive()
{
	return m_active;
}


