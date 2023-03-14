#pragma once
#include <iostream>
#include <entt.hpp>
#include "Entity.h"
#include "ShadersManager.h"

namespace RenderMe
{

	namespace Base
	{

		typedef entt::basic_registry<std::uint32_t> Registry;

		//the registry that stores entities stores them by 32 bit unsigned integer ids
		//so an entity is just 32 bit unsigend integer that represents the entity id in the registry
		// this means that the scene can store maximum of 4,294,967,295 entities 
		class Scene
		{
		public:
			Scene();
			~Scene();
		
			Entity addEntity();
			void removeEntity(Entity p_entity);
			ShaderManager* getShadersManager();
			std::vector<Entity> getEntities() const;
			template<typename T> T* getComponent(Entity p_entity);
			//NOTE : if entity already has that component it will replace it with the new one
			template<typename T> void addComponent(Entity p_entity, T& p_component);
		private:
			Registry m_registry;
			std::vector<Entity> m_entities;
			ShaderManager m_shadersManager;

		};

		template<typename T>
		inline T* Scene::getComponent(Entity p_entity)
		{
			if (m_registry.all_of<T>(p_entity))
			{
				return &m_registry.get<T>(p_entity);
			}
			else
			{
				return nullptr;
			}
		}

		template<typename T>
		inline void Scene::addComponent(Entity p_entity, T& p_component)
		{
		 m_registry.emplace_or_replace<T>(p_entity);
		 *getComponent<T>(p_entity) = p_component;

		}

	}
}