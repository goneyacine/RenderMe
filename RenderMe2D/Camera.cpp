#include "glm.hpp"
#include "ext/matrix_clip_space.hpp"


#include "Camera.h"
#include "TexturesManager.h"
#include "SpriteRenderer.h"
#include "type_ptr.hpp"
#include "ErrorHandler.h"
#include "Vertex.h"

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
	glm::mat4 projectionMatrix = glm::ortho(-1,1,-1,1);


	for (auto entity : entities)
	{

		TransformComponent* transform = m_scene->getComponent<TransformComponent>(entity);
		SpriteRenderer* spriteRenderer = m_scene->getComponent<SpriteRenderer>(entity);

		for (int i = 0; i < spriteRenderer->getVertices().size(); i++)
			vertices[i] = spriteRenderer->getVertices()[i];

		if (transform == nullptr || spriteRenderer == nullptr)
			continue;

		//TODO : have some kind of default shader for sprite renderers that does not have attached shaders
		GL_CALL(glUseProgram(spriteRenderer->getShaderProgram()))


			//sending projection view matrix data to the gpu -------------------------------
			GL_CALL(glUniformMatrix4fv(glGetUniformLocation(spriteRenderer->getShaderProgram(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix)))

			//iterating through all the uniforms data in the sprite renderer and pass it to the gpu ----------------

			/*
			//uniform1f
			for (auto uniform : spriteRenderer->g_uniforms_1f)
				glUniform1f(glGetUniformLocation(spriteRenderer->getShaderProgram(), uniform.name.c_str()), uniform.value1);
			//uniform2f
			for (auto uniform : spriteRenderer->g_uniforms_2f)
				glUniform2f(glGetUniformLocation(spriteRenderer->getShaderProgram(), uniform.name.c_str()), uniform.value1, uniform.value2);

			//uniform3f
			for (auto uniform : spriteRenderer->g_uniforms_3f)
				glUniform3f(glGetUniformLocation(spriteRenderer->getShaderProgram(), uniform.name.c_str()), uniform.value1, uniform.value2,uniform.value3);

			//uniform4f
			for (auto uniform : spriteRenderer->g_uniforms_4f)
				glUniform4f(glGetUniformLocation(spriteRenderer->getShaderProgram(), uniform.name.c_str()), uniform.value1, uniform.value2,uniform.value3,uniform.value4);


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
			*/





			//applying rotation offsets 
			// TODO : implement camera rotation because object rotation is only what's implemented 
			  //top left vertex



			double cos_z_rotation = cos(transform->z_rotation * 3.14159265359f / 180);
		    double sin_z_rotation = sin(transform->z_rotation * 3.14159265359f / 180);


		//vertices[0].position[0] = spriteRenderer->getVertices()[0].position[0] * cos_z_rotation - spriteRenderer->getVertices()[0].position[1] * sin_z_rotation;
		//vertices[0].position[1] = spriteRenderer->getVertices()[0].position[1] * cos_z_rotation + spriteRenderer->getVertices()[0].position[0] * sin_z_rotation;
		/*
		//buttom left vertex
		vertices[1].position[0] = spriteRenderer->getVertices()[1].position[0] * cos_z_rotation + spriteRenderer->getVertices()[1].position[1] * sin_z_rotation;
		vertices[1].position[1] = spriteRenderer->getVertices()[1].position[1] * cos_z_rotation - spriteRenderer->getVertices()[1].position[0] * sin_z_rotation;

		//buttom right vertex
		vertices[2].position[0] = spriteRenderer->getVertices()[2].position[0] * cos_z_rotation - spriteRenderer->getVertices()[2].position[1] * sin_z_rotation;
		vertices[2].position[1] = spriteRenderer->getVertices()[2].position[1] * cos_z_rotation + spriteRenderer->getVertices()[2].position[0] * sin_z_rotation;

		//top right vertex
		vertices[3].position[0] = spriteRenderer->getVertices()[3].position[0] * cos_z_rotation - spriteRenderer->getVertices()[3].position[1] * sin_z_rotation;
		vertices[3].position[1] = spriteRenderer->getVertices()[3].position[1] * cos_z_rotation + spriteRenderer->getVertices()[3].position[0] * sin_z_rotation;
		*/
		//applying position offsets 
		 //top left vertex
		vertices[0].position[0] = vertices[0].position[0] + transform->x_position - m_x;
		vertices[0].position[1] = vertices[0].position[1] + transform->y_position - m_y;
		//buttom left 	 
		vertices[1].position[0] = vertices[1].position[0] + transform->x_position - m_x;
		vertices[1].position[1] = vertices[1].position[1] + transform->y_position - m_y;
		//buttom right 	  
		vertices[2].position[0] = vertices[2].position[0] + transform->x_position - m_x;
		vertices[2].position[1] = vertices[2].position[1] + transform->y_position - m_y;
		//top right 	  
		vertices[3].position[0] = vertices[3].position[0] + transform->x_position - m_x;
		vertices[3].position[1] = vertices[3].position[1] + transform->y_position - m_y;


		GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW))
			GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesData), indicesData, GL_DYNAMIC_DRAW))


			GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0))

	}


	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0)) //unbinding the vertex buffer
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)) //unbinding the index buffer


		GL_CALL(glDeleteBuffers(1, &vertexBuffer))
		GL_CALL(glDeleteBuffers(1, &indexBuffer))

}
