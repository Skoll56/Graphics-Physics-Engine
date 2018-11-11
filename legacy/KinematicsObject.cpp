#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "KinematicsObject.h"

KinematicsObject::KinematicsObject(glm::vec3 _startPos, glm::vec3 _scale, std::string _texName)
{
	m_vBOp = new VertexBuffer();
	m_vBOt = new VertexBuffer();
	m_vAO = new VertexArray();
	m_tex = new Texture();
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_position = _startPos;
	m_scale = _scale;
	m_gravity = -0.981f;
	m_tex->addTexture(_texName);
	m_resist = 0.1f;
}

KinematicsObject::~KinematicsObject()
{
}

void KinematicsObject::Update(float _deltaTs)
{
	
	m_position.y  += (m_velocity.y + (m_velocity.y + m_gravity * _deltaTs) / 2) * _deltaTs;
	m_position.x  += (m_velocity.x + (m_velocity.x + m_resist * _deltaTs) / 2) * _deltaTs;

	m_velocity.y = (m_velocity.y + m_gravity * _deltaTs);
	m_velocity.x = (m_velocity.x + m_resist * _deltaTs);
	
}

void KinematicsObject::updateModelMatrix()
{
	//m_modelMatrix = glm::translate(glm::mat4(1.0f), m_position);
	//m_modelMatrix = glm::scale(m_modelMatrix, m_scale);
}

void KinematicsObject::Stop()
{
	setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
}
