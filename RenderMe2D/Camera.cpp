#include "Camera.h"
#include "TexturesManager.h"
#include "SpriteRenderer.h"
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

	glClear(GL_COLOR_BUFFER_BIT);  //clearing the frame buffer 


	unsigned int vertexBuffer,indexBuffer;

	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);

	//float color_offset = (sizeof(float) * 2);
	//float texture_coordinate_offset = (sizeof(float) * 4);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	//color attrib
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, &color_offset);
	//texture coordinate attrib
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, &texture_coordinate_offset);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);


	//TODO : implement the render function
	//iterate through scene objects
	 //get sprite renderer and transform components
	  //do some calculations 
	  //do opengl stuff

	std::vector<RenderMe::Base::Entity> entities = m_scene->getEntities();


	float verticesData[8];
	unsigned int indicesData[6] = { 0, 1, 2, 2, 3, 0 };

	for (auto entity : entities)
	{
		TransformComponent* transform = m_scene->getComponent<TransformComponent>(entity);
		SpriteRenderer* spriteRenderer = m_scene->getComponent<SpriteRenderer>(entity);

		if (transform == nullptr || spriteRenderer == nullptr)
		continue;

		//applying rotation offsets 
		// TODO : implement camera rotation because object rotation is only what's implemented 
		  //top left vertex

		double cos_z_rotation = cos(transform->z_rotation * 3.14159265359f / 180);
		double sin_z_rotation = sin(transform->z_rotation * 3.14159265359f / 180);
		/*
		verticesData[0] = spriteRenderer->getVertices()[0] * cos_z_rotation - spriteRenderer->getVertices()[1] * sin_z_rotation;
		verticesData[1] = spriteRenderer->getVertices()[1] * cos_z_rotation + spriteRenderer->getVertices()[0] * sin_z_rotation;

		//buttom left vertex
		verticesData[8] = spriteRenderer->getVertices()[8] * cos_z_rotation - spriteRenderer->getVertices()[9] * sin_z_rotation;
		verticesData[9] = spriteRenderer->getVertices()[9] * cos_z_rotation + spriteRenderer->getVertices()[8] * sin_z_rotation;

		//buttom right vertex
		verticesData[16] = spriteRenderer->getVertices()[16] * cos_z_rotation - spriteRenderer->getVertices()[17] * sin_z_rotation;
		verticesData[17] = spriteRenderer->getVertices()[17] * cos_z_rotation + spriteRenderer->getVertices()[16] * sin_z_rotation;

		//top right vertex
		verticesData[24] = spriteRenderer->getVertices()[24] * cos_z_rotation - spriteRenderer->getVertices()[25] * sin_z_rotation;
		verticesData[25] = spriteRenderer->getVertices()[25] * cos_z_rotation + spriteRenderer->getVertices()[24] * sin_z_rotation;

		//applying position offsets 
		 //top left vertex
		verticesData[0] = verticesData[0] + transform->x_position - m_x;
		verticesData[1] = verticesData[1] + transform->y_position - m_y;
		//buttom left 	 
		verticesData[8] = verticesData[8] + transform->x_position - m_x;
		verticesData[9] = verticesData[9] + transform->y_position - m_y;
		//buttom right 	  
		verticesData[16] = verticesData[16] + transform->x_position - m_x;
		verticesData[17] = verticesData[17] + transform->y_position - m_y;
		//top right 	  
		verticesData[24] = verticesData[24] + transform->x_position - m_x;
		verticesData[25] = verticesData[25] + transform->y_position - m_y;



		*/

		verticesData[0] = (-0.5f) * cos_z_rotation - (-0.5f) * sin_z_rotation;
		verticesData[1] = (-0.5f) * cos_z_rotation + (-0.5f) * sin_z_rotation;

		//buttom left vertex
		verticesData[2] = 0.5f * cos_z_rotation - (-0.5f) * sin_z_rotation;
		verticesData[3] = (-0.5f) * cos_z_rotation + (0.5f) * sin_z_rotation;

		//buttom right vertex
		verticesData[4] = 0.5f * cos_z_rotation - 0.5f * sin_z_rotation;
		verticesData[5] = 0.5f * cos_z_rotation + 0.5f * sin_z_rotation;

		//top right vertex
		verticesData[6] = (- 0.5f)* cos_z_rotation - 0.5f * sin_z_rotation;
		verticesData[7] =  0.5f *  cos_z_rotation +  (- 0.5f) * sin_z_rotation;

		//applying position offsets 
		 //top left vertex
		verticesData[0] = verticesData[0] + transform->x_position - m_x;
		verticesData[1] = verticesData[1] + transform->y_position - m_y;
		//buttom left 	 
		verticesData[2] = verticesData[2] + transform->x_position - m_x;
		verticesData[3] = verticesData[3] + transform->y_position - m_y;
		//buttom right 	  
		verticesData[4] = verticesData[4] + transform->x_position - m_x;
		verticesData[5] = verticesData[5] + transform->y_position - m_y;
		//top right 	  
		verticesData[6] = verticesData[6] + transform->x_position - m_x;
		verticesData[7] = verticesData[7] + transform->y_position - m_y;



		verticesData[0] = verticesData[0] * transform->x_scale * spriteRenderer->getTexture().getWidth() / spriteRenderer->getPixelsPerUnit();
		verticesData[1] = verticesData[1] * transform->y_scale * spriteRenderer->getTexture().getHeight() / spriteRenderer->getPixelsPerUnit();

		verticesData[2] = verticesData[2] * transform->x_scale * spriteRenderer->getTexture().getWidth() / spriteRenderer->getPixelsPerUnit();
		verticesData[3] = verticesData[3] * transform->y_scale * spriteRenderer->getTexture().getHeight() / spriteRenderer->getPixelsPerUnit();

		verticesData[4] = verticesData[4] * transform->x_scale * spriteRenderer->getTexture().getWidth() / spriteRenderer->getPixelsPerUnit();
		verticesData[5] = verticesData[5] * transform->y_scale * spriteRenderer->getTexture().getHeight() / spriteRenderer->getPixelsPerUnit();
		
		verticesData[6] = verticesData[6] * transform->x_scale * spriteRenderer->getTexture().getWidth() / spriteRenderer->getPixelsPerUnit();
		verticesData[7] = verticesData[7] * transform->y_scale * spriteRenderer->getTexture().getHeight() / spriteRenderer->getPixelsPerUnit();


		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesData), indicesData, GL_DYNAMIC_DRAW);


		glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,0);

	}


	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbinding the vertex buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); //unbinding the index buffer


;
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);

}