#pragma once
#include <mat4x4.hpp>
#include <vec4.hpp>
#include "EngineCore/Renderer/RenderDevice.hpp"

// Forward declaration.
namespace engine::graphics { class Shader; }

namespace engine::renderer
{
	class Immediate3D
	{
	public:
		explicit Immediate3D(RenderDevice& dev);
		~Immediate3D();

		void Init();
		void ShutDown();

		void Begin(const glm::mat4& view, const glm::mat4& proj);
		void End();

		// TODO: Create on my own DrawCube method signature declaration.

	private:
		RenderDevice* m_Device{};
		graphics::Shader* m_ColorShader{};

		glm::mat4 m_View{ 1.0f }, m_Proj{ 1.0f };
	};
}