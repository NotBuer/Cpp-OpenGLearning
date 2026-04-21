#include "pch.h"
#include "EngineCore/Renderer/detail/GL.hpp"
#include "EngineCore/Renderer/SpriteBatch.hpp"
#include "EngineCore/IO/AssetPath.hpp"
#include "EngineCore/Renderer/QuadVertex.hpp"

namespace engine::renderer
{
	SpriteBatch::SpriteBatch(RenderDevice& dev) : 
		m_Device(&dev),
		m_Shader(std::make_unique<graphics::Shader>())
	{
	
	}

	SpriteBatch::~SpriteBatch() { Shutdown(); }

	void SpriteBatch::Init(bool useShaders)
	{
		// Buffers.
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, MaxVerts * sizeof(QuadVertex), nullptr, GL_DYNAMIC_DRAW);

		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, MaxIndices * sizeof(std::uint32_t), nullptr, GL_DYNAMIC_DRAW);

		// Vertex layout.
		glEnableVertexAttribArray(0); // pos
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, pos));

		glEnableVertexAttribArray(1); // color
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, color));

		glEnableVertexAttribArray(2); // uv
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, uv));

		if (useShaders)
		{
			std::string log;
			if (!m_Shader->Compile(
				engine::graphics::Shader::LoadFromSource(engine::io::shader("basic.vert").c_str()),
				engine::graphics::Shader::LoadFromSource(engine::io::shader("basic.frag").c_str()),
				&log))
			{
				std::cerr << "SHADER COMPILE ERROR: " << log << std::endl;
			}
		}

		m_Vertices.reserve(MaxVerts);
		m_Indices.reserve(MaxIndices);
	}

	void SpriteBatch::Shutdown()
	{
		if (m_Shader)
		{
			m_Shader->Destroy();
			m_Shader = nullptr;
		}
		if (m_EBO) { glDeleteBuffers(1, &m_EBO); m_EBO = 0; }
		if (m_VBO) { glDeleteBuffers(1, &m_VBO); m_VBO = 0; }
		if (m_VAO) { glDeleteVertexArrays(1, &m_VAO); m_VAO = 0; }
	}

	void SpriteBatch::SetProjection(const glm::mat4& proj) { m_Proj = proj; }

	//[[deprecated("This function is obsolete due to the new architecture changes")]] 
	void SpriteBatch::Begin(const glm::mat4& view, const glm::mat4& proj, bool useDeviceDefaults)
	{
		m_View = view;
		m_Proj = proj;

		if (useDeviceDefaults)
		{
			m_Device->SetDepthTest(false);
			m_Device->SetBlend(false);
			m_Device->setCullFace(true);
		}

		m_Begun = true;
		StartBatch();
	}

	void SpriteBatch::End()
	{
		if (!m_Begun) return;
		Upload();
		Flush();
		m_Begun = false;
	}

	void SpriteBatch::DrawQuad(const glm::vec2& min, const glm::vec2& size, const glm::vec4& color)
	{
		if (!m_Begun) return;

		if (m_Vertices.size() + 4 > MaxVerts || m_Indices.size() + 6 > MaxIndices)
		{
			End();
			Begin(m_View, m_Proj);
		}

		float x = min.x, y = min.y;
		float w = size.x, h = size.y;
		std::uint32_t base = static_cast<std::uint32_t>(m_Vertices.size());

		m_Vertices.push_back({ { x,		y,	   0.f }, color, {0.f, 0.f} });
		m_Vertices.push_back({ { x + w, y,	   0.f }, color, {1.f, 0.f} });
		m_Vertices.push_back({ { x + w, y + h, 0.f }, color, {1.f, 1.f} });
		m_Vertices.push_back({ { x,		y + h, 0.f }, color, {0.f, 1.f} });

		m_Indices.push_back(base + 0);
		m_Indices.push_back(base + 1);
		m_Indices.push_back(base + 2);
		m_Indices.push_back(base + 2);
		m_Indices.push_back(base + 3);
		m_Indices.push_back(base + 0);
	}

	void SpriteBatch::DrawQuads(std::span<const QuadVertex> quads)
	{
		if (!m_Begun) return;

		if (m_Vertices.size() + 4 > MaxVerts || m_Indices.size() + 6 > MaxIndices)
		{
			End();
			Begin(m_View, m_Proj);
		}

		for (const QuadVertex& quad : quads)
		{
			float x = quad.pos.x, y = quad.pos.y;
			float w = 1, h = 1; // Not using any other scale than 1 for now...
			std::uint32_t base = static_cast<std::uint32_t>(m_Vertices.size());

			m_Vertices.push_back({ { x,		y,	   0.f }, quad.color, {0.f, 0.f} });
			m_Vertices.push_back({ { x + w, y,	   0.f }, quad.color, {1.f, 0.f} });
			m_Vertices.push_back({ { x + w, y + h, 0.f }, quad.color, {1.f, 1.f} });
			m_Vertices.push_back({ { x,		y + h, 0.f }, quad.color, {0.f, 1.f} });

			m_Indices.push_back(base + 0);
			m_Indices.push_back(base + 1);
			m_Indices.push_back(base + 2);
			m_Indices.push_back(base + 2);
			m_Indices.push_back(base + 3);
			m_Indices.push_back(base + 0);
		}
	}

	void SpriteBatch::StartBatch()
	{
		m_Vertices.clear();
		m_Indices.clear();
	}

	void SpriteBatch::Upload()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(QuadVertex), m_Vertices.data());

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_Indices.size() * sizeof(std::uint32_t), m_Indices.data());
	}

	void SpriteBatch::Flush()
	{
		m_Device->BindVertexArray(m_VAO);
		m_Device->DrawIndexed(static_cast<uint32_t>(m_Indices.size()));
	}
}