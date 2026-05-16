#include "pch.h"
#include <iostream>
#include "EngineCore/Scene/Scene.hpp"

namespace entities = engine::scene::entities;
namespace components = engine::scene::components;

namespace engine::scene
{
	Scene::Scene(const std::string& name) : 
		m_name{ name },
		m_entityManager{}
	{
		std::cout << "Scene '" << m_name << "' created.\n";
	}

	void Scene::update(float dt)
	{

	}

	void Scene::buildRenderView(engine::renderer::RenderView& out) const
	{
		out.clear();

		for (const auto& spriteEntity : m_sprites.entities())
		{
			const auto& transform = m_transforms.tryGet(spriteEntity);

			if (transform == nullptr) continue;

			const auto& spriteComponent = m_sprites.tryGet(spriteEntity);

			out.quads.push_back(
				engine::renderer::QuadCommand{
					.min{transform->position.x, transform->position.y},
					.size{transform->scale.x, transform->scale.y},
					.textureHandle{spriteComponent->textureHandle},
					.color{spriteComponent->color}
				}
			);
		}
	}

	entities::EntityId Scene::createEntity()
	{
		return m_entityManager.create();
	}

	void Scene::destroyEntity(entities::EntityId id)
	{
		if (!isAlive(id))
			return;

		// TODO: This is an intended tech debt.
		// Leaving the removal of components "manually" for now.
		// Later on will implement a better way to do it as the engine components count grows.
		removeComponent<components::Transform>(id);
		removeComponent<components::Sprite>(id);

		m_entityManager.destroy(id);
	}

	bool Scene::isAlive(entities::EntityId id) const
	{
		return m_entityManager.isAlive(id);
	}
}