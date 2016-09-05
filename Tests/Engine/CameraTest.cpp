#include "catch.hpp"

#include "Engine/Camera/Camera.h"
#include <glm/include/glm/glm.hpp>

#define TEST_EPSILON 0.00001f
#define EQUAL_WITH_EPSILON(x,y) ((x - y) < TEST_EPSILON && (x - y) > -TEST_EPSILON)

SCENARIO("Camera rotation works properly")
{
	GIVEN("A camera freshly initialized, facing +X")
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

		WHEN("Camera rotates 90 degrees to the right")
		{
			camera.SetRelativeOrientation(0, 90, 0);

			THEN("Camera forward should be z")
			{
				REQUIRE(EQUAL_WITH_EPSILON(camera.GetForward().x, 0.0f));
				REQUIRE(EQUAL_WITH_EPSILON(camera.GetForward().y, 0.0f));
				REQUIRE(EQUAL_WITH_EPSILON(camera.GetForward().z, 1.0f));
			}

			WHEN("Camera rotates 45 degrees up")
			{
				camera.SetRelativeOrientation(45, 0, 0);
				THEN("Camera forward should be 0.7071 in +Z and 0.7071 in +Y (cos(45))")
				{
					REQUIRE(EQUAL_WITH_EPSILON(camera.GetForward().x, 0.0f));
					REQUIRE(EQUAL_WITH_EPSILON(camera.GetForward().y, 0.7071f));
					REQUIRE(EQUAL_WITH_EPSILON(camera.GetForward().z, 0.7071f));
				}
			}
		}

		WHEN("Camera rotations more than 89 degrees up")
		{
			camera.SetRelativeOrientation(91, 0, 0);
			THEN("Camera rotation should be clipped to 89 degrees to avoid gimbal lock")
			{
				REQUIRE(EQUAL_WITH_EPSILON(camera.GetForward().x, 0.01745f)); // cos(89)
				REQUIRE(EQUAL_WITH_EPSILON(camera.GetForward().y, 0.999848f)); // sin(89)
				REQUIRE(EQUAL_WITH_EPSILON(camera.GetForward().z, 0.0f));
			}
		}
	
		WHEN("Camera rotates more than 89 degrees down")
		{
			camera.SetRelativeOrientation(-91, 0, 0);
			THEN("Camera rotation should be clipped to -89 degrees to avoid gimbal lock")
			{
				REQUIRE(EQUAL_WITH_EPSILON(camera.GetForward().x, 0.01745f)); // cos(89)
				REQUIRE(EQUAL_WITH_EPSILON(camera.GetForward().y, -0.999848f)); // sin(89)
				REQUIRE(EQUAL_WITH_EPSILON(camera.GetForward().z, 0.0f));
			}
		}
	}
}