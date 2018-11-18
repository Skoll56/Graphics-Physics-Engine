#include "Physics.h"
#include "Utility.h"
#include <iostream>

void Physics::update(GameObject * _my, std::vector<GameObject*> _other, float _dT)
{
	float gravity = m_gravity * _my->getMass(); 
	_my->setVelocity(_my->m_rb->getVelocity());
	_my->m_rb->addForce(glm::vec3(0.0f, gravity, 0.0f)); //Apply force due to gravity
	glm::vec3 nextPos = _my->getPosition() + _my->getVelocity() * _dT;
	collide(_dT, _other, _my, nextPos); // Check Collisions
	_my->setPosition(_my->m_rb->rungeKutta2(_dT, _my->getMass())); // Move via Runge Kutta 2
	_my->m_rb->clearForces();
}

bool Physics::collide(float _dT, std::vector<GameObject*> _objects, GameObject* _my, glm::vec3 _c1)
{
	for (int i = 0; i < _objects.size(); i++) // Check every object
	{
		if (_objects[i]->isSolid() && _objects[i]->isActive()) // Don't check collisions against inactive objects and against non-solids
		{
			bool cancel = false;
			
			if (_objects[i]->getTag() == _my->getTag()) // Don't collide with yourself
			{

				std::string shape = _objects[i]->getType(); // The other object type
				std::string type = _my->getType(); // My object type


				if (type == "sphere") // If current object is a sphere
				{
					//Y + P
					if (shape == "sphere")
					{
						_my->m_rb->setCollided(utility::sphereToSphere(_my, _objects[i], _c1));
					}


					//Y + P
					else if (shape == "plane")
					{

					}

					else if (shape == "mesh")
					{

					}

					else if (shape == "box")
					{


					}
				}

				else if (type == "box")
				{
					if (shape == "sphere")
					{

					}


					//Y + P
					else if (shape == "plane")
					{

					}

					else if (shape == "mesh")
					{

					}

					else if (shape == "box")
					{


					}

				}


				else if (type == "mesh")
				{
					if (shape == "sphere")
					{

					}



					else if (shape == "plane")
					{

					}

					else if (shape == "mesh")
					{

					}

					else if (shape == "box")
					{


					}

				}  // End of collision code



				
			}

		}

	}
		
	
	return false;
}

void Physics::handleCollisions(GameObject * _object)
{
	std::vector<Collision*> collision = _object->m_rb->m_collisions;
	for (int i = 0; i < collision.size(); i++)
	{
		_object->setPosition(collision[i]->m_cP);
		_object->m_rb->setVelocity(_object->getVelocity() + collision[i]->m_deltaVel);
		
	}
	_object->m_rb->resetCollisions();
}


