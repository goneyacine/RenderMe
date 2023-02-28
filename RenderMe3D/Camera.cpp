#include "Camera.h"
#include "Vertex.h"
#include "ErrorHandler.h"

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

	//create projection view matrix
	//
}

void Camera::initBuffers()
{       
	    //enabling blending
	    GL_CALL(glEnable(GL_BLEND))
		GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
		//enabling 2d texutures
		GL_CALL(glActiveTexture(GL_TEXTURE0))
		GL_CALL(glEnable(GL_TEXTURE_2D))

		//generate the index and vertex buffers
		GL_CALL(glGenBuffers(1, &m_vertexBuffer))
		GL_CALL(glGenBuffers(1, &m_indexBuffer))
		//binding index and vertex buffers
	    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer))
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer))


	    //setting vertex attributes
		//setting position attrib
		GL_CALL(glEnableVertexAttribArray(0))
		GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(RenderMe::RenderMe3D::Vertex), (void*)offsetof(RenderMe::RenderMe3D::Vertex, position)))
		//color attrib
		GL_CALL(glEnableVertexAttribArray(1))
		GL_CALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(RenderMe::RenderMe3D::Vertex), (void*)offsetof(RenderMe::RenderMe3D::Vertex, color)))
		//texture coordinate attrib
		GL_CALL(glEnableVertexAttribArray(2))
		GL_CALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(RenderMe::RenderMe3D::Vertex), (void*)offsetof(RenderMe::RenderMe3D::Vertex, uv)))


}

void Camera::deleteBuffers()
{
	    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0)) //unbinding the vertex buffer
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)) //unbinding the index buffer
		GL_CALL(glDeleteBuffers(1, &m_vertexBuffer))
		GL_CALL(glDeleteBuffers(1, &m_indexBuffer))
}