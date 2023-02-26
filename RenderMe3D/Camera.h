#pragma once

#include "Scene.h"
#include "Vectors.h"

namespace RenderMe
{
	namespace RenderMe3D
	{
		class Camera
		{
		public :
			Camera();
			Camera(RenderMe::Base::Scene* p_scene);
			Camera(RenderMe::Base::Scene* p_scene, RenderMe::Base::Vector3 p_position);
			Camera(RenderMe::Base::Scene* p_scene, RenderMe::Base::Vector3 P_position, RenderMe::Base::Vector3 p_rotation);
			~Camera();


			void render();


			RenderMe::Base::Vector3 g_position;
			RenderMe::Base::Vector3 g_rotation;
		private:
			void initBuffers();
			void deleteBuffers();

			RenderMe::Base::Scene* m_scene;
			unsigned int m_vertexBuffer, m_indexBuffer;
		};
	}
}
