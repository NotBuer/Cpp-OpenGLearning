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

		for (const auto& transform : m_transforms.components()) {
			
		}
	}

	entities::EntityId Scene::createEntity()
	{
		return m_entityManager.create();
	}

	void Scene::destroy(entities::EntityId id)
	{
		m_entityManager.destroy(id);

		// TODO: This is an intended tech debt.
		// Leaving the removal of components "manually" for now.
		// Later on will implement a better way to do it as the components grows.
		removeComponent<components::Transform>(id);
	}

	bool Scene::isAlive(entities::EntityId id) const
	{
		return m_entityManager.isAlive(id);
	}
}