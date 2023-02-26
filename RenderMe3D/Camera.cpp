#include "Camera.h"


using namespace RenderMe::RenderMe3D;


Camera::Camera() :
	m_scene(nullptr),g_position({0,0,0}),g_rotation({0,0,0})
{

}

Camera::Camera(RenderMe::Base::Scene* p_scene, RenderMe::Base::Vector3 p_position)
	: m_scene(p_scene),g_position(p_position),g_rotation({0,0,0})
{
}

Camera::Camera(RenderMe::Base::Scene* p_scene, RenderMe::Base::Vector3 p_position, RenderMe::Base::Vector3 p_rotation)
	: m_scene(p_scene), g_position(p_position), g_rotation(p_rotation)
{
}

Camera::~Camera()
{
	//deleting index and vertex and index buffers
	deleteBuffers();
}


void Camera::render()
{
	if (m_scene == nullptr)
		return;

	//initializing vertex and index buffers
	if (m_vertexBuffer == 0 || m_indexBuffer == 0)
		initBuffers();

}

void Camera::initBuffers()
{

}

void Camera::deleteBuffers()
{

}