#include "pch.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "EngineCore/Renderer/OrthographicCamera.hpp"

namespace engine::renderer
{
	OrthographicCamera::OrthographicCamera(float width, float height, float near, float far) :
		m_width(width),
		m_height(height),
		m_near(near),
		m_far(far),
		m_view(1.0f),
		m_proj(1.0f),
		m_viewProj(1.0f)
	{
		RecalcProj();
		RecalcViewProj();
	}

	OrthographicCamera::~OrthographicCamera() = default;

	void OrthographicCamera::SetViewPort(float width, float height, float near, float far)
	{
		m_width = width; m_height = height; m_near = near; m_far = far;
		RecalcProj();
		RecalcViewProj();
	}

	const glm::mat4& OrthographicCamera::view() const { return m_view; }
	const glm::mat4& OrthographicCamera::proj() const { return m_proj; }
	const glm::mat4& OrthographicCamera::viewProj() const { return m_viewProj; }

	void OrthographicCamera::RecalcProj()
	{
		m_proj = glm::ortho(0.0f, m_width, 0.0f, m_height, m_near, m_far);
	}

	void OrthographicCamera::RecalcViewProj()
	{
		m_viewProj = m_proj * m_view;
	}
}