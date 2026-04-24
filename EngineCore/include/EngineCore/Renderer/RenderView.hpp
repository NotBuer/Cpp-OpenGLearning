#pragma once
#include <cstdint>
#include <vector>
#include <vec2.hpp>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include "EngineCore/Renderer/QuadCommand.hpp"

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
		std::vector<QuadCommand> quads;
		
		void clear()
		{
			quads.clear();
		}

		void reserve(size_t draws)
		{
			quads.reserve(draws);
		}
	};
}