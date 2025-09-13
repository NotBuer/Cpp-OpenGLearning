#pragma once
#include <string>
#include <ostream>

namespace engine::graphics
{

	enum class ShaderType : uint8_t { VERTEX, FRAGMENT };

	inline std::ostream& operator<<(std::ostream& os, ShaderType t)
	{
		switch (t)
		{
		case ShaderType::VERTEX: return os << "VERTEX";
		case ShaderType::FRAGMENT: return os << "FRAGMENT";
		}
		return os << "UNKNOW";
	}

	class Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		void use() const;

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;

		void checkShaderCompilationErrors(unsigned int id, ShaderType type, int& success, char* infoLog);
		void checkShaderProgramLinkingErrors(unsigned int id, int& success, char* infolog);

	private:
		unsigned int Id;
	};

}