#pragma once
#include "EngineCore/Renderer/Camera.hpp"

namespace engine::renderer
{
	class OrthographicCamera final : public Camera
	{
	public:
		OrthographicCamera(float worldHeight, float aspectRatio, float near = -1.f, float far = 1.f);
		~OrthographicCamera() override;

		void SetViewPort(float aspectRatio);
		void SetPosition(const glm::vec3& p);
		void SetRotation(float radians);

		[[nodiscard]] const glm::mat4& view() const noexcept override;
		[[nodiscard]] const glm::mat4& proj() const noexcept override;
		[[nodiscard]] const glm::mat4& viewProj() const noexcept override;
		[[nodiscard]] const glm::vec3& position() const noexcept override;

	private:
		void RecalcProj();
		void RecalcView();
		void RecalcViewProj();

		float m_width;
		float m_worldHeight;
		float m_aspectRatio;
		float m_near;
		float m_far;

		glm::vec3 m_pos;
		float m_rotation;

		glm::mat4 m_view;
		glm::mat4 m_proj;
		glm::mat4 m_viewProj;
	};
}