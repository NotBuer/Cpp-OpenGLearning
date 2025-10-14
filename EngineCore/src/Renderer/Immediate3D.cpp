#include "pch.h"
#include "EngineCore/Renderer/Immediate3D.hpp"

namespace engine::renderer
{
	Immediate3D::Immediate3D(RenderDevice& device) : m_Device(&device) {}
	Immediate3D::~Immediate3D() { ShutDown(); }

	void Immediate3D::Init()
	{

	}

	void Immediate3D::ShutDown()
	{

	}

	void Immediate3D::Begin(const glm::mat4& view, const glm::mat4& proj)
	{
		m_View = view;
		m_Proj = proj;
		m_Device->SetDepthTest(true);
		m_Device->SetBlend(false);
	}

	void Immediate3D::End()
	{

	}

	// TODO: Create on my own DrawCube method implementation.
}