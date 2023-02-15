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
		private :
			float m_x = 0;
			float m_y = 0;
			float m_angle = 0;

			float m_aspectRatioX = 16;
			float m_aspectRatioY = 9;
			float m_orthographicSize = 10;

			RenderMe::Base::Scene* m_scene = nullptr;
		};
	}
}
