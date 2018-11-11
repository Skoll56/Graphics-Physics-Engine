#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 _startPos, glm::vec3 _startRot)
{
	m_pos = _startPos;
	m_rot = _startRot;
	m_angle = 0.0f;
	m_speed = 15.0f;
	m_left = false;
	m_right = false;
	m_up = false;
	m_down = false;
	m_asc = false;
	m_desc = false;
	m_r1 = false;
	m_r2 = false;
	m_rotSpeed = 4.0f;
}

Camera::~Camera()
{

}

void Camera::update(float _dTime)
{
	glm::mat4 temp(1.0f);
	
	glm::vec3 direction = glm::vec3(0, 0, 0);

	if (m_left) 
	{ 
		direction.x -= 1;		
	}
	if (m_right)
	{ 
		direction.x += 1;
	}
	if (m_up)
	{	
		direction.z -= 1;
	}
	if (m_down)
	{ 
		direction.z += 1;
	}

	if (m_asc)
	{
		direction.y += 1;
	}

	if (m_desc)
	{
		direction.y -= 1;
	}

	if (m_r1)
	{
		m_angle -= m_rotSpeed;
	}

	if (m_r2)
	{
		m_angle+= m_rotSpeed;
	}

		temp = glm::rotate(temp, glm::radians(m_angle), glm::vec3(0, 1, 0));
		temp = glm::translate(temp, direction);
		glm::vec3 fwd = temp * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		if (fwd != glm::vec3(0, 0, 0))
		{
			fwd = glm::normalize(fwd);
		}
		m_pos += fwd * m_speed * _dTime;
		//m_rot += fwd * _dTime;
		//m_viewMat = glm::lookAt(m_pos, m_pos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		//std::cout << m_pos.y << std::endl;
}
