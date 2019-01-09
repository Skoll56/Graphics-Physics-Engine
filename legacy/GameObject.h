#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include <vector>
#include <string>
#include "Components.h"
#include "Shader.h"



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

	void setShader(Shader * _shader) { m_shader = _shader; }
	Shader* getShader() { return m_shader; }

	
	//Component functions
	void addPlaneShape(std::string _texName, glm::vec3 _scale, glm::vec3 _normal);
	void addBoxShape(std::string _texName, glm::vec3 _scale);    
	void addSphereShape(std::string _texName, float _radius);
	void addMeshShape(std::string _texName, std::string _obj, glm::vec3 _scale, glm::vec3 _size, std::string _tag);
	void deleteShape();

	void addPhysics(std::string _tag, float _mass, float _bounciness); // Adds a rigidbody
	void addAdvancedPhysics(std::string _shape, glm::vec3 _scale, float _mass); //Adds rotational-physics
	void removePhysics();
	bool isPhysics() { return m_physics; } // A boolean that holds if it is a physics object or not
	bool isAdvancedPhysics() { return m_advancedPhys; }
	std::string getShape() { return m_shape; } // shape (ie: box, sphere, etc)
	void setShapeString(std::string _val) { m_shape = _val; }
	void setPhysBool(bool _val) { m_physics = _val; }
	void setAdPhysBool(bool _val) { m_advancedPhys = _val; }

	//Component variables
	PhysicsObj *m_rb;
	Plane *m_plane;
	Sphere *m_sphere;
	Box *m_box;
	Mesh *m_mesh;
	Shape *m_shapeComp;
	AdvancedPhysics *m_Phy;

protected:		
	Shader *m_shader;
	glm::vec3 m_position;	
	std::string m_tag;	
	bool m_active;

	//Component Variables
	std::string m_shape;	
	bool m_physics;	
	bool m_advancedPhys;
};

#endif
