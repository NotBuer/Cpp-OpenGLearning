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

		Transform(
			glm::vec3 pos = glm::vec3(0.0f),
			glm::mat4 rot = glm::mat4(1.0f),
			glm::vec3 scl = glm::vec3(1.0f)
		) : position(pos), rotation(rot), scale(scl) {}
	};
}