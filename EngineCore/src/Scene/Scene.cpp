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

		std::uint16_t count = 0;

		for (const auto& transform : m_transforms.components()) {

			float x = transform.position.x, y = transform.position.y;

			out.quads.push_back(
				engine::renderer::QuadCommand{
					.min{transform.position.x, transform.position.y},
					.size{transform.scale.x, transform.scale.y},
					.color{1.f, 0.f, 0.f, 1.f} 
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

		m_entityManager.destroy(id);
	}

	bool Scene::isAlive(entities::EntityId id) const
	{
		return m_entityManager.isAlive(id);
	}
}