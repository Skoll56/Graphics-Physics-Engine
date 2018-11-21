#include "Collision.h"

Collision::Collision(glm::vec3 _cP, glm::vec3 _norm, GameObject* _other, GameObject* _my)
{
	m_cP = _cP;
	m_normal = _norm;

	float invBounce = 0.0f - (1 + _my->m_rb->getBounciness());
	glm::vec3 otherVel;
	float otherMass;
	if (!_other->isPhysics()) // If the other object isn't a physics object
	{
		otherVel = glm::vec3(0.0f, 0.0f, 0.0f);
		otherMass = INFINITY;
	}
	else // If it is
	{
		otherVel = _other->m_rb->getVelocity();
		otherMass = _other->m_rb->getMass();
	}

	m_velDif = _my->m_rb->getVelocity() - otherVel;
	m_massCalc = (1.0f / _my->m_rb->getMass()) + (1.0f / otherMass);
	m_resultForce = glm::dot(invBounce * m_velDif, m_normal) / m_massCalc;
	m_deltaVel = (m_resultForce * m_normal) / _my->m_rb->getMass();

	// Write response code here
}