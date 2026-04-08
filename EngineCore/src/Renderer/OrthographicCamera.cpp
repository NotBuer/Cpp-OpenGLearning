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
		m_pos(0.0f, 0.0f, 3.0f),
		m_rotation(0.0f),
		m_view(1.0f),
		m_proj(1.0f),
		m_viewProj(1.0f)
	{
		RecalcProj();
		RecalcView();
		RecalcViewProj();
	}

	OrthographicCamera::~OrthographicCamera() = default;

	void OrthographicCamera::SetViewPort(float width, float height, float near, float far)
	{
		m_width = width; m_height = height; m_near = near; m_far = far;
		RecalcProj();
		RecalcViewProj();
	}

	void OrthographicCamera::SetPosition(const glm::vec3& p)
	{
		m_pos = p;
		RecalcView();
		RecalcViewProj();
	}

	void OrthographicCamera::SetRotation(float radians)
	{
		m_rotation = radians;
		RecalcView();
		RecalcViewProj();
	}

	const glm::mat4& OrthographicCamera::view() const { return m_view; }
	const glm::mat4& OrthographicCamera::proj() const { return m_proj; }
	const glm::mat4& OrthographicCamera::viewProj() const { return m_viewProj; }

	void OrthographicCamera::RecalcProj()
	{
		m_proj = glm::ortho(-m_width * 0.5f, m_width * 0.5f, -m_height * 0.5f, m_height * 0.5f, m_near, m_far);
	}

	void OrthographicCamera::RecalcView()
	{
		glm::mat4 transform{ 1.0f };
		transform = glm::translate(transform, m_pos);
		transform = glm::rotate(transform, m_rotation, glm::vec3(0.f, 0.f, 1.f));

		m_view = glm::inverse(transform);
	}

	void OrthographicCamera::RecalcViewProj()
	{
		m_viewProj = m_proj * m_view;
	}
}