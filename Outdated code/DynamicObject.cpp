#include "DynamicObject.h"
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>

/*DynamicObject::DynamicObject(glm::vec3 _startPos, glm::vec3 _scale, float _mass, float _bounciness, glm::vec3 _size, std::string _texName, std::string _type, std::string _tag)
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
	m_size = _size;
	MeshCol col;	

} 

DynamicObject::~DynamicObject()
{
}

void DynamicObject::update(float _deltaTs, std::vector<GameObject *> _objects, int _i)
{

	addForce(glm::vec3(5.0f, m_gravity, 0.0f));
	collide(_deltaTs, _objects, _i);
	std::cout << m_position.x << std::endl;
	rungeKutta2(_deltaTs);
	clearForces();
	//updateModelMatrix();
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

void DynamicObject::collide(float _deltaTs, std::vector<GameObject *> _objects, int _i)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		if (_objects[i]->getTag() != m_tag) // Don't check collisions against yourself
		{
			if (_objects[i]->isSolid() && _objects[i]->isActive()) // Don't collide with inactive or non-solid objects
			{
				//bool collisionBox = utility::boxToBox(_objects[i], m_position, m_scale, m_size);
				VertexBuffer *TriPos = _objects[i]->m_vAO->getTriPos();
				{

					int partition2 = 9;
					if (TriPos->getDataSize() > 450)
					{
						partition2 *= 2;
					}

					if (TriPos->getDataSize() > 1500)
					{
						partition2 *= 2;
					}

					if (TriPos->getDataSize() > 3000)
					{
						partition2 *= 2;
					}

					if (TriPos->getDataSize() > 6000)
					{
						partition2 *= 2;
					}

					for (int l = 0; l < TriPos->getDataSize() - partition2; l += partition2)
					{

						float v1x = TriPos->getData(l);
						float v1y = TriPos->getData(l + 1);
						float v1z = TriPos->getData(l + 2);

						float v2x = TriPos->getData(l + 3);
						float v2y = TriPos->getData(l + 4);
						float v2z = TriPos->getData(l + 5);

						float v3x = TriPos->getData(l + 6);
						float v3y = TriPos->getData(l + 7);
						float v3z = TriPos->getData(l + 8);


						glm::vec4 vV1 = glm::vec4(v1x, v1y, v1z, 1.0f);
						glm::vec4 vV2 = glm::vec4(v2x, v2y, v2z, 1.0f);
						glm::vec4 vV3 = glm::vec4(v3x, v3y, v3z, 1.0f);

						glm::mat4 model = _objects[i]->getModel();
						vV1 = model * vV1;
						vV2 = model * vV2;
						vV3 = model * vV3;

						glm::vec3 v3V1, v3V2, v3V3;
						v3V1 = vV1;
						v3V2 = vV2;
						v3V3 = vV3;


						float tri[3][3] =
						{
							{ vV1.x, vV1.y, vV1.z },
							{ vV2.x, vV2.y, vV2.z },
							{ vV3.x, vV3.y, vV3.z }
						};

						glm::vec3 boxSpace = m_position;						
						glm::vec3 boxHalfLen = (m_scale / 2.0f) * m_size;
						float boxMid[3] = { boxSpace.x, boxSpace.y, boxSpace.z };
						float boxDis[3] = { boxHalfLen.x, boxHalfLen.y, boxHalfLen.z };
						

						bool collideMesh = utility::triBoxOverlap(boxMid, boxDis, tri);

						if (collideMesh)

						{
							float Vector[3], Vector2[3];

							//3 points of a tri
							float v1[] = { tri[0][0],tri[0][1], tri[0][2] };
							float v2[] = { tri[1][0],tri[1][1], tri[1][2] };
							float v3[] = { tri[2][0],tri[2][1], tri[2][2] };

							Vector[0] = v3[0] - v1[0];
							Vector[1] = v3[1] - v1[1];
							Vector[2] = v3[2] - v1[2];

							Vector2[0] = v2[0] - v1[0];
							Vector2[1] = v2[1] - v1[1];
							Vector2[2] = v2[2] - v1[2];

							float *Normal = utility::CrossProduct(Vector, Vector2);

							glm::vec3 triNorm = glm::normalize(glm::vec3(Normal[0], Normal[1], Normal[2]));
							glm::vec3 edgePoint = m_position + ((m_scale / 2.0f) * m_size) * triNorm;
							float dEdge = glm::distance(edgePoint * triNorm, m_position * triNorm);
							glm::vec3 nextPos = m_position - m_velocity * _deltaTs;
							glm::vec3 nextEdgeP = nextPos + ((m_scale / 2.0f)* m_size) * triNorm;

							glm::vec3 otherEdge = _objects[i]->getPosition() + ((_objects[i]->getScale() / 2.0f)* _objects[i]->getSize()) * (triNorm * -1.0f);
							glm::vec3 checkNeg = edgePoint - nextEdgeP;
							glm::vec3 dirCheck = glm::normalize(m_velocity);
							bool underYou;

							if (v3V1.y < m_position.y && v3V2.y < m_position.y && v3V3.y < m_position.y)
							{
								underYou = true;
							}
							else { underYou = false; }
							
							if (underYou)
							{
								dirCheck.y = -1.0f;
							}


							if (triNorm.x < dirCheck.x - 0.9f || triNorm.x > dirCheck.x + 0.9f) // If the triangle faces us
							{
								collideMesh = false;
							}
							
							if (triNorm.y < dirCheck.y - 0.9f || triNorm.y> dirCheck.y + 0.9f) // If the triangle faces us
							{
								collideMesh = false;
							}
												
							

							if (triNorm.z < dirCheck.z - 0.9f || triNorm.z > dirCheck.z + 0.9f) // If the triangle faces us
							{
								collideMesh = false;
							}

							

							if (collideMesh)
							{
								float dOtherEdge = glm::distance(otherEdge * triNorm, _objects[i]->getPosition() * triNorm);
								float dToOther = glm::distance(m_position * triNorm, otherEdge * triNorm);
								float dToOther2 = glm::distance(nextPos * triNorm, otherEdge * triNorm);

								glm::vec3 cP;

								if (dToOther <= dEdge) //If already colliding with the plane
								{

									glm::vec3 dif = m_position - m_permCP;
									dif *= triNorm;
									

									if (checkNeg.x <= 0.0f && checkNeg.y <= 0.0f && checkNeg.z <= 0.0f)
									{
										cP = m_position + dif;
									}
									else
									{
										cP = m_position - dif;
									}
									std::cout << cP.x << " " << cP.y << " " << cP.z << std::endl;

								}

								if (dToOther < dEdge && dToOther2 > dEdge)
								{
									float t = (dToOther - dEdge) / (dToOther - dToOther2);
									cP = (1.0f - t) * m_position + t * nextPos;
									m_permCP = cP;
								}


								float invBounce = 0.0f - (1 + m_bounciness);
								glm::vec3 velDif = m_velocity - glm::vec3(0.0f, 0.0f, 0.0f);
								float massCalc = (1.0f / m_mass) + (1.0f / _objects[i]->getMass());
								float resultForce = glm::dot(invBounce * velDif, triNorm) / massCalc;
								m_velocity += (resultForce * triNorm) / m_mass;

								setPosition(cP);
							}
						}

						if (collideMesh)
						{
							break;
						}

					}
				}
			}
		}







				/*								// Don't bother checking objects that are really far away
				{
					std::string shape = _objects[i]->getType(); // Shape = the object shape we're colliding with 
					glm::vec3 nextPos = m_position + m_velocity * _deltaTs; // Where we'd land next frame

					
					if (m_type == "sphere") // If current object is a sphere
					{
						//Y + P
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

						//Y + P
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

						else if (shape == "box")
						{
							glm::vec3 cPP; //Contact point plane
							glm::vec3 pPos = _objects[i]->getPosition();
							int num;
							bool collisionFace = false;
							for (int p = 0; p < 6; p++)
							{
								collisionFace = utility::sphereToPlane(m_position, nextPos, m_bRadius, cPP, m_permCP, _objects[i]->m_face[p]);
								if (collisionFace)
								{
									num = p;
									break; 
								}
							}

							if (collisionFace)
							{
								glm::vec3 pNorm = _objects[i]->m_face[num]->getNorm();
								float invBounce = 0.0f - (1 + m_bounciness);
								glm::vec3 velDif = m_velocity - glm::vec3(0.0f, 0.0f, 0.0f);
								float massCalc = (1.0f / m_mass) + (1.0f / _objects[i]->getMass());
								float resultForce = glm::dot(invBounce * velDif, pNorm) / massCalc;
								m_velocity += (resultForce * pNorm) / m_mass;
								setPosition(cPP);
							}
						}

						else {}
					}
					 
					if (m_type == "box")
					{
						// Do box-box collisions, box-plane collisions and box-sphere collisions


						/*if (shape == "sphere")
						{
							glm::vec3 sN; // normal between the two objects
							glm::vec3 sPos = _objects[i]->getPosition();
							float sRadius = _objects[i]->getRadius();
							glm::vec3 cPS; //Contact point sphere
							bool collisionSphere = utility::boxToSphere(_objects[i], m_position, m_scale);

							if (collisionSphere)
							{
								float invBounce = 0.0f - (1 + m_bounciness);
								glm::vec3 velDif = m_velocity - glm::vec3(0.0f, 0.0f, 0.0f);
								float massCalc = (1.0f / m_mass) + (1.0f / _objects[i]->getMass());
								float resultForce = glm::dot(invBounce * velDif, sN) / massCalc;
								m_velocity += (resultForce * sN) / m_mass;
								//setPosition(cPS);
							}

							//if (collisionSphere)
							{

							}
						} 

						// 

						if (shape == "plane")
						{
							glm::vec3 cPP; //Contact point plane
							glm::vec3 pNorm = _objects[i]->getNorm();
							glm::vec3 pPos = _objects[i]->getPosition();
							bool collisionPlane = utility::boxToPlane(_objects[i], m_position, nextPos, cPP, m_permCP, m_scale);

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

						//Y
						else if (shape == "box")
						{
							//bool collisionBox = utility::boxToBox(_objects[i], m_position, m_scale, m_size);
							VertexBuffer *TriPos = _objects[i]->m_vAO->getTriPos();
							//if (collisionBox)
							{

								int partition2 = 9;
								if (TriPos->getDataSize() > 450)
								{
									partition2 *= 2;
								}

								if (TriPos->getDataSize() > 1500)
								{
									partition2 *= 2;
								}

								if (TriPos->getDataSize() > 3000)
								{
									partition2 *= 2;
								}

								if (TriPos->getDataSize() > 6000)
								{
									partition2 *= 2;
								}

								for (int l = 0; l < TriPos->getDataSize() - partition2; l += partition2)
								{

									float v1x = TriPos->getData(l);
									float v1y = TriPos->getData(l + 1);
									float v1z = TriPos->getData(l + 2);

									float v2x = TriPos->getData(l + 3);
									float v2y = TriPos->getData(l + 4);
									float v2z = TriPos->getData(l + 5);

									float v3x = TriPos->getData(l + 6);
									float v3y = TriPos->getData(l + 7);
									float v3z = TriPos->getData(l + 8);


									glm::vec4 vV1 = glm::vec4(v1x, v1y, v1z, 1.0f);
									glm::vec4 vV2 = glm::vec4(v2x, v2y, v2z, 1.0f);
									glm::vec4 vV3 = glm::vec4(v3x, v3y, v3z, 1.0f);

									glm::mat4 model = _objects[i]->getModel();
									vV1 = model * vV1;
									vV2 = model * vV2;
									vV3 = model * vV3;

									glm::vec3 v3V1, v3V2, v3V3;



									float tri[3][3] =
									{
										{ vV1.x, vV1.y, vV1.z },
										{ vV2.x, vV2.y, vV2.z },
										{ vV3.x, vV3.y, vV3.z }
									};

									glm::vec3 boxSpace = m_position;
									glm::vec3 boxHalfLen = m_scale / 2.0f;
									float boxMid[3] = { boxSpace.x, boxSpace.y, boxSpace.z };
									float boxDis[3] = { boxHalfLen.x, boxHalfLen.y, boxHalfLen.z };


									bool collideMesh = utility::triBoxOverlap(boxMid, boxDis, tri);

							if (colliideMesh)
							{
								float Vector[3], Vector2[3];

								//3 points of a tri
								float v1[] = { tri[0][0],tri[0][1], tri[0][2] };
								float v2[] = { tri[1][0],tri[1][1], tri[1][2] };
								float v3[] = { tri[2][0],tri[2][1], tri[2][2] };

								Vector[0] = v3[0] - v1[0];
								Vector[1] = v3[1] - v1[1];
								Vector[2] = v3[2] - v1[2];

								Vector2[0] = v2[0] - v1[0];
								Vector2[1] = v2[1] - v1[1];
								Vector2[2] = v2[2] - v1[2];

								float *Normal = utility::CrossProduct(Vector, Vector2);

								glm::vec3 triNorm = glm::normalize(glm::vec3(Normal[0], Normal[1], Normal[2]));

								float invBounce = 0.0f - (1 + m_bounciness);
								glm::vec3 velDif = m_velocity - glm::vec3(0.0f, 0.0f, 0.0f);
								float massCalc = (1.0f / m_mass) + (1.0f / _objects[i]->getMass());
								float resultForce = glm::dot(invBounce * velDif, triNorm) / massCalc;
								m_velocity += (resultForce * triNorm) / m_mass;

								glm::vec3 dif = m_position - m_permCP;
								dif *= triNorm;
								glm::vec3 cp = m_position - dif;
								m_permCP = m_position;
								setPosition(cp);

								break;

							}

						}

						
						else if (shape == "mesh")
						{ 
							
							bool collisionBox = utility::boxToBox(_objects[i], m_position, m_scale, m_size);
							VertexBuffer *TriPos = _objects[i]->m_vAO->getTriPos();
							//if (collisionBox)
							{

								int partition2 = 9;
								if (TriPos->getDataSize() > 450)
								{
									partition2 *= 2;
								}

								if (TriPos->getDataSize() > 1500)
								{
									partition2 *= 2;
								}

								if (TriPos->getDataSize() > 3000)
								{
									partition2 *= 2;
								}

								if (TriPos->getDataSize() > 6000)
								{
									partition2 *= 2;
								}

								for (int l = 0; l < TriPos->getDataSize() - partition2; l += partition2)
								{

									float v1x = TriPos->getData(l);
									float v1y = TriPos->getData(l + 1);
									float v1z = TriPos->getData(l + 2);

									float v2x = TriPos->getData(l + 3);
									float v2y = TriPos->getData(l + 4);
									float v2z = TriPos->getData(l + 5);

									float v3x = TriPos->getData(l + 6);
									float v3y = TriPos->getData(l + 7);
									float v3z = TriPos->getData(l + 8);


									glm::vec4 vV1 = glm::vec4(v1x, v1y, v1z, 1.0f);
									glm::vec4 vV2 = glm::vec4(v2x, v2y, v2z, 1.0f);
									glm::vec4 vV3 = glm::vec4(v3x, v3y, v3z, 1.0f);

									glm::mat4 model = _objects[i]->getModel();
									vV1 = model * vV1;
									vV2 = model * vV2;
									vV3 = model * vV3;

									glm::vec3 v3V1, v3V2, v3V3;
									
									
									
									float tri[3][3] =
									{
										{ vV1.x, vV1.y, vV1.z },
										{ vV2.x, vV2.y, vV2.z },
										{ vV3.x, vV3.y, vV3.z }
									};

									glm::vec3 boxSpace = m_position;
									glm::vec3 boxHalfLen = m_scale / 2.0f;
									float boxMid[3] = { boxSpace.x, boxSpace.y, boxSpace.z };
									float boxDis[3] = { boxHalfLen.x, boxHalfLen.y, boxHalfLen.z };


									bool collideMesh = utility::triBoxOverlap(boxMid, boxDis, tri);

									if (collideMesh)

									{
										float Vector[3], Vector2[3];

										//3 points of a tri
										float v1[] = { tri[0][0],tri[0][1], tri[0][2] };
										float v2[] = { tri[1][0],tri[1][1], tri[1][2] };
										float v3[] = { tri[2][0],tri[2][1], tri[2][2] };

										Vector[0] = v3[0] - v1[0];
										Vector[1] = v3[1] - v1[1];
										Vector[2] = v3[2] - v1[2];

										Vector2[0] = v2[0] - v1[0];
										Vector2[1] = v2[1] - v1[1];
										Vector2[2] = v2[2] - v1[2];

										float *Normal = utility::CrossProduct(Vector, Vector2);

										glm::vec3 triNorm = glm::normalize(glm::vec3(Normal[0], Normal[1], Normal[2]));
									
										float invBounce = 0.0f - (1 + m_bounciness);
										glm::vec3 velDif = m_velocity - glm::vec3(0.0f, 0.0f, 0.0f);
										float massCalc = (1.0f / m_mass) + (1.0f / _objects[i]->getMass());
										float resultForce = glm::dot(invBounce * velDif, triNorm) / massCalc;
										m_velocity += (resultForce * triNorm) / m_mass;

										glm::vec3 dif = m_position - m_permCP;
										dif *= triNorm;
										glm::vec3 cp = m_position - dif;
										m_permCP = m_position;
										setPosition (cp);

										break;

									}
								}
							}
							//else
							{
								// Return 0 or something
							}
						}


					}

					else if (m_type == "mesh")
					{
						VertexBuffer *myTriPos = m_vAO->getTriPos(); // Get all the triangle data in current object's mesh


						// Y
						if (shape == "mesh")
						{
							bool collideMesh;
							if (m_position == col.m_cPoint && _objects[i]->getPosition() == col.m_oPoint)
							{
								collideMesh = true;
							}
							else { collideMesh = false; }

							if (_i == 10) // Only check every 10 frames
							{
								bool collisionBox = utility::boxToBox(_objects[i], m_position, m_scale, m_size);

								if (collisionBox) // Check the hitbox before checking the mesh
								{
									VertexBuffer *otherTriPos = _objects[i]->m_vAO->getTriPos();
									float e1 = myTriPos->getData(col.v1[0]);
									float e2 = myTriPos->getData(col.v1[1]);
									float e3 = myTriPos->getData(col.v1[2]);
									float e4 = myTriPos->getData(col.v1[3]);
									float e5 = myTriPos->getData(col.v1[4]);
									float e6 = myTriPos->getData(col.v1[5]);
									float e7 = myTriPos->getData(col.v1[6]);
									float e8 = myTriPos->getData(col.v1[7]);
									float e9 = myTriPos->getData(col.v1[8]);

									glm::vec4 vE1 = glm::vec4(e1, e2, e3, 1.0f);
									glm::vec4 vE2 = glm::vec4(e4, e5, e6, 1.0f);
									glm::vec4 vE3 = glm::vec4(e7, e8, e9, 1.0f);

									vE1 = m_model * vE1;
									float eE1[3] = { vE1.x, vE1.y, vE1.z };

									vE2 = m_model * vE2;
									float eE2[3] = { vE2.x, vE2.y, vE2.z };

									vE3 = m_model * vE3;
									float eE3[3] = { vE3.x, vE3.y, vE3.z };


									float eo1 = otherTriPos->getData(col.u1[0]);
									float eo2 = otherTriPos->getData(col.u1[1]);
									float eo3 = otherTriPos->getData(col.u1[2]);
									float eo4 = otherTriPos->getData(col.u1[3]);
									float eo5 = otherTriPos->getData(col.u1[4]);
									float eo6 = otherTriPos->getData(col.u1[5]);
									float eo7 = otherTriPos->getData(col.u1[6]);
									float eo8 = otherTriPos->getData(col.u1[7]);
									float eo9 = otherTriPos->getData(col.u1[8]);

									glm::vec4 vEo1 = glm::vec4(eo1, eo2, eo3, 1.0f);
									glm::vec4 vEo2 = glm::vec4(eo4, eo5, eo6, 1.0f);
									glm::vec4 vEo3 = glm::vec4(eo7, eo8, eo9, 1.0f);

									vEo1 = _objects[i]->getModel() * vEo1;
									float eEo1[3] = { vEo1.x, vEo1.y, vEo1.z };

									vEo2 = _objects[i]->getModel() * vEo2;
									float eEo2[3] = { vEo2.x, vEo2.y, vEo2.z };

									vEo3 = _objects[i]->getModel() * vEo3;
									float eEo3[3] = { vEo3.x, vEo3.y, vEo3.z };


									bool collideEarly = utility::NoDivTriTriIsect(eE1, eE2, eE3, eEo1, eEo2, eEo3);
									if (collideEarly == false) 
									{

										int partition1 = 9;
										if (otherTriPos->getDataSize() > 450)
										{
											partition1 *= 2;
										}

										if (otherTriPos->getDataSize() > 1500)
										{
											partition1 *= 2;
										}

										if (otherTriPos->getDataSize() > 3000)
										{
											partition1 *= 2;
										}

										if (otherTriPos->getDataSize() > 6000)
										{
											partition1 *= 2;
										}


										for (int o = 0; o < otherTriPos->getDataSize() - partition1; o += partition1)
										{
											if (collideMesh)
											{
												break;
											}
											
											float u1x = otherTriPos->getData(o);
											float u1y = otherTriPos->getData(o + 1);
											float u1z = otherTriPos->getData(o + 2);

											float u2x = otherTriPos->getData(o + 3);
											float u2y = otherTriPos->getData(o + 4);
											float u2z = otherTriPos->getData(o + 5);

											float u3x = otherTriPos->getData(o + 6);
											float u3y = otherTriPos->getData(o + 7);
											float u3z = otherTriPos->getData(o + 8);


											glm::vec4 vU1 = glm::vec4(u1x, u1y, u1z, 1.0f);
											glm::vec4 vU2 = glm::vec4(u2x, u2y, u2z, 1.0f);
											glm::vec4 vU3 = glm::vec4(u3x, u3y, u3z, 1.0f);

											vU1 = _objects[i]->getModel() * vU1;
											float u1[3] = { vU1.x, vU1.y, vU1.z };

											vU2 = _objects[i]->getModel() * vU2;
											float u2[3] = { vU2.x, vU2.y, vU2.z };

											vU3 = _objects[i]->getModel() * vU3;
											float u3[3] = { vU3.x, vU3.y, vU3.z };


											int partition2 = 9;
											if (myTriPos->getDataSize() > 450)
											{
												partition2 *= 2;
											}

											if (myTriPos->getDataSize() > 1500)
											{
												partition2 *= 2;
											}

											if (myTriPos->getDataSize() > 3000)
											{
												partition2 *= 2;
											}

											if (myTriPos->getDataSize() > 6000)
											{
												partition2 *= 2;
											}
											for (int l = 0; l < myTriPos->getDataSize() - partition2; l += partition2)
											{

												float v1x = myTriPos->getData(l);
												float v1y = myTriPos->getData(l + 1);
												float v1z = myTriPos->getData(l + 2);

												float v2x = myTriPos->getData(l + 3);
												float v2y = myTriPos->getData(l + 4);
												float v2z = myTriPos->getData(l + 5);

												float v3x = myTriPos->getData(l + 6);
												float v3y = myTriPos->getData(l + 7);
												float v3z = myTriPos->getData(l + 8); 


												glm::vec4 vV1 = glm::vec4(v1x, v1y, v1z, 1.0f);
												glm::vec4 vV2 = glm::vec4(v2x, v2y, v2z, 1.0f);
												glm::vec4 vV3 = glm::vec4(v3x, v3y, v3z, 1.0f);

												vV1 = m_model * vV1;
												float v1[3] = { vV1.x, vV1.y, vV1.z };

												vV2 = m_model * vV2;
												float v2[3] = { vV2.x, vV2.y, vV2.z };

												vV3 = m_model * vV3;
												float v3[3] = { vV3.x, vV3.y, vV3.z };


												bool collideTri = utility::NoDivTriTriIsect(v1, v2, v3, u1, u2, u3);
												if (collideTri)
												{
													for (int t = 0; t < 9; t++)
													{
														col.v1[t] = i + t;
													}

													for (int t = 0; t < 9; t++)
													{
														col.u1[t] = i + t;
													}

													col.m_cPoint = m_position;
													col.m_oPoint = _objects[i]->getPosition();
													collideMesh = true;
													break;
												}

											}
										}
									}
									//else { collideMesh = true; }


									if (collideMesh) // Do collision responses here
									{
										setPosition(glm::vec3(0.0f, 5.0f, 0.0f));
									}
								}
							}
						}

						// Y
						else if (shape == "box")
						{
							bool collisionBox = utility::boxToBox(_objects[i], m_position, m_scale, m_size);
							if (collisionBox)
							{
								int partition2 = 9;
								if (myTriPos->getDataSize() > 450)
								{
									partition2 *= 2;
								}

								if (myTriPos->getDataSize() > 1500)
								{
									partition2 *= 2;
								}

								if (myTriPos->getDataSize() > 3000)
								{
									partition2 *= 2;
								}

								if (myTriPos->getDataSize() > 6000)
								{
									partition2 *= 2;
								}

								for (int l = 0; l < myTriPos->getDataSize() - partition2; l += partition2)
								{

									float v1x = myTriPos->getData(l);
									float v1y = myTriPos->getData(l + 1);
									float v1z = myTriPos->getData(l + 2);

									float v2x = myTriPos->getData(l + 3);
									float v2y = myTriPos->getData(l + 4);
									float v2z = myTriPos->getData(l + 5);

									float v3x = myTriPos->getData(l + 6);
									float v3y = myTriPos->getData(l + 7);
									float v3z = myTriPos->getData(l + 8);


									glm::vec4 vV1 = glm::vec4(v1x, v1y, v1z, 1.0f);
									glm::vec4 vV2 = glm::vec4(v2x, v2y, v2z, 1.0f);
									glm::vec4 vV3 = glm::vec4(v3x, v3y, v3z, 1.0f);

									vV1 = m_model * vV1;
									vV2 = m_model * vV2;
									vV3 = m_model * vV3;

									float tri[3][3] =
									{
										{ vV1.x, vV1.y, vV1.z },
										{ vV2.x, vV2.y, vV2.z },
										{ vV3.x, vV3.y, vV3.z }
									};

									glm::vec3 boxSpace = _objects[i]->getPosition();
									glm::vec3 boxHalfLen = _objects[i]->getScale() / 2.0f;
									float boxMid[3] = { boxSpace.x, boxSpace.y, boxSpace.z };
									float boxDis[3] = { boxHalfLen.x, boxHalfLen.y, boxHalfLen.z };


									bool collideBox = utility::triBoxOverlap(boxMid, boxDis, tri);

									if (collideBox)

									{
										// Do things
										setPosition(glm::vec3(0.0f, 5.0f, 0.0f));
										break;

									}
								}
							}
							else 
							{
							// Return 0 or something
							}
						}


						else if (shape == "sphere")
						{

						}


						else if (shape == "plane")
						{

						}

					}


					// TO - DO
					// Sphere:Mesh
					//Plane:Mesh
					//Box:Plane

				}
	}

}

	

	*/
	


	

	


