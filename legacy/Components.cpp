#include "Components.h"

glm::vec3 PhysicsObj::rungeKutta2(float _deltaTs, float _mass)
{
	glm::vec3 a = m_force / _mass;
	glm::vec3 k1 = _deltaTs * a; // Step one, ordinary Euler calculation at t= 0
	glm::vec3 k2 = (_deltaTs / 2.0f) * a + k1 / 2.0f;  // Evaluate again at t= 0.5 before adjusting the velocity
	m_velocity += k2;
	return (m_velocity * _deltaTs);
}


Collision::Collision(glm::vec3 _cP, glm::vec3 _norm, GameObject* _other, GameObject* _my)
{
	m_cP = _cP;
	m_normal = _norm;

	float invBounce = 0.0f - (1 + _my->m_rb->getBounciness());
	m_velDif = _my->getVelocity() - _other->getVelocity();
	m_massCalc = (1.0f / _my->getMass()) + (1.0f / _other->getMass());
	m_resultForce = glm::dot(invBounce * m_velDif, m_normal) / m_massCalc;
	m_deltaVel = (m_resultForce * m_normal) / _my->getMass();

	// Write response code here
}

void PhysicsObj::resetCollisions()
{
	m_collisions.clear();
	m_collided = false;
}