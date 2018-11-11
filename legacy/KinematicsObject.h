#ifndef _KinematicsObject_H_
#define _KinematicsObject_H_

#include "GameObject.h"

/*! \brief Brief description.
*  Physics object class is derived from the GameObject class, as a one type/class of game objects
*  It sets up parameters for physics computation and calls certain physics algorithms.
*  It returns the position and orientation of the object for the visualisation engine to display.
*  It is important to not include any graphics drawings in this class. This is the principle of the separation 
*  of physics computation from graphics
*
*/

class KinematicsObject : public GameObject
{
public:

	
	KinematicsObject(glm::vec3 _startPos, glm::vec3 _scale, std::string _texName);
	KinematicsObject() {};
	~KinematicsObject();

	
	virtual void Update(float _deltaTs);

	
	//void SetPosition(glm::vec3 pos) { m_position = pos; }

	void Stop();
	float getRadius() { return m_scale.y; }
	void setVelocity(glm::vec3 _vel) { m_velocity = _vel; }

	glm::vec3 getVelocity() { return m_velocity; }
	
	//void SetScale(glm::vec3 scale) { m_scale = scale; }
	
	//glm::vec3 GetPosition() { return _position; }
	
	glm::mat4 getOrientation() { return m_orientation; }
	void updateModelMatrix();
	
	void startSimulation(bool _start) { m_start = _start; }

protected:

	
	
	float m_gravity; //World Constants
	float m_resist; 
	
	glm::vec3 m_position;
	glm::vec3 m_velocity;
	
	glm::vec3 m_scale;
	
	glm::mat4 m_orientation;
	
	glm::vec3 m_rotation;
	bool m_start;
};

#endif //!_KinematicsObject_H_
