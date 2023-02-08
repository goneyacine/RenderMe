#include "Camera.h"


using namespace RenderMe::RenderMe2D;


Camera::Camera()
{

}
Camera::Camera(RenderMe::Base::Scene* p_scene) :
	m_scene(p_scene)
{

}
Camera::Camera(RenderMe::Base::Scene* p_scene, float p_x, float p_y) :
	m_scene(p_scene),m_x(p_x),m_y(p_y)
{

}
Camera::Camera(RenderMe::Base::Scene* p_scene, float p_x, float p_y, float p_angle) 
	: m_scene(p_scene),m_x(p_x),m_y(p_y),m_angle(p_angle)
{

}
Camera::Camera(RenderMe::Base::Scene* p_scene, float  p_aspectRatioX, float p_aspectRatioY, float p_x, float p_y, float p_angle)
	: m_scene(p_scene),m_aspectRatioX(p_aspectRatioX),m_aspectRatioY(p_aspectRatioY), m_x(p_x), m_y(p_y), m_angle(p_angle)
{

}
Camera::Camera(RenderMe::Base::Scene* p_scene, float p_aspectRatioX, float p_aspectRatioY, float p_orthographicSize, float p_x, float p_y, float p_angle)
	: m_scene(p_scene), m_aspectRatioX(p_aspectRatioX), m_aspectRatioY(p_aspectRatioY),m_orthographicSize(p_orthographicSize), m_x(p_x), m_y(p_y), m_angle(p_angle)
{

}
Camera::~Camera()
{

}