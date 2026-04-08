#include "pch.h"
#include <iostream>
#include "EngineCore/Scene/Scene.hpp"

namespace entities = engine::scene::entities;
namespace components = engine::scene::components;

namespace engine::scene
{
	Scene::Scene(const std::string& name) : 
		m_name{ name }
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
}