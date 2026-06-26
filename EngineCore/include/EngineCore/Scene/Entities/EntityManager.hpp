#pragma once
#include <array>
#include "EngineCore/Scene/Entities/EntityId.hpp"
#include "EngineCore/Scene/Entities/EntityLimits.hpp"

namespace engine::scene::entities
{
	class EntityManager
	{
	public:
		EntityManager();

		EntityId create();
		void destroy(EntityId id);
		bool isAlive(EntityId id) const;

		std::span<const bool> alive() const noexcept { return m_alive; };
		std::size_t aliveCount() noexcept { return m_alive.size(); }

	private:
		std::array<EntityGeneration, kMaxEntities> m_generations{};
		std::array<bool, kMaxEntities> m_alive{};
		std::array<EntityIndex, kMaxEntities> m_freeIndices{};
		std::size_t m_freeCount = 0;
	};
}