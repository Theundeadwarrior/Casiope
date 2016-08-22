#ifndef SCENEMANAGER_CAMERA_CPP
#define SCENEMANAGER_CAMERA_CPP

#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>


namespace Engine
{
	// TODO!!! FIX THE INIT OF POI AND UP!!!
	Camera::Camera(const glm::vec3& position, const glm::vec3& /*POI*/, const glm::vec3& /*up*/)
	: m_position(position)
	, m_Orientation(1.0f,0.0f,0.0f,0.0f)
	{
	}

	void Camera::GetViewMatrix(glm::mat4x4& matrix)
	{
		matrix = GetViewMatrix();
	}

	void Camera::SetRelativeOrientation(float key_pitch, float key_yaw, float key_roll)
	{
		glm::quat key_quat = glm::quat(glm::vec3(key_pitch, key_yaw, key_roll));

		m_Orientation = key_quat * m_Orientation;
		m_Orientation = glm::normalize(m_Orientation);
	}


	void Camera::UpdateViewMatrix()
	{
		glm::mat4 rotate = glm::mat4_cast(m_Orientation);

		glm::mat4 translate = glm::mat4(1.0f);
		translate = glm::translate(translate, -m_position);

		m_viewMatrix = rotate * translate;
	}

	glm::mat4x4 Camera::GetViewMatrix()
	{

		return m_viewMatrix;
	}
}

#endif
