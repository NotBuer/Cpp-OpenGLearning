#pragma once
#include <string>

namespace engine::scene
{
	class Scene
	{
	public:
		Scene(const std::string& name);

		const std::string& getName() const { return m_name; }

	private:
		std::string m_name;
	};
}