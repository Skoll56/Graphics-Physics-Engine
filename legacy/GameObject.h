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


	
	
	std::string getTag() { return m_tag; }
	void setTag(std::string _tag) { m_tag = _tag; }

	void setPosition( float _posX, float _posY, float _posZ ) {m_position.x = _posX; m_position.y = _posY; m_position.z = _posZ;}	
	void setPosition( glm::vec3 _value) {m_position = _value;}

	glm::vec3 getPosition() {return m_position;}		
	
	bool isActive() { return m_active; };
	void setActive(bool _status) { m_active = _status; }

	
	//Components

	void addPlaneShape(std::string _texName, glm::vec3 _scale, glm::vec3 _normal);
	void addBoxShape(std::string _texName, glm::vec3 _scale);    
	void addSphereShape(std::string _texName, float _radius);

	void addPhysics(std::string _tag, float _mass, float _bounciness); // Adds a rigidbody
	void removePhysics();
	bool isPhysics() { return m_physics; } // A boolean that holds if it is a physics object or not
	std::string getType() { return m_type; } // Type = shape (ie: box, sphere, etc)

	PhysicsObj *m_rb;
	Shape *m_shape;

protected:	
	
	
	std::string m_type;	
	glm::vec3 m_position;
	bool m_physics;
	
	
	std::string m_tag;
	
	
	bool m_active;
};

#endif
