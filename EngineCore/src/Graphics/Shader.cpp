#include "pch.h"
#include <gtc/type_ptr.hpp>
#include "EngineCore/Renderer/detail/GL.hpp"
#include "EngineCore/Graphics/Shader.hpp"

namespace engine::graphics
{
	std::string Shader::LoadFromSource(const char* shaderPath)
	{
		std::string shaderCode;
		try
		{
			std::ifstream shaderFile(shaderPath, std::ios::binary);
			if (!shaderFile) throw std::runtime_error("ERROR::SHADER::WRONG_SHADER_PATH_UNABLE_TO_READ\n");

			std::ostringstream oss;
			oss << shaderFile.rdbuf();
			shaderCode = oss.str();
		}
		catch (const std::exception& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << e.what() << std::endl;
		}
		return shaderCode;
	}

	static unsigned CompileStage(GLenum type, std::string_view src, std::string* outLog)
	{
		unsigned s = glCreateShader(type);
		const char* srcPtr = src.data();
		GLint srcLen = static_cast<GLint>(src.size());
		glShaderSource(s, 1, &srcPtr, &srcLen);
		glCompileShader(s);
		GLint ok = 0; 
		glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
		if (!ok)
		{
			GLint len = 0; 
			glGetShaderiv(s, GL_INFO_LOG_LENGTH, &len);
			std::string log(len, '\0'); 
			glGetShaderInfoLog(s, len, nullptr, log.data());
			if (outLog) *outLog += log;
			glDeleteShader(s);
			return 0;
		}
		return s;
	}

	bool Shader::Compile(std::string_view vsSrc, std::string_view fsSrc, std::string* errorLog)
	{
		unsigned vs = CompileStage(GL_VERTEX_SHADER, vsSrc, errorLog);
		if (!vs) return false;
		unsigned fs = CompileStage(GL_FRAGMENT_SHADER, fsSrc, errorLog);
		if (!fs) { glDeleteShader(vs); return false; }

		m_program = glCreateProgram();
		glAttachShader(m_program, vs);
		glAttachShader(m_program, fs);
		glLinkProgram(m_program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		GLint ok = 0;
		glGetProgramiv(m_program, GL_LINK_STATUS, &ok);
		if (!ok)
		{
			GLint len = 0;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &len);
			std::string log(len, '\0');
			glGetProgramInfoLog(m_program, len, nullptr, log.data());
			if (errorLog) *errorLog += log;
			glDeleteProgram(m_program);
			m_program = 0;
			return false;
		}
		return true;
	}

	void Shader::Destroy()
	{
		if (m_program) { 
			glDeleteProgram(m_program);
			m_program = 0;
		}
	}

	Shader::~Shader() { Destroy(); }

	Shader::Shader(Shader&& o) noexcept { m_program = o.m_program; o.m_program = 0; }
	Shader& Shader::operator=(Shader&& o) noexcept
	{
		if (this == &o) return *this;
		Destroy();
		m_program = o.m_program; 
		o.m_program = 0;
		return *this;
	}

	void Shader::Bind() const { glUseProgram(m_program); }

	void Shader::setBool(const char* name, bool value) const
	{
		GLint loc = glGetUniformLocation(m_program, name);
		glUniform1i(loc, value);
	}

	void Shader::setInt(const char* name, int value) const
	{
		GLint loc = glGetUniformLocation(m_program, name);
		glUniform1i(loc, value);
	}

	void Shader::setFloat(const char* name, float value) const
	{
		GLint loc = glGetUniformLocation(m_program, name);
		glUniform1f(loc, value);
	}

	void Shader::setMat4(const char* name, const glm::mat4& matrix) const
	{
		GLint loc = glGetUniformLocation(m_program, name);
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::setVec4(const char* name, const glm::vec4& vector) const
	{
		GLint loc = glGetUniformLocation(m_program, name);
		glUniform4fv(loc, 1, &vector.x);
	}
}