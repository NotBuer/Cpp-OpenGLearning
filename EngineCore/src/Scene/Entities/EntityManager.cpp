#include <pch.h>
#include "EngineCore/Scene/Entities/EntityId.hpp"
#include "EngineCore/Scene/Entities/EntityManager.hpp"

namespace engine::scene::entities
{
	EntityManager::EntityManager() :
		m_freeCount(kMaxEntities)
	{
		// 0 -> kMaxEntities(65535)
		for (std::size_t i = 0; i < kMaxEntities; ++i)
		{
			m_generations[i] = 0;
			m_alive[i] = false;

			// Free index mark basically is inversely proportional to the capacity.
			// [0]     = (65535 - 1 - i(0))	    = 65534
			// [1000]  = (65535 - 1 - i(1000))  = 64534
			// [32767] = (65535 - 1 - i(32768)) = 32767
			// [65524] = (65535 - 1 - i(64524)) = 10
			// [65534] = (65535 - 1 - i(64534)) = 0
			m_freeIndices[i] = static_cast<EntityIndex>(kMaxEntities - 1 - i);
		}
	}

	EntityId EntityManager::create()
	{
		if (m_freeCount == 0)
			throw std::runtime_error("Entity capacity exceeded in EntityManager::create");

		// Following the inversely proportional order from kMaxEntities - 1 to 0.
		// Example:
		// m_freeCount -> (kMaxEntities - 1) = 65534
		// m_freeIndices[kMaxEntities(65535)]
		// m_freeIndices[--m_freeCount] -> m_freeIndices[65534] -> 0
		// ...
		// m_freeIndices[65524] = 10
		// m_freeIndices[--m_freeCount] -> m_freeIndices[65523] -> 11
		const EntityIndex index = m_freeIndices[--m_freeCount];
		m_alive[index] = true;

		return EntityId{
			.index = index,
			.generation = m_generations[index]
		};
	}

	void EntityManager::destroy(EntityId id)
	{
		if (!isAlive(id))
			return;

		m_alive[id.index] = false;
		++m_generations[id.index];
		m_freeIndices[m_freeCount++] = id.index;
	}

	bool EntityManager::isAlive(EntityId id) const
	{
		if (!id.isValid()) return false;
		if (id.index >= kMaxEntities) return false;

		// Only marked as alive and from the same generation "version".
		return m_alive[id.index] && m_generations[id.index] == id.generation;
	}
}