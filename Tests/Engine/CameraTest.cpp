#include "catch.hpp"

#include "Engine/Camera/Camera.h"
#include <glm/include/glm/glm.hpp>

#define TEST_EPSILON 0.00001f
#define EQUAL_WITH_EPSILON(x,y) ((x - y) < TEST_EPSILON || (y - x) < TEST_EPSILON)

SCENARIO("Camera properties are updated properly")
{
	GIVEN("A camera freshly initialized")
	{
		glm::vec3 pos(0.0f, 0.0f, 0.0f);
		glm::vec3 poi(1.0f, 0.0f, 0.0f);
		glm::vec3 up(0.0f, 1.0f, 0.0f);
		Engine::Camera camera(pos, poi, up);
		camera.UpdateViewMatrix();

		glm::vec3& campoi = camera.GetPOI();
		CHECK(campoi == poi);
		CHECK(camera.GetPosition() == pos);
		CHECK(EQUAL_WITH_EPSILON(camera.GetRight().x, 1.0f));
		CHECK(EQUAL_WITH_EPSILON(camera.GetRight().y, 0.0f));
		CHECK(EQUAL_WITH_EPSILON(camera.GetRight().z, 0.0f));
	}
}