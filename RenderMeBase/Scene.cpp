#include "Scene.h"


Scene::Scene()
{

}

Scene::~Scene()
{
	//when the scene is destroyed we should call the registry clear function to remove all the entities and components pools
	//forgeting this will lead to memory leaks
	m_registry.clear();
}


Registry* Scene::getRegistry()
{
	return &m_registry;
}