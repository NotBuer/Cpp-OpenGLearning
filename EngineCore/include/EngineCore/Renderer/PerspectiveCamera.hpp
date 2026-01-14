#pragma once
#include "EngineCore/Renderer/Camera.hpp"

namespace engine::renderer
{
	class PerspectiveCamera final : public Camera 
	{
	public:
		PerspectiveCamera(float fovDeg, float aspect, float near, float far);
		~PerspectiveCamera() override;

		void SetPosition(const glm::vec3& p);
		void AddYawPitch(float yawDeg, float pitchDeg);
		void MoveLocal(const glm::vec3& localDelta);
		void SetAspect(float a);

		const glm::mat4& view() const override;
		const glm::mat4& proj() const override;
		const glm::mat4& viewProj() const override;

		float fov() const;
		float aspect() const;
		float near() const;
		float far() const;

		const glm::vec3& position() const;
		
	private:
		void RecalcProj();
		void RecalcView();
		void RecalcViewProj();

		float m_fov;
		float m_aspect;
		float m_near;
		float m_far;

		glm::vec3 m_pos;
		float m_yawDeg;
		float m_pitchDeg;

		glm::vec3 m_forward;
		glm::vec3 m_right;
		glm::vec3 m_up;

		glm::mat4 m_view;
		glm::mat4 m_proj;
		glm::mat4 m_viewProj;
	};
}