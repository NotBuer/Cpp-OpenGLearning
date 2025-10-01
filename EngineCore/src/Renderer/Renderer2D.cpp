#include "pch.h"
#include "EngineCore/Renderer/detail/GL.hpp"
#include "EngineCore/Renderer/Renderer2D.hpp"
#include "EngineCore/Renderer/RenderCommand.hpp"

namespace engine::renderer
{
	std::uint32_t Renderer2D::s_VAO = 0;
	std::uint32_t Renderer2D::s_VBO = 0;
	std::uint32_t Renderer2D::s_EBO = 0;
	std::vector<QuadVertex> Renderer2D::s_Vertices;
	std::vector<std::uint32_t> Renderer2D::s_Indices;
	bool Renderer2D::s_Begun = false;

	void Renderer2D::Init()
	{
		RenderCommand::Init();

		glGenVertexArrays(1, &s_VAO);
		glGenBuffers(1, &s_VBO);
		glGenBuffers(1, &s_EBO);

		glBindVertexArray(s_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
		glBufferData(GL_ARRAY_BUFFER, MaxVerts * sizeof(QuadVertex), nullptr, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, MaxIndices * sizeof(std::uint32_t), nullptr, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, position));
		/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)0);*/

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, color));
		/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)(3 * sizeof(float)));*/

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, uv));
		/*glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)(6 * sizeof(float)));*/

		glBindVertexArray(0);

		s_Vertices.reserve(MaxVerts);
		s_Indices.reserve(MaxIndices);
	}

	void Renderer2D::Shutdown()
	{
		if (s_EBO) glDeleteBuffers(1, &s_EBO);
		if (s_VBO) glDeleteBuffers(1, &s_VBO);
		if (s_VAO) glDeleteVertexArrays(1, &s_VAO);

		s_VAO = s_VBO = s_EBO = 0;
		s_Vertices.clear();
		s_Indices.clear();
	}

	void Renderer2D::ClearFrame(const glm::vec4& color)
	{
		RenderCommand::Clear(color);
	}

	void Renderer2D::BeginFrame()
	{
		s_Begun = true;
		StartBatch();
		RenderCommand::BindVertexArray(s_VAO);
	}

	void Renderer2D::EndFrame()
	{
		if (!s_Begun) return;
		Flush();
		s_Begun = false;
		RenderCommand::BindVertexArray(0);
	}

	void Renderer2D::BeginPass(const engine::graphics::Shader& shader)
	{
		if (s_CurrentShader && s_CurrentShader != &shader)
		{
			if (s_Begun)
			{
				Flush();
				s_Begun = false;
			}
		}

		s_CurrentShader = &shader;

		s_CurrentShader->Bind();

		if (!s_Begun)
		{
			StartBatch();
			s_Begun = true;
		}
	}

	void Renderer2D::EndPass()
	{
		if (!s_CurrentShader)
		{
			assert(!s_CurrentShader && "EndPass only should be called when there is a shader bound!");
			return;
		}

		if (s_Begun)
		{
			Flush();
			s_Begun = false;
		}

		s_CurrentShader = nullptr;
	}

	void Renderer2D::DrawQuad(const glm::vec2& min, const glm::vec2& size, const glm::vec4& color)
	{
		assert(s_CurrentShader && "DrawQuad called without an active pass. Call BeginPass(shader) first!");

		if (!s_Begun) return;

		if (s_Vertices.size() + 4 > MaxVerts || s_Indices.size() + 6 > MaxIndices)
		{
			Flush();
			StartBatch();
		}

		const float z = 0.0f;
		glm::vec2 max = { min.x + size.x, min.y + size.y };
		std::uint32_t base = static_cast<std::uint32_t>(s_Vertices.size());

		s_Vertices.push_back({ { min.x, max.y, z }, color, {0.0f, 1.0f} }); // top-left
		s_Vertices.push_back({ { max.x, max.y, z }, color, {1.0f, 1.0f} }); // top-right
		s_Vertices.push_back({ { max.x, min.y, z }, color, {1.0f, 0.0f} }); // bottom-right
		s_Vertices.push_back({ { min.x, min.y, z }, color, {0.0f, 0.0f} }); // bottom-left

		s_Indices.push_back(base + 0);
		s_Indices.push_back(base + 1);
		s_Indices.push_back(base + 3);
		s_Indices.push_back(base + 1);
		s_Indices.push_back(base + 2);
		s_Indices.push_back(base + 3);
	}

	void Renderer2D::StartBatch()
	{
		s_Vertices.clear();
		s_Indices.clear();
	}

	void Renderer2D::Upload()
	{
		glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, s_Vertices.size() * sizeof(QuadVertex), s_Vertices.data());

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_EBO);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, s_Indices.size() * sizeof(QuadVertex), s_Indices.data());
	}

	void Renderer2D::Flush()
	{
		if (s_Indices.empty()) return;
		Upload();
		RenderCommand::DrawIndexed(static_cast<std::uint32_t>(s_Indices.size()));
		StartBatch();
	}
}