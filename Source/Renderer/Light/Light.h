#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace Renderer
{
	enum LightType : uint32_t
	{
		LightType_PointLight = 0,
		LightType_SpotLight = 1,
		LightType_DirectionalLight = 2
	};

	struct LightParam
	{
		glm::vec4  PositionWS;
		glm::vec4  DirectionWS;
		glm::vec4  PositionVS;
		glm::vec4  DirectionVS;
		glm::vec4  Color;
		float SpotlightAngle;
		float Range;
		float Intensity;
		uint32_t Enabled;
		uint32_t Selected;
		LightType Type;
		float Padding[2];
	};

	class Light
	{
	public:
		void EnableLight();
		void DisableLight();

		bool IsLightEnabled();

		void UpdateViewSpaceCoord(const glm::mat4& view);

		glm::vec4 GetWorldSpacePosition() {
			return m_Params.PositionWS;
		}

		~Light() = default;

	protected:
		LightParam m_Params;
		Light() = default;
	};

	class PointLight : public Light
	{
	public:
		PointLight(const glm::vec3& position, const glm::vec4& color, float range, float intensity);
	};

	class SpotLight : public Light
	{
	public:
		SpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec4& color, float range, float intensity, float angle);
	};

	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(const glm::vec3& direction, const glm::vec4& color, float intensity);
	};
}



