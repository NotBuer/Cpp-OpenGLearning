#include "pch.h"
#include "EngineCore/Renderer/detail/GL.hpp"
#include "EngineCore/Renderer/Immediate3D.hpp"
#include "EngineCore/IO/AssetPath.hpp"

namespace engine::renderer
{
	Immediate3D::Immediate3D(RenderDevice& device) :
		m_Device(&device),
		m_Shader(std::make_unique<graphics::Shader>())
	{

	}

	Immediate3D::~Immediate3D() { ShutDown(); }

	void Immediate3D::Init()
	{
		// Buffers.
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, VoxelVertex::MaxVerts * sizeof(VoxelVertex), nullptr, GL_DYNAMIC_DRAW);

		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, VoxelVertex::MaxIndices * sizeof(std::uint32_t), nullptr, GL_DYNAMIC_DRAW);

		// Vertex layout.
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VoxelVertex), (const void*)offsetof(VoxelVertex, pos));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VoxelVertex), (const void*)offsetof(VoxelVertex, color));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VoxelVertex), (const void*)offsetof(VoxelVertex, uv));

		// Shader.
		std::string log;
		if (!m_Shader->Compile(
			engine::graphics::Shader::LoadFromSource(engine::io::shader("basic.vert").c_str()),
			engine::graphics::Shader::LoadFromSource(engine::io::shader("basic.frag").c_str()),
			&log))
		{
			std::cerr << "SHADER COMPILE ERROR: " << log << std::endl;
		}
	}

	void Immediate3D::ShutDown()
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

	void Immediate3D::SetProjection(const glm::mat4& proj) { m_Proj = proj; }

	void Immediate3D::Begin(const glm::mat4& view, const glm::mat4& proj)
	{
		m_View = view;
		m_Proj = proj;
		m_Device->SetDepthTest(true);
		m_Device->SetBlend(false);
	}

	void Immediate3D::End()
	{
		Upload();

		m_Device->BindVertexArray(m_VAO);
		m_Device->DrawIndexed(static_cast<uint32_t>(m_Indices.size()));

		m_Vertices.clear();
		m_Indices.clear();
	}

	void Immediate3D::DrawCube(const glm::vec3& min, const glm::vec3& size, const glm::vec4& color)
	{
		float x = min.x, y = min.y, z = min.z;
		float w = size.x, h = size.y, d = size.z;

		const float x0 = x, x1 = x + w;
		const float y0 = y, y1 = y + h;
		const float z0 = z, z1 = z + d;

		// Front-face (Z+)
		m_Vertices.push_back({ .pos{x0,y0,z1}, .color{color}, .uv{0.f, 0.f} });	// Bottom-Left.
		m_Vertices.push_back({ .pos{x1,y0,z1}, .color{color}, .uv{1.f, 0.f} });	// Bottom-Right.
		m_Vertices.push_back({ .pos{x1,y1,z1}, .color{color}, .uv{1.f, 1.f} });	// Top-Right.
		m_Vertices.push_back({ .pos{x0,y1,z1}, .color{color}, .uv{0.f, 1.f} });	// Top-Left.

		// Right-face (X+)
		m_Vertices.push_back({ .pos{x1,y0,z1}, .color{color}, .uv{0.f, 0.f} });	// Bottom-Left.
		m_Vertices.push_back({ .pos{x1,y0,z0}, .color{color}, .uv{1.f, 0.f} });	// Bottom-Right.
		m_Vertices.push_back({ .pos{x1,y1,z0}, .color{color}, .uv{1.f, 1.f} });	// Top-Right.
		m_Vertices.push_back({ .pos{x1,y1,z1}, .color{color}, .uv{0.f, 1.f} });	// Top-Left.

		// Back-face (Z-)
		m_Vertices.push_back({ .pos{x1,y0,z0}, .color{color}, .uv{0.f, 0.f} });	// Bottom-Left.
		m_Vertices.push_back({ .pos{x0,y0,z0}, .color{color}, .uv{1.f, 0.f} });	// Bottom-Right.
		m_Vertices.push_back({ .pos{x0,y1,z0}, .color{color}, .uv{1.f, 1.f} });	// Top-Right.
		m_Vertices.push_back({ .pos{x1,y1,z0}, .color{color}, .uv{0.f, 1.f} });	// Top-Left.

		// Left-face (X-)
		m_Vertices.push_back({ .pos{x0,y0,z0}, .color{color}, .uv{0.f, 0.f} });	// Bottom-Left.
		m_Vertices.push_back({ .pos{x0,y0,z1}, .color{color}, .uv{1.f, 0.f} });	// Bottom-Right.
		m_Vertices.push_back({ .pos{x0,y1,z1}, .color{color}, .uv{1.f, 1.f} });	// Top-Right.
		m_Vertices.push_back({ .pos{x0,y1,z0}, .color{color}, .uv{0.f, 1.f} });	// Top-Left.

		// Bottom-face (Y-)
		m_Vertices.push_back({ .pos{x0,y0,z0}, .color{color}, .uv{0.f, 0.f} });	// Bottom-Left.
		m_Vertices.push_back({ .pos{x1,y0,z0}, .color{color}, .uv{1.f, 0.f} });	// Bottom-Right.
		m_Vertices.push_back({ .pos{x1,y0,z1}, .color{color}, .uv{1.f, 1.f} });	// Top-Right.
		m_Vertices.push_back({ .pos{x0,y0,z1}, .color{color}, .uv{0.f, 1.f} });	// Top-Left.

		// Top-face (Y+)
		m_Vertices.push_back({ .pos{x0,y1,z1}, .color{color}, .uv{0.f, 0.f} });	// Bottom-Left.
		m_Vertices.push_back({ .pos{x1,y1,z1}, .color{color}, .uv{1.f, 0.f} });	// Bottom-Right.
		m_Vertices.push_back({ .pos{x1,y1,z0}, .color{color}, .uv{1.f, 1.f} });	// Top-Right.
		m_Vertices.push_back({ .pos{x0,y1,z0}, .color{color}, .uv{0.f, 1.f} });	// Top-Left.

		for (std::uint32_t i = 0; i < m_Vertices.size(); i += VoxelVertex::FaceVertexCount)
		{
			m_Indices.push_back(i + 0); 
			m_Indices.push_back(i + 1);
			m_Indices.push_back(i + 2);
			m_Indices.push_back(i + 2);
			m_Indices.push_back(i + 3);
			m_Indices.push_back(i + 0);
		}
	}

	void Immediate3D::Upload()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(VoxelVertex), m_Vertices.data());

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_Indices.size() * sizeof(std::uint32_t), m_Indices.data());
	}
}