#pragma once
#include "EngineCore/Renderer/Camera.hpp"

namespace engine::renderer
{
	class OrthographicCamera final : Camera
	{
	public:
		OrthographicCamera(float width, float height, float near = -1.f, float far = 1.f);
		~OrthographicCamera() override;

		void SetViewPort(float width, float height, float near = -1.f, float far = 1.f);
		void SetPosition(const glm::vec3& p);
		void SetRotation(float radians);

		// TODO: Continue with the orthographic camera movement implementation.

		const glm::mat4& view() const override;
		const glm::mat4& proj() const override;
		const glm::mat4& viewProj() const override;

	private:
		void RecalcProj();
		void RecalcView();
		void RecalcViewProj();

		float m_width;
		float m_height;
		float m_near;
		float m_far;

		glm::vec3 m_position;
		float m_rotation;

		glm::mat4 m_view;
		glm::mat4 m_proj;
		glm::mat4 m_viewProj;
	};
}