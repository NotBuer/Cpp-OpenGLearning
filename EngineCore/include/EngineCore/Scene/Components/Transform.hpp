#pragma once
#include <gtc/quaternion.hpp>
#include <mat4x4.hpp>
#include <vec3.hpp>

namespace engine::scene::components
{
	struct Transform
	{
		glm::vec3 position;
		glm::mat4 rotation;
		glm::vec3 scale;
	};
}