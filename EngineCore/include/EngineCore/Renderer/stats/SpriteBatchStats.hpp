#pragma once
#include <cstdint>

namespace engine::renderer::stats
{
    /// @brief Private lower-level stats snapshot.
    struct SpriteBatchStats
    {
        std::uint16_t submittedQuadCount = 0;
        std::uint16_t flushCount = 0;
        std::uint16_t drawCallCount = 0;
        std::uint16_t textureSwitchCount = 0;
    };
}