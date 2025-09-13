#pragma once
#include <string>

namespace engine::io
{

// If OpenGLearning defines ASSETS_DIR macro (e.g., R"($(ProjectDir)..\assets)"),
// use it; otherwise default to "assets".
#ifndef ASSETS_DIR
	inline constexpr const char* kAssetsRoot = ASSETS_DIR;
#else
	inline constexpr const char* kAssetsRoot = "assets";
#endif // !ASSETS_DIR

	inline std::string shader(const char* fileName)
	{
		return std::string(kAssetsRoot) + "/shaders/" + fileName;
	}

}