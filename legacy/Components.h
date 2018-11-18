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


class Component
{

};

class PhysicsObj : public Component
{
public:
	void addForce(glm::vec3 _force) { m_force += _force; }
	void clearForces() { m_force = glm::vec3(0.0f, 0.0f, 0.0f); }
	void euler(float _deltaTs);

	glm::vec3 rungeKutta2(float _deltaTs, float _mass);
	void rungeKutta4(float _deltaTs);

	void setForce(const glm::vec3 _force) {
		m_force = _force;
	}
	void setMass(float _mass) { m_mass = _mass; }
	float getMass() const { return m_mass; }
	glm::vec3 getVelocity() { return m_velocity; }
	void setVelocity(const glm::vec3 _vel) { m_velocity = _vel; }
	float getBounciness() { return m_bounciness; }

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
	float m_bounciness;
	glm::vec3 m_force;
	bool m_collided;
	glm::vec3 m_velocity;

	float m_mass;
	float m_resist;
	bool m_start;
};