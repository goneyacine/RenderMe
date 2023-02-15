#include "Scene.h"


using namespace RenderMe::Base;

Scene::Scene()
{
	m_shadersManager = ShaderManager();
}

Scene::~Scene()
{
	//when the scene is destroyed we should call the registry clear function to remove all the entities and components pools
	//forgeting this will lead to memory leaks
	m_registry.clear();
}

Entity Scene::addEntity()
{
    Entity entity = m_registry.create();
	m_entities.push_back(entity);
	return entity;
}

void Scene::removeEntity(Entity p_entity)
{
	m_registry.destroy(p_entity);
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities[i] == p_entity)
		{
			m_entities.erase(m_entities.begin() + i);
			break;
		}
	}
}

ShaderManager* RenderMe::Base::Scene::getShadersManager() 
{
	return &m_shadersManager;
}


 std::vector<Entity> Scene::getEntities() const
{
	return m_entities;
}
