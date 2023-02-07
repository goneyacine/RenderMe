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
			inline Registry* getRegistry();
		private:
			Registry m_registry;
			ShaderManager m_shadersManager;

		};

	}
}