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
			float w = transform.scale.x, h = transform.scale.y;

			out.quads.push_back(engine::renderer::QuadVertex{ .pos{x,	  y,	 0.f}, .color{0.f, 0.f, 0.f, 1.f}, .uv{0.f, 0.f} });
			out.quads.push_back(engine::renderer::QuadVertex{ .pos{x + w, y,	 0.f}, .color{0.f, 0.f, 0.f, 1.f}, .uv{1.f, 0.f} });
			out.quads.push_back(engine::renderer::QuadVertex{ .pos{x + w, y + h, 0.f}, .color{0.f, 0.f, 0.f, 1.f}, .uv{1.f, 1.f} });
			out.quads.push_back(engine::renderer::QuadVertex{ .pos{x,	  y + h, 0.f}, .color{0.f, 0.f, 0.f, 1.f}, .uv{0.f, 1.f} });
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