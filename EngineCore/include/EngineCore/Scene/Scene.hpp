#pragma once
#include <string>
#include "EngineCore/Scene/Containers/SparseSet.hpp"
#include "EngineCore/Scene/Components/Transform.hpp"
#include "EngineCore/Renderer/RenderView.hpp"
#include "EngineCore/Scene/Entities/EntityId.hpp"

namespace entities = engine::scene::entities;
namespace components = engine::scene::components;

namespace engine::scene
{
	class Scene
	{
	public:
		Scene(const std::string& name);

		void update(float dt);
		void buildRenderView(engine::renderer::RenderView& out) const;

		template<typename T>
		decltype(auto) registry()
		{
			if constexpr (std::is_same_v<T, components::Transform>)
			{
				return m_transforms;
			}
			else
			{
				// Since no objects can have a size of 0, it "throws" right on instantiation.
				static_assert(sizeof(T) == 0, "Unsupported component type requested from registry.");
			}
		}

		template<typename T>
		decltype(auto) registry() const
		{
			if constexpr (std::is_same_v<T, components::Transform>)
			{
				return m_transforms;
			}
			else
			{
				// Since no objects can have a size of 0, it "throws" right on instantiation.
				static_assert(sizeof(T) == 0, "Unsupported component type requested from registry.");
			}
		}

		template<typename T>
		bool hasComponent(entities::EntityId id) const
		{
			return registry<T>().has(id);
		}

		template<typename T>
		T& getComponent(entities::EntityId id)
		{
			auto* component = registry<T>().tryGet(id);

			if (component == nullptr)
				throw std::runtime_error("Entity does not have the requested component.");

			return *component;
		}

		template<typename T>
		const T& getComponent(entities::EntityId id) const
		{
			auto* component = registry<T>().tryGet(id);

			if (component == nullptr)
				throw std::runtime_error("Entity does not have the requested component.");

			return *component;
		}

		template<typename T>
		T& addComponent(entities::EntityId id, const T& value)
		{
			return registry<T>().add(id, value);
		}

		template<typename T>
		void removeComponent(entities::EntityId id)
		{
			registry<T>().remove(id);
		}

		const std::string& getName() const { return m_name; }

	private:
		std::string m_name;

		engine::scene::containers::SparseSet<components::Transform> m_transforms;
	};
}