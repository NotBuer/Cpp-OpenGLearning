#include "pch.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "EngineCore/Renderer/detail/GL.hpp"
#include "EngineCore/Graphics/Shader.hpp"
#include "EngineCore/IO/AssetPath.hpp"
#include "EngineCore/Renderer/SceneRenderer.hpp"
#include "EngineCore/Renderer/RenderDevice.hpp"

namespace engine::renderer
{
	SceneRenderer::SceneRenderer(RenderDevice& device) :
		m_RenderDevice{ device },
		m_SpriteBatch(std::make_unique<engine::renderer::SpriteBatch>(m_RenderDevice))
	{
		m_RenderDevice.Init();
		m_SpriteBatch->Init();
	}

	void SceneRenderer::beginPass(const engine::renderer::RenderPassDesc& pass)
	{
		m_RenderDevice.BeginPass(pass);
		m_RenderDevice.setCullFace(true);
		m_RenderDevice.setViewPort(pass.viewport);
	}

	void SceneRenderer::render(const engine::renderer::RenderView& renderView)
	{
		m_SpriteBatch->shader().Bind();

		m_SpriteBatch->Begin(renderView.camera.view, renderView.camera.proj, false);

		// TODO: Validate this call redundancy, as the call above already defines m_Proj matrix.
		//m_SpriteBatch->SetProjection(renderView.camera.proj); 

		glm::mat4 model{1.0f};

		// TODO: Validate if SceneRenderer should know gl low level calls...
		glUniformMatrix4fv(glGetUniformLocation(m_SpriteBatch->shader().id(), "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(m_SpriteBatch->shader().id(), "view"), 1, GL_FALSE, glm::value_ptr(renderView.camera.view));
		glUniformMatrix4fv(glGetUniformLocation(m_SpriteBatch->shader().id(), "projection"), 1, GL_FALSE, glm::value_ptr(renderView.camera.proj));

		m_SpriteBatch->DrawQuads(renderView.quads);
	}

	void SceneRenderer::endPass()
	{
		m_SpriteBatch->End();
	}
}