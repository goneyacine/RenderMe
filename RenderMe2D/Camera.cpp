#include "glm.hpp"
#include "ext/matrix_clip_space.hpp"


#include "Camera.h"
#include "TexturesManager.h"
#include "SpriteRenderer.h"
#include "type_ptr.hpp"
#include "ErrorHandler.h"
#include "Vertex.h"

#define DEG_TO_RAD(x) x * 3.14159265359f / 180

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

void Camera::render()
{
	if (m_scene == nullptr)
		return;

	GL_CALL(glClear(GL_COLOR_BUFFER_BIT))  //clearing the frame buffer 
		//Enabling blending
		GL_CALL(glEnable(GL_BLEND))
		GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))

		unsigned int vertexBuffer, indexBuffer;

	GL_CALL(glGenBuffers(1, &vertexBuffer))
		GL_CALL(glGenBuffers(1, &indexBuffer))

		Vertex vertices[4];
	unsigned int indicesData[6] = { 0, 1, 2, 2, 3, 0 };

	float color_offset = (sizeof(float) * 2);
	float texture_coordinate_offset = (sizeof(float) * 4);

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer))
		GL_CALL(glEnableVertexAttribArray(0))
		GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0))
		//color attrib
		GL_CALL(glEnableVertexAttribArray(1))
		GL_CALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color)))
		//texture coordinate attrib
		GL_CALL(glEnableVertexAttribArray(2))
		GL_CALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv)))

		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer))


		//TODO : implement the render function
		//iterate through scene objects
		 //get sprite renderer and transform components
		  //do some calculations 
		  //do opengl stuff

		std::vector<RenderMe::Base::Entity> entities = m_scene->getEntities();




	//computing projection view matrix here ------------------------------------
	float cam_x_size = m_orthographicSize * m_aspectRatioX / std::max(m_aspectRatioX, m_aspectRatioY);
	float cam_y_size = m_orthographicSize * m_aspectRatioY / std::max(m_aspectRatioX, m_aspectRatioY);

	glm::mat4 projectionMatrix = glm::ortho(-cam_x_size / 2, cam_x_size / 2, -cam_y_size / 2, cam_y_size / 2);


	for (auto entity : entities)
	{

		TransformComponent* transform = m_scene->getComponent<TransformComponent>(entity);
		SpriteRenderer* spriteRenderer = m_scene->getComponent<SpriteRenderer>(entity);

		//model view projection matrix
		glm::mat4 mvp = glm::mat4(1);
		mvp = glm::translate(mvp, glm::vec3(transform->x_position - m_x, transform->y_position - m_y, 1));
		mvp = glm::rotate(mvp, DEG_TO_RAD(transform->z_rotation - m_angle), glm::vec3(0, 0, 1));
		mvp = glm::scale(mvp, glm::vec3(transform->x_scale, transform->y_scale, 1));

		for (int i = 0; i < spriteRenderer->getVertices().size(); i++)
			vertices[i] = spriteRenderer->getVertices()[i];

		if (transform == nullptr || spriteRenderer == nullptr)
			continue;

		//TODO : have some kind of default shader for sprite renderers that does not have attached shaders
		GL_CALL(glUseProgram(spriteRenderer->getShaderProgram()))


			//sending projection view matrix data to the gpu -------------------------------
			GL_CALL(glUniformMatrix4fv(glGetUniformLocation(spriteRenderer->getShaderProgram(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix)))
			GL_CALL(glUniformMatrix4fv(glGetUniformLocation(spriteRenderer->getShaderProgram(), "mvp"), 1, GL_FALSE, glm::value_ptr(mvp)))

			//iterating through all the uniforms data in the sprite renderer and pass it to the gpu ----------------


			//uniform1f
			for (auto uniform : spriteRenderer->g_uniforms_1f)
				glUniform1f(glGetUniformLocation(spriteRenderer->getShaderProgram(), uniform.name.c_str()), uniform.value1);
		//uniform2f
		for (auto uniform : spriteRenderer->g_uniforms_2f)
			glUniform2f(glGetUniformLocation(spriteRenderer->getShaderProgram(), uniform.name.c_str()), uniform.value1, uniform.value2);

		//uniform3f
		for (auto uniform : spriteRenderer->g_uniforms_3f)
			glUniform3f(glGetUniformLocation(spriteRenderer->getShaderProgram(), uniform.name.c_str()), uniform.value1, uniform.value2, uniform.value3);

		//uniform4f
		for (auto uniform : spriteRenderer->g_uniforms_4f)
			glUniform4f(glGetUniformLocation(spriteRenderer->getShaderProgram(), uniform.name.c_str()), uniform.value1, uniform.value2, uniform.value3, uniform.value4);


		//uniform1i
		for (auto uniform : spriteRenderer->g_uniforms_1i)
			glUniform1i(glGetUniformLocation(spriteRenderer->getShaderProgram(), uniform.name.c_str()), uniform.value1);

		//uniform2i
		for (auto uniform : spriteRenderer->g_uniforms_2i)
			glUniform2i(glGetUniformLocation(spriteRenderer->getShaderProgram(), uniform.name.c_str()), uniform.value1, uniform.value2);
		//uniform3i
		for (auto uniform : spriteRenderer->g_uniforms_3i)
			glUniform3i(glGetUniformLocation(spriteRenderer->getShaderProgram(), uniform.name.c_str()), uniform.value1, uniform.value2, uniform.value3);
		//uniform4i
		for (auto uniform : spriteRenderer->g_uniforms_4i)
			glUniform4i(glGetUniformLocation(spriteRenderer->getShaderProgram(), uniform.name.c_str()), uniform.value1, uniform.value2, uniform.value3, uniform.value4);



		//uniform1ui
		for (auto uniform : spriteRenderer->g_uniforms_1ui)
			glUniform1ui(glGetUniformLocation(spriteRenderer->getShaderProgram(), uniform.name.c_str()), uniform.value1);

		//uniform2ui
		for (auto uniform : spriteRenderer->g_uniforms_2ui)
			glUniform2ui(glGetUniformLocation(spriteRenderer->getShaderProgram(), uniform.name.c_str()), uniform.value1, uniform.value2);

		//uniform3ui
		for (auto uniform : spriteRenderer->g_uniforms_3ui)
			glUniform3ui(glGetUniformLocation(spriteRenderer->getShaderProgram(), uniform.name.c_str()), uniform.value1, uniform.value2, uniform.value3);

		//uniform4ui
		for (auto uniform : spriteRenderer->g_uniforms_4ui)
			glUniform4ui(glGetUniformLocation(spriteRenderer->getShaderProgram(), uniform.name.c_str()), uniform.value1, uniform.value2, uniform.value3, uniform.value4);


		GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW))
			GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesData), indicesData, GL_DYNAMIC_DRAW))


			GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0))

	}


	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0)) //unbinding the vertex buffer
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)) //unbinding the index buffer


		GL_CALL(glDeleteBuffers(1, &vertexBuffer))
		GL_CALL(glDeleteBuffers(1, &indexBuffer))

}
