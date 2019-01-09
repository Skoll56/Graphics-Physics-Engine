#ifndef _COLLISION_H_
#define _COLLISION_H_


class GameObject;

class Collision
{
public:
	Collision(glm::vec3 _cP, glm::vec3 _norm, GameObject* _other, GameObject* _my);
	void ignoreCollision();
	GameObject* m_other;
	GameObject* m_my;
	glm::vec3 m_poC; // Point of contact
	glm::vec3 m_cP; // Contact Position
	glm::vec3 m_normal; // The normal of the collision
	float m_resultForce;
	glm::vec3 m_velDif;
	glm::vec3 m_fric;
	float m_massCalc;
	glm::vec3 m_deltaVel; // The change in velocity this object will have
	bool m_constCol;
};

#endif