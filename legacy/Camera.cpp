#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Camera.h"
#include "Input.h"

Camera::Camera(glm::vec3 _startPos)
{
	m_pos = _startPos;
	m_upVec = glm::vec3(0.0f, 1.0f, 0.0f);
	m_yaw = 90.0f;
	m_pitch = 0.0f;
	m_speed = 15.0f;
	m_rotSpeed = 2.0f;
}

Camera::~Camera()
{

}

void Camera::update(float _dTime, Input *_input)
{
	if (_input->m_r1)
	{
		m_yaw += m_rotSpeed;
	}

	if (_input->m_r2)
	{
		m_yaw -= m_rotSpeed;
	}

	if (_input->m_r)
	{
		m_pitch += m_rotSpeed;
	}

	if (_input->m_f)
	{
		m_pitch -= m_rotSpeed;
	}

	if (m_pitch > 89.0f) { m_pitch = 89.0f; }
	else if (m_pitch < -89.0f) { m_pitch = -89.0f; }
	if (m_yaw > 360.0f) { m_yaw = 0.0f; }
	else if (m_yaw < -360.0f) { m_yaw = 0.0f; }

	//Reference LearnOpenGL
	m_fwd.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_fwd.y = sin(glm::radians(m_pitch));
	m_fwd.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_fwd = glm::normalize(m_fwd);
	m_right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), m_fwd));
}
