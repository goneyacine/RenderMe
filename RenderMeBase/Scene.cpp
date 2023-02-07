#include "Scene.h"


using namespace RenderMe::Base;

Scene::Scene()
{

}

Scene::~Scene()
{
	//when the scene is destroyed we should call the registry clear function to remove all the entities and components pools
	//forgeting this will lead to memory leaks
	m_registry.clear();
}


inline Registry* Scene::getRegistry()
{
	return &m_registry;
}