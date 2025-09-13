#include "pch.h"
#include "EngineCore/Graphics/Shader.hpp"

#include <glad/glad.h>

namespace engine::graphics
{
	// TODO: refactor boilerplate code to common function later on...
	Shader::Shader(const char* vPath, const char* fPath)
	{
		std::string vertexCode;
		std::string fragmentCode;

		try
		{
			std::ifstream vShaderFile(vPath, std::ios::binary);
			std::ifstream fShaderFile(fPath, std::ios::binary);

			if (!vShaderFile || !fShaderFile)
				throw std::runtime_error("ERROR::SHADER::WRONG_SHADER_PATH_UNABLE_TO_READ\n");

			std::ostringstream vs, fs;
			vs << vShaderFile.rdbuf();
			fs << fShaderFile.rdbuf();

			vertexCode = vs.str();
			fragmentCode = fs.str();
		}
		catch (const std::exception& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << e.what() << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		Id = glCreateProgram();
		glAttachShader(Id, vertex);
		glAttachShader(Id, fragment);
		glLinkProgram(Id);
		glGetProgramiv(Id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(Id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	Shader::~Shader() {}

	void Shader::use() const
	{
		glUseProgram(Id);
	}

	void Shader::setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(Id, name.c_str()), (int)value);
	}

	void Shader::setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(Id, name.c_str()), (int)value);
	}

	void Shader::setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(Id, name.c_str()), (int)value);
	}

}