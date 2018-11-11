#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

//#include "Mesh.h"
//#include "Material.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"

/*! \brief Brief description.
*  GameObject class contains a mesh, a material, a position and an orientation information
*  about the game object. This should be a base class for different types of game object. 
*
*/

class GameObject
{
public:
	
	GameObject(glm::vec3 _startPos, glm::vec3 _scale, std::string _texName, std::string _type, std::string _tag);
	GameObject() {};
	
	~GameObject();	

	void setTag(std::string _tag) { m_tag = _tag; }
	std::string getType() { return m_type; }
	std::string getTag() { return m_tag; }
	void setPosition( float _posX, float _posY, float _posZ ) {m_position.x = _posX; m_position.y = _posY; m_position.z = _posZ;}
	
	void setPosition( glm::vec3 _value) {m_position = _value;}
	
	void setRotation( float _rotX, float _rotY, float _rotZ ) {m_rotation.x = _rotX; m_rotation.y = _rotY; m_rotation.z = _rotZ;}
	
	void setScale(float _sX, float _sY, float _sZ) { m_scale.x = _sX; m_scale.y = _sY; m_scale.z = _sZ; }
	glm::vec3 getScale() { return m_scale; }
	float getRadius() { return m_scale.y; }
	
	glm::vec3 getNorm() { return m_normal; }
	
	glm::vec3 getPosition() {return m_position;}
	
	virtual void update(float _dTime, std::vector <GameObject*> _objects);

	void activate();

	bool isSolid() { return m_solid; }
	void setSolid(bool _solid) { m_solid = _solid; }
	float getMass() { return m_mass; }
	bool isActive();
	
	VertexArray *m_vAO;
	VertexBuffer *m_vBOt;
	VertexBuffer *m_vBOp;
	
	Texture *m_tex;


protected:

	

	/** Matrix for the position of the game object
	*/ 
	///glm::mat4 m_modelMatrix;
	/** Matrix for the orientation of the game object
	*/
	///glm::mat4 m_invModelMatrix;
	
	/** Position of the model
	* The model matrix must be built from the position of the model geometry
	*/
	std::string m_tag;
	std::string m_type;
	float m_mass;
	glm::vec3 m_position;
	
	/** Orientation of the model
	* The model matrix must be built from the orientation of the model geometry
	*/
	glm::vec3 m_rotation;
	/** Scale of the model
	* The model matrix must be built from the scale of the model geometry
	*/
	glm::vec3 m_scale;
	
	glm::vec3 m_normal;
	bool m_solid;
	bool m_active;

};



#endif
