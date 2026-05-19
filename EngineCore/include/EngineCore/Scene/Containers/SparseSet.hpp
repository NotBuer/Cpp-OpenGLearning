#pragma once
#include "EngineCore/Core/Assert.hpp"
#include <cstddef>
#include <array>
#include <span>
#include "EngineCore/Scene/Entities/EntityId.hpp"
#include "EngineCore/Scene/Entities/EntityLimits.hpp"

namespace entities = engine::scene::entities;

namespace engine::scene::containers
{
	template<typename T>
	class SparseSet
	{
	public:
		SparseSet()
			: m_count(0)
		{
			m_sparse.fill(entities::kInvalidEntityIndex);
			m_dense_entities.fill({});
			m_dense_components.fill(T{});
		}

		static_assert(std::is_default_constructible_v<T>, "SparseSet<T> requires T to be default-constructible.");
		static_assert(std::is_copy_assignable_v<T>, "SparseSet<T> requires T to be copy-assignable for std::array::fill.");

		void validate() const;

		// TODO: Test by:
		// Create 3 entities, add component to only one, conirm has() returns correctly.
		bool has(entities::EntityId e) const
		{
			if (e.index >= m_sparse.size()) return false;

			const size_t denseIndex = m_sparse[e.index];
			if (denseIndex == entities::kInvalidEntityIndex) return false;
			if (denseIndex < 0) return false;
			if (static_cast<std::size_t>(denseIndex) >= m_count) return false;

			if (m_dense_entities[static_cast<std::size_t>(denseIndex)] != e) return false;

			return true;
		}

		// TODO: Test by:
		// After adding 3 entities, dump arrays and confirm mapping matches the expectation.
		T& add(entities::EntityId e, T value)
		{
			if (e.index >= m_sparse.size()) throw std::out_of_range("EntityId index out of range in SparseSet::add");
			if (has(e)) throw std::runtime_error("Component already exists for entity in SparseSet::add");

			if (m_count >= entities::kMaxEntities) throw std::runtime_error("SparseSet capacity exceeded in SparseSet::add");

			m_dense_entities[m_count] = e;
			m_dense_components[m_count] = value;
			m_sparse[e.index] = static_cast<std::uint16_t>(m_count);
			m_count++;

			validate();

			return m_dense_components[static_cast<std::size_t>(m_sparse[e.index])];
		}

		// TODO: Test by:
		// If remove the component later then try_get() becomes null again.
		T* tryGet(entities::EntityId e) noexcept
		{
			if (!has(e)) return nullptr;
			return &m_dense_components[static_cast<std::size_t>(m_sparse[e.index])];
		}

		const T* tryGet(entities::EntityId e) const noexcept
		{
			if (!has(e)) return nullptr;
			return &m_dense_components[static_cast<std::size_t>(m_sparse[e.index])];
		}

		void remove(entities::EntityId e)
		{
			if (!has(e)) return;

			const std::uint32_t denseIndex = static_cast<std::uint32_t>(m_sparse[e.index]);
			const std::uint32_t lastIndex = static_cast<std::uint32_t>(m_count - 1);

			if (denseIndex != lastIndex)
			{
				const entities::EntityId movedEntity = m_dense_entities[lastIndex];
				m_dense_entities[denseIndex] = movedEntity;
				m_dense_components[denseIndex] = m_dense_components[lastIndex];
				m_sparse[movedEntity.index] = static_cast<std::int32_t>(denseIndex);
			}

			m_sparse[e.index] = entities::kInvalidEntityIndex;
			m_count--;

			validate();
		}

		[[nodiscard]] std::span<const T> components() const { return { m_dense_components.data(), m_count }; }
		[[nodiscard]] std::span<const entities::EntityId> entities() const { return { m_dense_entities.data(), m_count }; }
		[[nodiscard]] std::size_t size() const { return m_count; }

	private:
		std::array<T, entities::kMaxEntities> m_dense_components;
		std::array<entities::EntityId, entities::kMaxEntities> m_dense_entities;
		std::array<std::uint16_t, entities::kMaxEntities> m_sparse;

		std::size_t m_count = 0;

		// m_dense_entities[denseIndex] = entity.
		// m_dense_components[denseIndex] = component.
		// m_sparse[entityIndex] = dense index (or invalid index if missing).
	};

	template<typename T>
	inline void SparseSet<T>::validate() const
	{
		ENGINE_ASSERT(m_count <= entities::kMaxEntities);

		ENGINE_ASSERT(m_dense_entities.size() == m_dense_components.size());

		// Dense to Sparse mapping
		for (std::size_t i = 0; i < m_count; i++)
		{
			ENGINE_ASSERT(m_dense_entities[i].index < entities::kMaxEntities);

			entities::EntityId e = m_dense_entities[i];

			ENGINE_ASSERT(m_sparse[e.index] == i);
			ENGINE_ASSERT(m_sparse[e.index] < m_count);

			// Assertion explanation example:
			// 
			// Dense components:
			// [T5][T2][T9]
			// 
			// Dense entities:
			// [E5][E2][E9]
			//
			// Sparse:
			//	- m_sparse[5] = 0
			//	- m_sparse[2] = 1
			//	- m_sparse[9] = 2
			//
			// Iterations:
			// 0 -> m_dense_entities[0] = E5 -> m_sparse[5] = 0
			// 1 -> m_dense_entities[1] = E2 -> m_sparse[2] = 1
			// 2 -> m_dense_entities[2] = E9 -> m_sparse[9] = 2
		}

		// Sparse to Dense mapping
		for (std::size_t i = 0; i < entities::kMaxEntities; i++)
		{
			if (m_sparse[i] == entities::kInvalidEntityIndex) continue;

			ENGINE_ASSERT(m_sparse[i] < m_count);
			ENGINE_ASSERT(m_dense_entities[m_sparse[i]].index == i);

			// Assertion explanation example:
			// 
			// Dense components:
			// [T0][T1][T2][T3][T4]
			// 
			// Dense entities:
			// [E0][E1][E2][E3][E4]
			//
			// Sparse:
			// [0] [1] [2] [3] [4]
			//
			// Iterations:
			// 0 -> m_sparse[0] = 0 -> m_dense_entities[0] = E0 -> E0.index == 0
			// 1 -> m_sparse[1] = 1 -> m_dense_entities[1] = E1 -> E1.index == 1
			// 2 -> m_sparse[2] = 2 -> m_dense_entities[2] = E2 -> E2.index == 2
			// ...
		}
	}
}
