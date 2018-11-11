#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>




class Camera
{
private:
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	float m_angle;
	float m_speed;
	glm::mat4 m_model;
	float m_rotSpeed;
	
	

public:
	Camera(glm::vec3 _startPos, glm::vec3 _startRot);
	~Camera();
	glm::mat4 m_viewMat;
	bool m_left, m_right, m_up, m_down, m_asc, m_desc, m_r1, m_r2;
	
	float speed() { return m_speed; }
	glm::vec3 getPos() { return m_pos; }
	float getRot() { return m_angle; }
	void setPos(glm::vec3 _pos) { m_pos = _pos; }
	void setRot(glm::vec3 _rot) { m_rot = _rot; }
	void update(float _dTime);

	
	
	

};
