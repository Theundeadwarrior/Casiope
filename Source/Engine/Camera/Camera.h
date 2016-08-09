#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_access.hpp>

namespace Engine
{
	class Camera
	{
	public:
		Camera(const glm::vec3& position, const glm::vec3& POI, const glm::vec3& up);
		virtual ~Camera(){};

		//Getters
		void GetViewMatrix(glm::mat4x4& matrix);
		void UpdateViewMatrix();
		glm::mat4x4 GetViewMatrix();
		glm::vec3 GetPosition() { return m_position; }
		glm::vec3 GetPOI() { return -glm::vec3(glm::row(m_viewMatrix, 2)); }
		glm::vec3 GetRight() { return glm::vec3(glm::row(m_viewMatrix, 0)); }

		glm::vec3 m_position;
		glm::quat m_Orientation;

		void SetPosition(const glm::vec3& position) { m_position = position; }
		void SetRelativeOrientation(float key_pitch, float key_yaw, float key_roll);


	protected:
		glm::mat4x4 m_viewMatrix;


	};
}
