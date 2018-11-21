#include <iostream>
#include "Physics.h"



void Physics::update(GameObject * _my, std::vector<GameObject*> _other, float _dT)
{
	float gravity = m_gravity * _my->m_rb->getMass(); 
	_my->m_rb->addForce(glm::vec3(0.0f, gravity, 0.0f)); //Apply force due to gravity
	glm::vec3 nextPos = _my->getPosition() + _my->m_rb->getVelocity() * _dT;
	collide(_dT, _other, _my, nextPos); // Check Collisions
	_my->setPosition(_my->m_rb->rungeKutta2(_dT, _my->m_rb->getMass())); // Move via Runge Kutta 2
	_my->m_rb->clearForces();
}

bool Physics::collide(float _dT, std::vector<GameObject*> _objects, GameObject* _my, glm::vec3 _c1)
{
	for (int i = 0; i < _objects.size(); i++) // Check every object
	{
		if (_objects[i]->m_shapeComp->isSolid() && _objects[i]->isActive()) // Don't check collisions against inactive objects and against non-solids
		{			
			if (_objects[i]->getTag() == _my->getTag()) // Don't collide with yourself
			{
				std::string otherShape = _objects[i]->getShape(); // The other object type
				std::string myShape = _my->getShape(); // My object type
				bool collision = false; 

				if (myShape == "sphere") // If current object is a sphere
				{
					//Y + P
					if (otherShape == "sphere")
					{
						collision = utility::sphereToSphere(_my, _objects[i], _c1);
						_my->m_rb->setCollided(collision);
					}


					//Y + P
					else if (otherShape == "plane")
					{

					}

					else if (otherShape == "mesh")
					{

					}

					else if (otherShape == "box")
					{


					}
				}

				else if (myShape == "box")
				{
					if (otherShape == "sphere")
					{

					}


					//Y + P
					else if (otherShape == "plane")
					{

					}

					else if (otherShape == "mesh")
					{

					}

					else if (otherShape == "box")
					{


					}

				}


				else if (myShape == "mesh")
				{
					if (otherShape == "sphere")
					{

					}



					else if (otherShape == "plane")
					{

					}

					else if (otherShape == "mesh")
					{

					}

					else if (otherShape == "box")
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
		_object->m_rb->setVelocity(_object->m_rb->getVelocity() + collision[i]->m_deltaVel);
		
	}
	_object->m_rb->resetCollisions();
}


