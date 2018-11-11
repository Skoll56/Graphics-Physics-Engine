#include "DynamicObject.h"
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>

DynamicObject::DynamicObject(glm::vec3 _startPos, glm::vec3 _scale, float _mass, float _bounciness, std::string _texName, std::string _type, std::string _tag)
{
	m_vBOp = new VertexBuffer();
	m_vBOt = new VertexBuffer();
	m_vAO = new VertexArray();
	m_tex = new Texture();
	m_tag = _tag;
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_position = _startPos;
	m_tex->addTexture(_texName);
	m_scale = _scale;
	m_resist = 0.1f;
	m_mass = _mass;
	m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	m_gravity = m_mass * -0.981f;
	m_bRadius = _scale.y;
	m_bounciness = _bounciness;
	m_type = _type;
	m_solid = true;
	m_active = true;
}

DynamicObject::~DynamicObject()
{
}

void DynamicObject::update(float _deltaTs, std::vector<GameObject *> _objects)
{
	addForce(glm::vec3(0.0f, m_gravity, 0.0f));
	collide(_deltaTs, _objects);
	rungeKutta2(_deltaTs);
	std::cout << m_position.x << "<< " << std::endl;
	clearForces();
	updateModelMatrix();
}

void DynamicObject::euler(float _deltaTs)
{
	glm::vec3 a = m_force / m_mass;
	m_velocity += a * _deltaTs;
	m_position += m_velocity * _deltaTs;
}

void DynamicObject::rungeKutta2(float _deltaTs)
{
	glm::vec3 a = m_force / m_mass;
	glm::vec3 k1 = _deltaTs * a; // Step one, ordinary Euler calculation at t= 0
	glm::vec3 k2 = (_deltaTs / 2.0f) * a + k1 / 2.0f;  // Evaluate again at t= 0.5 before adjusting the velocity
	m_velocity += k2;
	m_position += m_velocity * _deltaTs;

}

void DynamicObject::rungeKutta4(float _deltaTs)
{
}

void DynamicObject::collide(float _deltaTs, std::vector<GameObject *> _objects)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		if (_objects[i]->getTag() != m_tag) // Don't check collisions against yourself
		{
			if (_objects[i]->isSolid() && _objects[i]->isActive()) // Don't collide with inactive or non-solid objects
			{
				float d = glm::length(_objects[i]->getPosition() - m_position);
				if (d < 500.0f || d > -500.0f)									// Don't bother checking objects that are really far away
				{
					std::string shape = _objects[i]->getType(); // Shape = the object shape we're colliding with 
					glm::vec3 nextPos = m_position + m_velocity * _deltaTs; // Where we'd land next frame

					
					if (m_type == "sphere") // If current object is a sphere
					{
						if (shape == "sphere")
						{
							glm::vec3 sN; // Sphere-normal between the two spheres
							glm::vec3 sPos = _objects[i]->getPosition();
							float sRadius = _objects[i]->getRadius();
							glm::vec3 cPS; //Contact point sphere
							bool collisionSphere = utility::sphereToSphere(m_position, sPos, m_bRadius, sRadius, cPS, sN);

							if (collisionSphere)
							{
								float invBounce = 0.0f - (1 + m_bounciness);
								glm::vec3 velDif = m_velocity - glm::vec3(0.0f, 0.0f, 0.0f);
								float massCalc = (1.0f / m_mass) + (1.0f / _objects[i]->getMass());
								float resultForce = glm::dot(invBounce * velDif, sN) / massCalc;
								m_velocity += (resultForce * sN) / m_mass;
								setPosition(cPS);
							}
						}

						else if (shape == "plane")
						{
							glm::vec3 cPP; //Contact point plane
							glm::vec3 pNorm = _objects[i]->getNorm();
							glm::vec3 pPos = _objects[i]->getPosition();
							bool collisionPlane = utility::sphereToPlane(m_position, nextPos, m_bRadius, cPP, m_permCP, _objects[i]);

							if (collisionPlane)
							{
								float invBounce = 0.0f - (1 + m_bounciness);
								glm::vec3 velDif = m_velocity - glm::vec3(0.0f, 0.0f, 0.0f);
								float massCalc = (1.0f / m_mass) + (1.0f / _objects[i]->getMass());
								float resultForce = glm::dot(invBounce * velDif, pNorm) / massCalc;
								m_velocity += (resultForce * pNorm) / m_mass;
								setPosition(cPP);
							}
						}

						else if (shape == "mesh")
						{
							
						}

						else {}
					}

					else if (m_type == "box")
					{
						// Do box-box collisions, box-plane collisions and box-sphere collisions


						if (shape == "sphere")
						{


							//if (collisionSphere)
							{

							}
						}

						else if (shape == "plane")
						{


							//if (collisionPlane)
							{

							}
						}

						else if (shape == "box")
						{

							bool collisionBox = utility::boxToBox(_objects[i], m_position, m_scale);

							if (collisionBox)
							{
								m_position.y = 20.0f;
							}

						}

						else 
						{ 
							// Alien detected. Dunno.
						}


					}

					else if (m_type == "mesh")
					{
						if (shape == "mesh")
						{
							bool collideMesh = false;
							VertexBuffer *myTriPos = m_vAO->getTriPos();
							VertexBuffer *otherTriPos = _objects[i]->m_vAO->getTriPos();
							for (int o = 0; o < otherTriPos->getDataSize() - 9; o + 9)
							{
								float u1x = otherTriPos->getData(o);
								float u1y = otherTriPos->getData(o+1);
								float u1z = otherTriPos->getData(o+2);

								float u2x = otherTriPos->getData(o+3);
								float u2y = otherTriPos->getData(o + 4);
								float u2z = otherTriPos->getData(o + 5);

								float u3x = otherTriPos->getData(o + 6);
								float u3y = otherTriPos->getData(o + 7);
								float u3z = otherTriPos->getData(o + 8);

								float u1[3] = { u1x, u1y, u1z };
								float u2[3] = { u2x, u2y, u2z };
								float u3[3] = { u3x, u3y, u3z };


								for (int i = 0; i < myTriPos->getDataSize() - 9; i + 9)
								{

									float v1x = myTriPos->getData(i);
									float v1y = myTriPos->getData(i + 1);
									float v1z = myTriPos->getData(i + 2);

									float v2x = myTriPos->getData(i + 3);
									float v2y = myTriPos->getData(i + 4);
									float v2z = myTriPos->getData(i + 5);

									float v3x = myTriPos->getData(i + 6);
									float v3y = myTriPos->getData(i + 7);
									float v3z = myTriPos->getData(i + 8);

									float v1[3] = { v1x, v1y, v1z };
									float v2[3] = { v2x, v2y, v2z };
									float v3[3] = { v3x, v3y, v3z };

									bool collideTri = utility::NoDivTriTriIsect(v1, v2, v3, u1, u2, u3);
									if (collideTri) 
									{ 
										collideMesh = true; 
									}
								}
							}
							//
							if (collideMesh)
							{
								setPosition(glm::vec3(0.0f, 20.0f, 0.0f));
							}

						}

					}
				}
			}

		}

	}

	
	


	

	
}

void DynamicObject::updateModelMatrix()
{
	//m_modelMatrix = glm::translate(glm::mat4(1.0f), m_position);
	//m_modelMatrix = glm::scale(m_modelMatrix, m_scale);
}
