#pragma once
#include "EngineCore/Renderer/RenderCommon.hpp"

namespace engine::renderer
{
	enum class Primitive : uint32_t
	{
		Points = 0x0000,
		Lines = 0x0001,
		Triangles = 0x0004
	};

	class RenderDevice
	{
	public:
		void Init();

		void BeginPass(const RenderPassDesc& desc);

		void Clear(const glm::vec4& color, bool depth);
		void SetDepthTest(bool enabled);
		void SetBlend(bool enabled);
		void SetCullFace(bool enabled);
		void setViewPort(const Viewport& viewport);

		void BindVertexArray(uint32_t vao);

		void DrawIndexed(uint32_t indexCount);
		void DrawArrays(Primitive primitive, uint32_t first, uint32_t count);
	};
}
