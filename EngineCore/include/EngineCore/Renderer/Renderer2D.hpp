#pragma once
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <vector>
#include <cstdint>
#include "EngineCore/Graphics/Shader.hpp"

namespace engine::renderer
{
	struct QuadVertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 uv;
	};

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void ClearFrame(const glm::vec4& color);
		static void BeginFrame();
		static void EndFrame();

		static void BeginPass(const engine::graphics::Shader& shader);
		static void EndPass();

		static void DrawQuad(const glm::vec2& min, const glm::vec2& size, const glm::vec4& color);

	private:
		static void StartBatch();
		static void Upload();
		static void Flush();

	private:
		static std::uint32_t s_VAO, s_VBO, s_EBO;
		
		static std::vector<QuadVertex> s_Vertices;
		static std::vector<std::uint32_t> s_Indices;
		static bool s_Begun;

		static inline const engine::graphics::Shader* s_CurrentShader = nullptr;

		static constexpr std::uint32_t MaxQuads = 1000;
		static constexpr std::uint32_t MaxVerts = MaxQuads * 4;
		static constexpr std::uint32_t MaxIndices = MaxQuads * 6;
	};
}