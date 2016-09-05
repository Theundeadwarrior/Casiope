#include "catch.hpp"

#include "Engine/Camera/Camera.h"
#include <glm/include/glm/glm.hpp>

#define TEST_EPSILON 0.00001f
#define EQUAL_WITH_EPSILON(x,y) ((x - y) < TEST_EPSILON && (x - y) > -TEST_EPSILON)

SCENARIO("Camera properties are updated properly")
{
	GIVEN("A camera freshly initialized")
	{
		glm::vec3 pos(0.0f, 0.0f, 0.0f);
		glm::vec3 poi(1.0f, 0.0f, 0.0f);
		glm::vec3 up(0.0f, 1.0f, 0.0f);
		Engine::Camera camera(pos, poi, up);
		camera.UpdateViewMatrix();

		REQUIRE(camera.GetForward() == poi);
		REQUIRE(camera.GetPosition() == pos);
		REQUIRE(EQUAL_WITH_EPSILON(camera.GetRight().x, 0.0f));
		REQUIRE(EQUAL_WITH_EPSILON(camera.GetRight().y, 0.0f));
		REQUIRE(EQUAL_WITH_EPSILON(camera.GetRight().z, 1.0f));
	}
}