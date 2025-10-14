#pragma once
#include <string>
#include <ostream>
#include <vec4.hpp>
#include <mat4x4.hpp>

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
		Shader() = default;
		~Shader();

		// Non-copyable, movable
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader(Shader&&) noexcept;
		Shader& operator=(Shader&&) noexcept;

		static std::string LoadFromSource(const char* shaderPath);
		bool Compile(std::string_view vsSrc, std::string_view fsSrc, std::string* errorLog = nullptr);
		void Destroy();

		void Bind() const;

		void setBool(const char* name, bool value) const;
		void setInt(const char* name, int value) const;
		void setFloat(const char* name, float value) const;
		void setMat4(const char* name, const glm::mat4& matrix) const;
		void setVec4(const char* name, const glm::vec4& vector) const;

		const int& id() const { return m_program; }

	private:
		unsigned m_program = 0;
	};

}