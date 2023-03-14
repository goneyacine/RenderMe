
#include "glm.hpp"
#include "ext/matrix_clip_space.hpp"
#include "type_ptr.hpp"

#include "Camera.h"
#include "Vertex.h"
#include "ErrorHandler.h"
#include "MeshRenderer.h"

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
	if (m_vertexBuffer <= 0 || m_indexBuffer <= 0)
		initBuffers();

	GL_CALL(glClear(GL_COLOR_BUFFER_BIT))  //clearing the frame buffer 


		glm::mat4 projectionViewMatrix = glm::perspective(glm::radians(45.0f), g_aspectRatio.x / g_aspectRatio.y,1.0f, 100.0f);

	std::vector<RenderMe::Base::Entity> entities = m_scene->getEntities();
	//degrees to radians
	float deg2rad = 3.14159265359f / 180;

	for (auto entity : entities)
	{
		RenderMe::Base::TransformComponent* transform = m_scene->getComponent<RenderMe::Base::TransformComponent>(entity);
		MeshRenderer* meshRenderer = m_scene->getComponent<MeshRenderer>(entity);

		if (meshRenderer == nullptr || transform == nullptr)
			continue;
		//model view projection matrix
		glm::mat4 mvp = glm::mat4(1);
		
		//apply rotation around x axis
		mvp = glm::rotate(mvp, (transform->x_rotation - g_rotation.x) * deg2rad, glm::vec3(1, 0, 0));
		//apply rotation around y axis
		mvp = glm::rotate(mvp, (transform->y_rotation - g_rotation.y) * deg2rad, glm::vec3(0, 1, 0));
		//apply rotation around z axis
		mvp = glm::rotate(mvp, (transform->z_rotation - g_rotation.z) * deg2rad, glm::vec3(0, 0, 1));

		mvp = glm::translate(mvp,
			glm::vec3(transform->x_position - g_position.x, transform->y_position - g_position.y, transform->z_position - g_position.z));

		mvp = glm::scale(mvp, glm::vec3(transform->x_scale, transform->y_scale, transform->z_scale));


		
		GL_CALL(glUseProgram(meshRenderer->getShaderProgram()))
		GL_CALL(glUniform1i(glGetUniformLocation(meshRenderer->getShaderProgram(), "u_texture"), 0))
		GL_CALL(glBindTexture(GL_TEXTURE_2D, meshRenderer->g_texture.getOpenGL_ID()))
		GL_CALL(glUniformMatrix4fv(glGetUniformLocation(meshRenderer->getShaderProgram(), "u_projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionViewMatrix)))
		GL_CALL(glUniformMatrix4fv(glGetUniformLocation(meshRenderer->getShaderProgram(), "u_mvp"), 1, GL_FALSE, glm::value_ptr(mvp)))
		
		//set vertices data
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, meshRenderer->g_mesh.getVertices().size() * sizeof(Vertex),meshRenderer->g_mesh.getVertices().data(), GL_DYNAMIC_DRAW))
		//set indices data
		GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshRenderer->g_mesh.getIndices().size() * sizeof(Index),meshRenderer->g_mesh.getIndices().data(), GL_DYNAMIC_DRAW))
		GL_CALL(glDrawElements(GL_TRIANGLES, meshRenderer->g_mesh.getIndices().size(), GL_UNSIGNED_INT, 0))

	}
	glBindTexture(GL_TEXTURE_2D, 0);

}

	void Camera::initBuffers()
	{       

		//Enabling blending
		GL_CALL(glEnable(GL_BLEND))
		GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
		GL_CALL(glActiveTexture(GL_TEXTURE0))
		GL_CALL(glEnable(GL_TEXTURE_2D))
        
			//generate the index and vertex buffers
			GL_CALL(glGenBuffers(1, &m_vertexBuffer))
			GL_CALL(glGenBuffers(1, &m_indexBuffer))
			//binding index and vertex buffers



			GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer))
			//setting vertex attributes
			//setting position attrib
			GL_CALL(glEnableVertexAttribArray(0))
			GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)))
			//color attrib
			GL_CALL(glEnableVertexAttribArray(1))
			GL_CALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color)))
			//texture coordinate attrib
			GL_CALL(glEnableVertexAttribArray(2))
			GL_CALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv)))
			GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer))


	}

void Camera::deleteBuffers()
{
	    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0)) //unbinding the vertex buffer
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)) //unbinding the index buffer
		GL_CALL(glDeleteBuffers(1, &m_vertexBuffer))
		GL_CALL(glDeleteBuffers(1, &m_indexBuffer))
}