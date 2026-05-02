#include "pch.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "EngineCore/Renderer/OrthographicCamera.hpp"

namespace engine::renderer
{
	OrthographicCamera::OrthographicCamera(float worldHeight, float aspectRatio, float near, float far) :
		m_worldHeight(worldHeight),
		m_aspectRatio(aspectRatio),
		m_near(near),
		m_far(far),
		m_pos(0.0f, 0.0f, 0.0f),
		m_rotation(0.0f),
		m_view(1.0f),
		m_proj(1.0f),
		m_viewProj(1.0f)
	{
		SetViewPort(aspectRatio);
		RecalcView();
	}

	OrthographicCamera::~OrthographicCamera() = default;

	void OrthographicCamera::SetViewPort(float aspectRatio)
	{
		m_width = m_worldHeight * aspectRatio;
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

	[[nodiscard]] const glm::mat4& OrthographicCamera::view() const noexcept { return m_view; }
	[[nodiscard]] const glm::mat4& OrthographicCamera::proj() const noexcept { return m_proj; }
	[[nodiscard]] const glm::mat4& OrthographicCamera::viewProj() const noexcept { return m_viewProj; }
	[[nodiscard]] const glm::vec3& OrthographicCamera::position() const noexcept { return m_pos; }

	void OrthographicCamera::RecalcProj()
	{
		m_proj = glm::ortho(-m_width * 0.5f, m_width * 0.5f, -m_worldHeight * 0.5f, m_worldHeight * 0.5f, m_near, m_far);
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