#include "pch.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <cmath>
#include <algorithm>
#include "EngineCore/Renderer/PerspectiveCamera.hpp"

namespace engine::renderer
{
	PerspectiveCamera::PerspectiveCamera(float fovDeg, float aspect, float near, float far) : 
		m_fov(fovDeg),
		m_aspect(aspect),
		m_near(near),
		m_far(far),
		m_pos(0.0f, 0.0f, 3.0f),
		m_yawDeg(-90.0f),
		m_pitchDeg(0.0f),
		m_forward(0.0f, 0.0f, -1.0f),
		m_right(1.0f, 0.0f, 0.0f),
		m_up(0.0f, 1.0f, 0.0f),
		m_view(1.0f),
		m_proj(1.0f),
		m_viewProj(1.0f)
	{
		RecalcProj();
		RecalcView();
		RecalcViewProj();
	}

	PerspectiveCamera::~PerspectiveCamera() = default;

	void PerspectiveCamera::SetPosition(const glm::vec3& p)
	{
		m_pos = p;
		RecalcView();
		RecalcViewProj();
	}

	void PerspectiveCamera::AddYawPitch(float yawDeg, float pitchDeg)
	{
		m_yawDeg += yawDeg;
		m_pitchDeg = glm::clamp(m_pitchDeg + pitchDeg, -89.9f, 89.9f);
		RecalcView();
		RecalcViewProj();
	}

	void PerspectiveCamera::MoveLocal(const glm::vec3& localDelta)
	{
		m_pos += localDelta.x * m_right + localDelta.y * m_up + localDelta.z * m_forward;
		RecalcView();
		RecalcViewProj();
	}

	void PerspectiveCamera::SetAspect(float a)
	{
		m_aspect = a;
		RecalcProj();
		RecalcViewProj();
	}

	const glm::mat4& PerspectiveCamera::view() const { return m_view; }
	const glm::mat4& PerspectiveCamera::proj() const { return m_proj; }
	const glm::mat4& PerspectiveCamera::viewProj() const { return m_viewProj; }

	float PerspectiveCamera::fov() const { return m_fov; }
	float PerspectiveCamera::aspect() const { return m_aspect; }
	float PerspectiveCamera::near() const { return m_near; }
	float PerspectiveCamera::far() const { return m_far; }
	const glm::vec3& PerspectiveCamera::position() const { return m_pos; }

	void PerspectiveCamera::RecalcProj()
	{
		m_proj = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
	}

	void PerspectiveCamera::RecalcView()
	{
		const float cy = std::cos(glm::radians(m_yawDeg));
		const float sy = std::sin(glm::radians(m_yawDeg));
		const float cp = std::cos(glm::radians(m_pitchDeg));
		const float sp = std::sin(glm::radians(m_pitchDeg));

		m_forward = glm::normalize(glm::vec3(cy * cp, sp, sy * cp));
		m_right = glm::normalize(glm::cross(m_forward, glm::vec3(0.0f, 1.0f, 0.0f)));
		m_up = glm::normalize(glm::cross(m_right, m_forward));

		m_view = glm::lookAt(m_pos, m_pos + m_forward, m_up);
	}

	void PerspectiveCamera::RecalcViewProj()
	{
		m_viewProj = m_proj * m_view;
	}
}