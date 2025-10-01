#pragma once
#include <vec4.hpp>
#include <cstdint>

namespace engine::renderer
{
	struct RenderCommand
	{
		static void Init();
		static void Clear(const glm::vec4& color);
		static void BindVertexArray(std::uint32_t vao);
		static void DrawIndexed(std::uint32_t count);
	};
}