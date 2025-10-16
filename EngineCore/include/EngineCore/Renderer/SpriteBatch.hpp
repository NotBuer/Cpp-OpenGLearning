#pragma once
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <vector>
#include <cstdint>
#include "EngineCore/Graphics/Shader.hpp"
#include "EngineCore/Renderer/RenderDevice.hpp"
#include "EngineCore/Renderer/QuadVertex.hpp"

// Forward declaration
namespace engine::renderer { class Shader; }

namespace engine::renderer
{
	class SpriteBatch
	{
	public:
		explicit SpriteBatch(RenderDevice& device);
		~SpriteBatch();

		void Init();
		void Shutdown();

		void SetProjection(const glm::mat4& proj);

		void Begin();
		void End();

		void DrawQuad(const glm::vec2& min, const glm::vec2& size, const glm::vec4& color);

		const graphics::Shader& shader() const { return *m_Shader; }
		const glm::mat4& proj() const { return m_Proj; }

	private:
		void StartBatch();
		void Upload();
		void Flush();

	private:
		RenderDevice* m_Device{};
		std::unique_ptr<graphics::Shader> m_Shader = nullptr;
		unsigned m_VAO{}, m_VBO{}, m_EBO{};

		std::vector<QuadVertex> m_Vertices;
		std::vector<std::uint32_t> m_Indices;

		glm::mat4 m_Proj{ 1.0f };
		bool m_Begun{ false };

		static constexpr std::uint32_t MaxQuads = 1000;
		static constexpr std::uint32_t MaxVerts = MaxQuads * 4;
		static constexpr std::uint32_t MaxIndices = MaxQuads * 6;
	};
}