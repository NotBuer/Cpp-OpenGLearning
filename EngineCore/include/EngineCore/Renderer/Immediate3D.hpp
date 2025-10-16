#pragma once
#include <mat4x4.hpp>
#include <vec4.hpp>
#include "EngineCore/Renderer/RenderDevice.hpp"
#include "EngineCore/Graphics/Shader.hpp"
#include "EngineCore/Renderer/VoxelVertex.hpp"

namespace engine::renderer
{
	class Immediate3D
	{
	public:
		explicit Immediate3D(RenderDevice& dev);
		~Immediate3D();

		void Init();
		void ShutDown();

		void SetProjection(const glm::mat4& proj);

		void Begin(const glm::mat4& view, const glm::mat4& proj);
		void End();

		void DrawCube(const glm::vec3& min, const glm::vec3& size, const glm::vec4& color);

		void Upload();

		const graphics::Shader& shader() const { return *m_Shader; }
		const glm::mat4& proj() const { return m_Proj; }

	private:
		RenderDevice* m_Device{};
		std::unique_ptr<graphics::Shader> m_Shader = nullptr;
		unsigned m_VAO{}, m_VBO{}, m_EBO{};

		std::vector<VoxelVertex> m_Vertices;
		std::vector<std::uint32_t> m_Indices;

		glm::mat4 m_View{ 1.0f }, m_Proj{ 1.0f };
	};
}