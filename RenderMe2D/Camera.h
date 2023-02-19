#pragma once

#include "Scene.h"

namespace RenderMe
{
	namespace RenderMe2D
	{
		class Camera
		{
		public :
			Camera();
			Camera(RenderMe::Base::Scene* p_scene);
			Camera(RenderMe::Base::Scene* p_scene, float p_x = 0, float p_y = 0);
			Camera(RenderMe::Base::Scene* p_scene, float p_x = 0, float p_y = 0,float p_angle = 0);
			Camera(RenderMe::Base::Scene* p_scene, float  p_aspectRatioX = 16,float p_aspectRatioY = 9,float p_x = 0, float p_y = 0,float p_angle = 0);
			Camera(RenderMe::Base::Scene* p_scene, float p_aspectRatioX = 16, float p_aspectRatioY = 9,float p_orthographicSize = 10,float p_x = 0, float p_y = 0,float p_angle = 0);
			~Camera();
			void render();


			float g_x = 0;
			float g_y = 0;
			float g_angle = 0;

			float g_aspectRatioX = 16;
			float g_aspectRatioY = 9;
			float g_orthographicSize = 10;
		private :
			void initBuffers();
			void deleteBuffers();

			unsigned int m_vertexBuffer, m_indexBuffer;
			RenderMe::Base::Scene* m_scene = nullptr;
		};
	}
}
