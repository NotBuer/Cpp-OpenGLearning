#pragma once
#include <vec2.hpp>
#include <vec3.hpp>

namespace engine::renderer
{
	struct VoxelVertex
	{
		glm::vec3 pos;
		glm::vec3 color;
		glm::vec2 uv;

		static constexpr std::uint32_t FaceVertexCount = 4;
		static constexpr std::uint32_t FaceCount = 6;

		static constexpr size_t MaxVerts = FaceCount * FaceVertexCount;
		static constexpr size_t MaxIndices = FaceCount * 6;

		// Since each face has 2 triangles.
		// 6 * 4 = 24 verts
		// 6 * 6 = 36 triangles
	};
}