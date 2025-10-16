#include "pch.h"
#include "EngineCore/Renderer/detail/GL.hpp"
#include "EngineCore/Renderer/RenderDevice.hpp"

namespace engine::renderer
{
	void RenderDevice::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glDisable(GL_DEPTH_TEST);
	}

	void RenderDevice::BeginPass(const RenderPassDesc& d)
	{
		SetDepthTest(d.clearDepth); // heuristic: if we clear depth, we likely render 3D
		SetBlend(d.clearDepth);     // heuristic: UI/2D often blends, 3D opaque often not

		if (d.clearColor || d.clearDepth)
		{
			GLbitfield mask = 0;
			if (d.clearColor)
			{
				glClearColor(d.clearValue.r, d.clearValue.g, d.clearValue.b, d.clearValue.a);
				mask |= GL_COLOR_BUFFER_BIT; // 0x4000
			}
			if (d.clearDepth)
			{
				glClearDepth(1.0);
				mask |= GL_DEPTH_BUFFER_BIT; // 0x0100
			}
			if (mask) glClear(mask);
		}
	}

	void RenderDevice::Clear(const glm::vec4& color, bool depth)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		GLbitfield mask = GL_COLOR_BUFFER_BIT;
		if (depth) mask |= GL_DEPTH_BUFFER_BIT;
		glClear(mask);
	}

	void RenderDevice::SetDepthTest(bool enabled)
	{
		if (enabled) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
		if (enabled) glDepthFunc(GL_LESS);
	}

	void RenderDevice::SetBlend(bool enabled)
	{
		if (enabled) glEnable(GL_BLEND); else glDisable(GL_BLEND);
	}

	void RenderDevice::SetCullFace(bool enabled)
	{
		if (enabled) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
	}

	void RenderDevice::BindVertexArray(uint32_t vao)
	{
		glBindVertexArray(vao);
	}

	void RenderDevice::DrawIndexed(uint32_t indexCount)
	{
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT, nullptr);
	}

	void RenderDevice::DrawArrays(Primitive primitive, uint32_t first, uint32_t count)
	{
		glDrawArrays(static_cast<GLenum>(primitive), static_cast<GLint>(first), static_cast<GLsizei>(count));
	}
}