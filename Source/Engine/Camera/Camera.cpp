#ifndef SCENEMANAGER_CAMERA_CPP
#define SCENEMANAGER_CAMERA_CPP

#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>


namespace Engine
{
	// TODO!!! FIX THE INIT OF POI AND UP!!!
	Camera::Camera(const glm::vec3& position, const glm::vec3& POI, const glm::vec3& up)
		: m_Position(position)
		, m_Forward(POI)
		, m_Up(up)
		, m_Pitch(0)
		, m_Yaw(0)
	{
	}

	void Camera::GetViewMatrix(glm::mat4x4& matrix)
	{
		matrix = GetViewMatrix();
	}

	void Camera::SetRelativeOrientation(float key_pitch, float key_yaw, float key_roll)
	{
		m_Yaw += key_yaw;
		m_Pitch += key_pitch;

		if (m_Pitch >= 89.0f)
			m_Pitch = 89.0f;
		else if (m_Pitch <= -89.0f)
			m_Pitch = -89.0f;

		if (m_Yaw >= 360.0f)
			m_Yaw -= 360.0f;
		else if (m_Yaw <= -360.0f)
			m_Yaw += 360.0f;

		m_Forward.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Forward.y = sin(glm::radians(m_Pitch));
		m_Forward.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Forward = glm::normalize(m_Forward);
	}


	void Camera::UpdateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
	}

	glm::mat4x4 Camera::GetViewMatrix()
	{
		return m_ViewMatrix;
	}
}

#endif
