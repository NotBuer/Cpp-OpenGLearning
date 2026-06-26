#pragma once
#include <cstdint>

namespace engine::renderer::stats 
{
    /// @brief Public stats snapshot view for higher layers upstream.
    struct SceneRendererStats
    {
        std::uint32_t inputQuadCount = 0;
        std::uint32_t resolvedQuadCount = 0;
        std::uint32_t drawCallCount = 0;
        std::uint32_t flushCount = 0;
        std::uint32_t textureSwitchCount = 0;
    };
}