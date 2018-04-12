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
		glm::vec3 GetPosition() const { return m_Position; }
		glm::vec3 GetForward() { return glm::normalize(m_Forward); }
		glm::vec3 GetRight() { return glm::normalize(glm::cross(m_Forward, m_Up)); }
		glm::vec3 GetUp() { return m_Up; }
		glm::vec3 m_Position;
		glm::vec3 m_Forward;



		void SetPosition(const glm::vec3& position) { m_Position = position; }
		void SetRelativeOrientation(float key_pitch, float key_yaw, float key_roll);


	protected:
		glm::mat4x4 m_ViewMatrix;
		glm::vec3 m_Up;

		float m_Pitch;
		float m_Yaw;
	};
}
