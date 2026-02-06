#pragma once
#include <cstddef>
#include <array>
#include "EngineCore/Scene/Entities/EntityId.hpp"

namespace engine::scene 
{
	inline constexpr std::size_t kMaxEntities = 0xFFFF;
	inline constexpr std::int32_t kInvalidIndex = -1;

	template<typename T>
	class SparseSet
	{
	public:
		// TODO: Ctor that initializes sparse to kInvalidIndex and dense's to kMaxEntities.

		void validate() const;

		// TODO: Test by:
		// Create 3 entities, add component to only one, confirm has() returns correctly.
		bool has(EntityId e) const
		{
			if (e.index >= sparse.size()) return false;

			const std::int32_t denseIndex = sparse[e.index];
			if (denseIndex == kInvalidIndex) return false;
			if (denseIndex < 0) return false;
			if (static_cast<std::size_t>(denseIndex) >= count) return false;

			if (dense_entities[static_cast<std::size_t>(denseIndex)] != e) return false;

			return true;
		}

		// TODO: Test by:
		// After adding 3 entities, dump arrays and confirm mapping matches the expectation.
		T& add(EntityId e, T value)
		{
			if (e.index >= sparse.size()) throw std::out_of_range("EntityId index out of range in SparseSet::add");
			if (has(e)) throw std::runtime_error("Component already exists for entity in SparseSet::add");

			if (count >= kMaxEntities) throw std::runtime_error("SparseSet capacity exceeded in SparseSet::add");

			dense_entities[count] = e;
			dense_components[count] = value;
			sparse[e.index] = static_cast<std::int32_t>(count);
			count++;

			return dense_components[static_cast<std::size_t>(sparse[e.index])];
		}

		// TODO: Test by:
		// If remove the component later then try_get() becomes null again.
		T* tryGet(EntityId e) noexcept
		{
			if (!has(e)) return nullptr;
			return &dense_components[static_cast<std::size_t>(sparse[e.index])];
		}

		const T* tryGet(EntityId e) const noexcept
		{
			if (!has(e)) return nullptr;
			return &dense_components[static_cast<std::size_t>(sparse[e.index])];
		}

		void remove(EntityId e)
		{
			if (!has(e)) return;

			EntityId last = dense_entities[count - 1];

			// Move last element to the removed element's place.

			if (dense_entities[sparse[e.index]] == e) {
				dense_entities[sparse[e.index]] = dense_entities[count - 1];
				dense_components[sparse[e.index]] = dense_components[count - 1];

			}

			// 0, 1, 2
			// 1 removed
			// 

			sparse[e.index]
		}

		std::size_t size() const { return count; }

		void clear()
		{

		}

	private:
		std::array<T, kMaxEntities> dense_components;
		std::array<EntityId, kMaxEntities> dense_entities;
		std::array<std::int32_t, kMaxEntities> sparse;

		std::size_t count = 0;

		// dense_entities[denseIndex] = entity.
		// dense_components[denseIndex] = component.
		// sparse[entityIndex] = dense index (or invalid index if missing).
	};

	template<typename T>
	inline void SparseSet<T>::validate() const
	{
		ENGINE_ASSERT(count <= kMaxEntities);

		ENGINE_ASSERT(dense_entities.size() == dense_components.size());

		// Dense to Sparse
		for (std::size_t i = 0; i < count; i++)
		{
			ENGINE_ASSERT(dense_entities[i].index < kMaxEntities);

			EntityId e = dense_entities[i];

			ENGINE_ASSERT(sparse[e.index] == i);
			ENGINE_ASSERT(sparse[e.index] < count)

			// Assertion explanation example:
			// 
			// Dense components:
			// [T5][T2][T9]
			// 
			// Dense entities:
			// [E5][E2][E9]
			//
			// Sparse:
			//	- sparse[5] = 0
			//	- sparse[2] = 1
			//	- sparse[9] = 2
			//
			// Iterations:
			// 0 -> dense_entities[0] = E5 -> sparse[5] = 0
			// 1 -> dense_entities[1] = E2 -> sparse[2] = 1
			// 2 -> dense_entities[2] = E9 -> sparse[9] = 2
		}

		// Sparse to Dense
		for (std::size_t i = 0; i < kMaxEntities; i++)
		{
			if (sparse[i] == kInvalidIndex) continue;

			ENGINE_ASSERT(sparse[i] < count);
			ENGINE_ASSERT(dense_entities[sparse[i]].index == i)

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
			// 0 -> sparse[0] = 0 -> dense_entities[0] = E0 -> E0.index == 0
			// 1 -> sparse[1] = 1 -> dense_entities[1] = E1 -> E1.index == 1
			// 2 -> sparse[2] = 2 -> dense_entities[2] = E2 -> E2.index == 2
			// ...
		}
	}
}
