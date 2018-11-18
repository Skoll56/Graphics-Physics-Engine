#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__


#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Components.h"


class GameObject
{
public:
	
	GameObject(glm::vec3 _startPos);
	GameObject() {};	
	~GameObject();	


	std::string getType() { return m_type; }
	
	glm::vec3 getVelocity() { return m_velocity; }
	void setVelocity(glm::vec3 _vel) { m_velocity = _vel; }

	std::string getTag() { return m_tag; }
	void setTag(std::string _tag) { m_tag = _tag; }

	void setPosition( float _posX, float _posY, float _posZ ) {m_position.x = _posX; m_position.y = _posY; m_position.z = _posZ;}	
	void setPosition( glm::vec3 _value) {m_position = _value;}
	glm::vec3 getPosition() {return m_position;}

	void setRotation( float _rotX, float _rotY, float _rotZ ) {m_rotation.x = _rotX; m_rotation.y = _rotY; m_rotation.z = _rotZ;}


	glm::vec3 getSize() { return m_size; }

	void setScale(float _sX, float _sY, float _sZ) { m_scale.x = _sX; m_scale.y = _sY; m_scale.z = _sZ; }
	glm::vec3 getScale() { return m_scale; }

	glm::mat4 getModel() { return m_model; }
	void setModel(glm::mat4 _model) { m_model = _model; }

	bool isSolid() { return m_solid; }
	void setSolid(bool _solid) { m_solid = _solid; }	
	
	bool isActive() { return m_active; };
	void setActive(bool _status) { m_active = _status; }

	float getMass() { return m_mass; }

	void addPhysics(std::string _tag, float _mass, float _bounciness);
	void removePhysics();
	bool isPhysics() { return m_physics; }

	PhysicsObj *m_rb;
	VertexArray *m_vAO;
	VertexBuffer *m_vBOt;
	VertexBuffer *m_vBOp;
	std::vector<GameObject*> m_face;
	Texture *m_tex;


protected:	
	
	glm::mat4 m_model;
	std::string m_type;
	float m_mass;
	glm::vec3 m_velocity;
	glm::vec3 m_position;
	float m_bounciness;
	bool m_physics;
	glm::vec3 m_size;
	glm::vec3 m_rotation;
	std::string m_tag;
	glm::vec3 m_scale;
	bool m_solid;
	bool m_active;
};

#endif
