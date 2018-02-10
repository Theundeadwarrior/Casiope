#include "Renderer/Light/Light.h"

namespace Renderer
{
	void Light::EnableLight()
	{
		m_Params.Enabled = true;
	}

	void Light::DisableLight()
	{
		m_Params.Enabled = false;
	}

	bool Light::IsLightEnabled()
	{
		return m_Params.Enabled;
	}

	void Light::UpdateViewSpaceCoord(const glm::mat4 & view)
	{
		if (m_Params.Type == LightType::LightType_SpotLight || m_Params.Type == LightType::LightType_PointLight)
		{
			m_Params.PositionVS = view * m_Params.PositionWS;
		}
		if (m_Params.Type == LightType::LightType_DirectionalLight || m_Params.Type == LightType::LightType_SpotLight)
		{
			m_Params.DirectionVS = view * m_Params.DirectionWS;
		}
	}

	PointLight::PointLight(const glm::vec3 & position, const glm::vec4 & color, float range, float intensity)
	{
		m_Params.PositionWS = glm::vec4(position, 1.0f);
		m_Params.Color = color;
		m_Params.Range = range;
		m_Params.Intensity = intensity;
		m_Params.Enabled = true;
		m_Params.Type = LightType::LightType_PointLight;
	}

	SpotLight::SpotLight(const glm::vec3 & position, const glm::vec3 & direction, const glm::vec4 & color, float range, float intensity, float angle)
	{
		m_Params.PositionWS = glm::vec4(position, 1.0f);
		m_Params.DirectionWS = glm::vec4(direction, 1.0f);
		m_Params.Color = color;
		m_Params.Range = range;
		m_Params.Intensity = intensity;
		m_Params.SpotlightAngle = angle;
		m_Params.Enabled = true;
		m_Params.Type = LightType::LightType_SpotLight;
	}

	DirectionalLight::DirectionalLight(const glm::vec3 & direction, const glm::vec4 & color, float intensity)
	{
		m_Params.DirectionWS = glm::vec4(direction, 1.0f);
		m_Params.Color = color;
		m_Params.Intensity = intensity;
		m_Params.Enabled = true;
		m_Params.Type = LightType::LightType_DirectionalLight;
	}
}
