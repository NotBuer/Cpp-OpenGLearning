#pragma once
#include <cstdint>
#include <vector>
#include <vec3.hpp>
#include <mat4x4.hpp>

namespace engine::renderer
{
	struct CameraData
	{
		glm::mat4 view{};
		glm::mat4 proj{};
		glm::vec3 position{};
		float _pad0{};
	};

	struct RenderView
	{
		CameraData camera{};

		void clear()
		{

		}

		void reserve(std::size_t lights, std::size_t draws)
		{

		}
	};
}