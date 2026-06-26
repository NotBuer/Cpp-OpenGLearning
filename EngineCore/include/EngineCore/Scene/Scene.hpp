#pragma once
#include <string>
#include "EngineCore/Scene/Containers/SparseSet.hpp"
#include "EngineCore/Scene/Components/Transform.hpp"
#include "EngineCore/Scene/Components/Sprite.hpp"
#include "EngineCore/Renderer/RenderView.hpp"
#include "EngineCore/Scene/Entities/EntityId.hpp"
#include "EngineCore/Scene/Entities/EntityManager.hpp"

namespace engine::scene
{
	class Scene
	{
	public:
		Scene(const std::string& name);

		void update(float dt);
		void buildRenderView(engine::renderer::RenderView& out) const;

		template<typename T>
		auto& registry()
		{
			if constexpr (std::is_same_v<T, engine::scene::components::Transform>)
			{
				return m_transforms;
			}
			else if constexpr (std::is_same_v<T, engine::scene::components::Sprite>)
			{
				return m_sprites;
			}
			else
			{
				// Since no objects can have a size of 0, it "throws" right on instantiation.
				static_assert(sizeof(T) == 0, "Unsupported component type requested from registry.");
			}
		}

		template<typename T>
		const auto& registry() const
		{
			if constexpr (std::is_same_v<T, engine::scene::components::Transform>)
			{
				return m_transforms;
			}
			else if constexpr (std::is_same_v<T, engine::scene::components::Sprite>)
			{
				return m_sprites;
			}
			else
			{
				// Since no objects can have a size of 0, it "throws" right on instantiation.
				static_assert(sizeof(T) == 0, "Unsupported component type requested from registry.");
			}
		}

		template<typename T>
		bool hasComponent(engine::scene::entities::EntityId id) const
		{
			if (!isAlive(id)) return false;
			return registry<T>().has(id);
		}

		template<typename T>
		T& getComponent(engine::scene::entities::EntityId id)
		{
			if (!isAlive(id))
				throw std::runtime_error("Cannot get component from a dead entity.");

			auto* component = registry<T>().tryGet(id);
			if (component == nullptr)
				throw std::runtime_error("Entity does not have the requested component.");

			return *component;
		}

		template<typename T>
		const T& getComponent(engine::scene::entities::EntityId id) const
		{
			if (!isAlive(id))
				throw std::runtime_error("Cannot get component from a dead entity.");

			auto* component = registry<T>().tryGet(id);
			if (component == nullptr)
				throw std::runtime_error("Entity does not have the requested component.");

			return *component;
		}

		template<typename T>
		T& addComponent(engine::scene::entities::EntityId id, const T& value)
		{
			if (!isAlive(id))
				throw std::runtime_error("Cannot add component to a dead entity.");

			return registry<T>().add(id, value);
		}

		template<typename T>
		void removeComponent(engine::scene::entities::EntityId id)
		{
			if (!isAlive(id))
				return;

			registry<T>().remove(id);
		}

		const std::string& getName() const noexcept { return m_name; }
		std::size_t entityCount() noexcept { return m_entityManager.aliveCount(); }

		engine::scene::entities::EntityId createEntity();
		void destroyEntity(engine::scene::entities::EntityId id);
		bool isAlive(engine::scene::entities::EntityId id) const;

	private:
		std::string m_name;

		engine::scene::entities::EntityManager m_entityManager;

		engine::scene::containers::SparseSet<engine::scene::components::Transform> m_transforms;
		engine::scene::containers::SparseSet<engine::scene::components::Sprite> m_sprites;
	};
}