#ifndef _DynamicObject_H_
#define _DynamicObject_H_

#include "GameObject.h"
#include "Utility.h"
#include <iostream>

/*! \brief Brief description.
*  This physics dynamic object class is derived from the GameObject class, as a one type/class of game objects
*  It sets up parameters for physics computation and calls certain physics algorithms.
*  It returns the position and orientation of the object for the visualisation engine to display.
*  It is important to not include any graphics drawings in this class. This is the principle of the separation
*  of physics computation from graphics
*
*/

class DynamicObject : public GameObject
{
public:

	
	DynamicObject(glm::vec3 _startPos, glm::vec3 _scale, float _mass, float _bounciness, std::string _texName, std::string _type, std::string _tag);	
	~DynamicObject();


	virtual void update(float _deltaTs, std::vector<GameObject *> _objects);

	
	void addForce(glm::vec3 _force) { m_force += _force; }
	void clearForces() { m_force = glm::vec3(0.0f, 0.0f, 0.0f); }
	
	 void euler(float _deltaTs);
	 void rungeKutta2(float _deltaTs);
	 void rungeKutta4(float _deltaTs);

	void setForce(const glm::vec3 _force) { m_force = _force; }
	
	void setMass(float _mass) { m_mass = _mass; }

	void setBoundingRadius(float _r) { m_bRadius = _r; }

	void collide(float _deltaTs, std::vector<GameObject *> _objects);

	
	void setVelocity(const glm::vec3 _vel) { m_velocity = _vel; }
	
	const glm::vec3 getForce() const { return m_force; }

	const float getMass() const { return m_mass; }
	
	const float getBoundingRadius() const { return m_bRadius; }
	
	const glm::mat4 getOrientation() const { return m_orientation; }

	void updateModelMatrix();
	void startSimulation(bool _start) { m_start = _start; }
	
private:

	
	
	glm::vec3 m_permCP;
	float m_bounciness;
	glm::vec3 m_force;
	
	glm::vec3 m_velocity;
	
	float m_mass;
	float m_gravity; //World Constants
	float m_resist;

	/** The radius of a bounding sphere of the object
	*/
	bool m_colliding;
	bool m_colPoint;
	float m_bRadius;
	
	glm::mat4 m_orientation;

	bool m_start;
};

#endif 

