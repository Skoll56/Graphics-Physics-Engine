#ifndef _COLLISION_H_
#define _COLLISION_H_

#include <glm/glm.hpp>
#include "GameObject.h"

struct Collision
{
	Collision(glm::vec3 _cP, glm::vec3 _norm, GameObject* _other, GameObject* _my);
	glm::vec3 m_cP; // Contact Point
	glm::vec3 m_normal; // The normal of the collision
	float m_resultForce;
	glm::vec3 m_velDif;
	float m_massCalc;
	glm::vec3 m_deltaVel; // The change in velocity this object will have
};

#endif