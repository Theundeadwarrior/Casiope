#pragma once

#include "Camera.h"

namespace Engine
{
	//-----------------------------------------------------------------------------
	struct PerspectiveCameraParams
	{
		PerspectiveCameraParams(float fovy, float aspectRatio, float nearZ, float farZ)
		: fovy(fovy)
		, aspectRatio(aspectRatio)
		, nearZ(nearZ)
		, farZ(farZ)
		{}

		float fovy;
		float aspectRatio;
		float nearZ;
		float farZ;
	};

	//-----------------------------------------------------------------------------
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(const PerspectiveCameraParams& params, const glm::vec3& position, const glm::vec3& POI, const glm::vec3& up);
		~PerspectiveCamera(){};

		//Getters
		void GetPerspectiveMat(glm::mat4x4& matrix) const;
		glm::mat4x4* GetPerspectiveMat() { return &m_perspective; }
		float GetFovy() const;
		float GetAspectRatio() const;
		float GetNear() const;
		float GetFar() const;

		//Setters
		void SetFovy(float value);
		void SetAspectRatio(float value);
		void SetNear(float value);
		void SetFar(float value);

	private:
		glm::mat4x4 m_perspective;
		float m_fovy;
		float m_aspectRatio;
		float m_near;
		float m_far;		
	};

} 
