#include "SpriteRenderer.h"
#include "GL/glew.h"
#include "ErrorHandler.h"
using namespace RenderMe::RenderMe2D;




SpriteRenderer::SpriteRenderer()
{

}

SpriteRenderer::SpriteRenderer(RenderMe::Base::Texture p_texture, unsigned int p_vertexShaderID, unsigned int p_fragmentShaderID)
	: m_texture(p_texture)
{
	m_glProgramID = glCreateProgram();

	GL_CALL(glAttachShader(m_glProgramID, p_vertexShaderID))
	GL_CALL(glAttachShader(m_glProgramID, p_fragmentShaderID))


	GL_CALL(glLinkProgram(m_glProgramID))
	
	//TODO : add some error hadling here to check for programm linking errors

}


SpriteRenderer::SpriteRenderer(RenderMe::Base::Texture p_texture, unsigned int p_vertexShaderID , unsigned int p_fragmentShaderID, unsigned int p_PPU)
	: m_texture(p_texture), g_PPU(p_PPU)
{
	m_glProgramID = glCreateProgram();

	GL_CALL(glAttachShader(m_glProgramID, p_vertexShaderID))
	GL_CALL(glAttachShader(m_glProgramID, p_fragmentShaderID))


	GL_CALL(glLinkProgram(m_glProgramID))
	//TODO : add some error hadling here to check for programm linking errors
}

SpriteRenderer::SpriteRenderer(RenderMe::Base::Texture p_texture,float* p_color, unsigned int p_vertexShaderID, unsigned int p_fragmentShaderID, unsigned int p_PPU)
	:m_texture(p_texture), g_PPU(p_PPU)
{

	g_color[0] = p_color[0];
	g_color[1] = p_color[1];
	g_color[2] = p_color[2];
	g_color[3] = p_color[3];
	
	m_glProgramID = glCreateProgram();

	GL_CALL(glAttachShader(m_glProgramID, p_vertexShaderID))
	GL_CALL(glAttachShader(m_glProgramID, p_fragmentShaderID))


	GL_CALL(glLinkProgram(m_glProgramID))

	//TODO : add some error hadling here to check for programm linking errors
}

SpriteRenderer::~SpriteRenderer()
{

}

void SpriteRenderer::setTexture(RenderMe::Base::Texture p_texture)
{
	m_texture = p_texture;
}

 RenderMe::Base::Texture SpriteRenderer::getTexture() const
{
	return m_texture;
}

unsigned int SpriteRenderer::getShaderProgram() const 
{
	return m_glProgramID;
}