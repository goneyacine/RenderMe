#include "glm.hpp"
#include "ext/matrix_clip_space.hpp"


#include "Camera.h"
#include "TexturesManager.h"
#include "SpriteRenderer.h"
#include "type_ptr.hpp"
#include "ErrorHandler.h"
#include "Vertex.h"
#include "LineRenderer.h"


using namespace RenderMe::RenderMe2D;
using namespace RenderMe::Base;


Camera::Camera() :
	m_scene(nullptr)
{

}
Camera::Camera(RenderMe::Base::Scene* p_scene) :
	m_scene(p_scene)
{

}
Camera::Camera(RenderMe::Base::Scene* p_scene, float p_x, float p_y) :
	m_scene(p_scene),g_x(p_x),g_y(p_y)
{

}
Camera::Camera(RenderMe::Base::Scene* p_scene, float p_x, float p_y, float p_angle) 
	: m_scene(p_scene),g_x(p_x),g_y(p_y),g_angle(p_angle)
{

}
Camera::Camera(RenderMe::Base::Scene* p_scene, float  p_aspectRatioX, float p_aspectRatioY, float p_x, float p_y, float p_angle)
	: m_scene(p_scene),g_aspectRatioX(p_aspectRatioX),g_aspectRatioY(p_aspectRatioY), g_x(p_x), g_y(p_y), g_angle(p_angle)
{

}
Camera::Camera(RenderMe::Base::Scene* p_scene, float p_aspectRatioX, float p_aspectRatioY, float p_orthographicSize, float p_x, float p_y, float p_angle)
	: m_scene(p_scene), g_aspectRatioX(p_aspectRatioX), g_aspectRatioY(p_aspectRatioY),g_orthographicSize(p_orthographicSize), g_x(p_x), g_y(p_y), g_angle(p_angle)
{

}
Camera::~Camera()
{
	deleteBuffers();
}

void Camera::render()
{
	if (m_scene == nullptr)
		return;

	if (m_indexBuffer <= 0 || m_vertexBuffer <= 0)
		initBuffers();



	GL_CALL(glClear(GL_COLOR_BUFFER_BIT))  //clearing the frame buffer 

	std::vector<RenderMe::Base::Entity> entities = m_scene->getEntities();



	float cam_x_size = g_orthographicSize; //* g_aspectRatioX / std::max(g_aspectRatioX, g_aspectRatioY);
	float cam_y_size = g_orthographicSize; //* g_aspectRatioY / std::max(g_aspectRatioX, g_aspectRatioY);

	glm::mat4 projectionMatrix = glm::ortho(-cam_x_size / 2, cam_x_size / 2, -cam_y_size / 2, cam_y_size / 2);


	for (auto entity : entities)
	{

		TransformComponent* transform = m_scene->getComponent<TransformComponent>(entity);
		SpriteRenderer* spriteRenderer = m_scene->getComponent<SpriteRenderer>(entity);
		LineRenderer* lineRenderer = m_scene->getComponent<LineRenderer>(entity);

		if ((lineRenderer == nullptr && spriteRenderer == nullptr) || transform == nullptr)
			continue;



		Vertex vertices[4] = {
			  {
				 {-0.5f,0.5f},
				 {spriteRenderer->m_color[0],spriteRenderer->m_color[1],spriteRenderer->m_color[2],spriteRenderer->m_color[3]},
				 {0,1}
			  },
			  {
				 {-0.5f,-0.5f},
				 {spriteRenderer->m_color[0],spriteRenderer->m_color[1],spriteRenderer->m_color[2],spriteRenderer->m_color[3]},
				 {0,0}
			  },
			  {
				 {0.5f,-0.5f},
				 {spriteRenderer->m_color[0],spriteRenderer->m_color[1],spriteRenderer->m_color[2],spriteRenderer->m_color[3]},
				 {1,0}
			  },
			  {
				 {0.5f,0.5f},
				 {spriteRenderer->m_color[0],spriteRenderer->m_color[1],spriteRenderer->m_color[2],spriteRenderer->m_color[3]},
				 {1,1}
			  }
		};

		//model view projection matrix
		glm::mat4 mvp = glm::mat4(1);

		mvp = glm::rotate(mvp, (transform->z_rotation - g_angle) * 3.14159265359f / 180, glm::vec3(0, 0, 1));

		mvp = glm::translate(mvp, glm::vec3(transform->x_position - g_x, transform->y_position - g_y, 1));

		mvp = glm::scale(mvp,
			glm::vec3(
				transform->x_scale * (float)spriteRenderer->getTexture().getWidth() / spriteRenderer->g_PPU,
				transform->y_scale * (float)spriteRenderer->getTexture().getHeight() / spriteRenderer->g_PPU,
				1)
		);

		if (spriteRenderer != nullptr)
		{
			GL_CALL(glUseProgram(spriteRenderer->getShaderProgram()))
		    GL_CALL(glUniform1i(glGetUniformLocation(spriteRenderer->getShaderProgram(), "u_texture"), 0))
		    GL_CALL(glBindTexture(GL_TEXTURE_2D, spriteRenderer->getTexture().getOpenGL_ID()))
		    GL_CALL(glUniformMatrix4fv(glGetUniformLocation(spriteRenderer->getShaderProgram(), "u_projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix)))
		    GL_CALL(glUniformMatrix4fv(glGetUniformLocation(spriteRenderer->getShaderProgram(), "u_mvp"), 1, GL_FALSE, glm::value_ptr(mvp)))
		    
		    
		    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW))
				unsigned int indicesData[6] = { 0, 1, 2, 2, 3, 0 };
			GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesData), indicesData, GL_DYNAMIC_DRAW))
		    GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0))

		}

		if (lineRenderer != nullptr)
		{
			GL_CALL(glUseProgram(lineRenderer->getShaderProgram()))
		    //GL_CALL(glUniform1i(glGetUniformLocation(lineRenderer->getShaderProgram(), "u_texture"), 0))
		    //GL_CALL(glBindTexture(GL_TEXTURE_2D, lineRenderer->g_texture.getOpenGL_ID()))
		    GL_CALL(glUniformMatrix4fv(glGetUniformLocation(lineRenderer->getShaderProgram(), "u_projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix)))
		    GL_CALL(glUniformMatrix4fv(glGetUniformLocation(lineRenderer->getShaderProgram(), "u_mvp"), 1, GL_FALSE, glm::value_ptr(mvp)))
		    
		    //set vertices data
		    GL_CALL(glBufferData(GL_ARRAY_BUFFER, lineRenderer->getVertices().size() * sizeof(Vertex), lineRenderer->getVertices().data(), GL_DYNAMIC_DRAW))
		    //set indices data
		    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, lineRenderer->getIndices().size() * sizeof(Index), lineRenderer->getIndices().data(), GL_DYNAMIC_DRAW))
		    GL_CALL(glDrawElements(GL_TRIANGLES, lineRenderer->getIndices().size(), GL_UNSIGNED_INT, 0))
		}
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

		
	    GL_CALL(glGenBuffers(1, &m_vertexBuffer))
		GL_CALL(glGenBuffers(1, &m_indexBuffer))

	    

		//setting vertex attributes
	    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer))
		//setting position attrib
		GL_CALL(glEnableVertexAttribArray(0))
		GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,position)))
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
