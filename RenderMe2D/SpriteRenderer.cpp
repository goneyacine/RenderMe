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

	m_color[0] = p_color[0];
	m_color[1] = p_color[1];
	m_color[2] = p_color[2];
	m_color[3] = p_color[3];
	
	m_glProgramID = glCreateProgram();

	GL_CALL(glAttachShader(m_glProgramID, p_vertexShaderID))
	GL_CALL(glAttachShader(m_glProgramID, p_fragmentShaderID))


	GL_CALL(glLinkProgram(m_glProgramID))

	//TODO : add some error hadling here to check for programm linking errors
}

SpriteRenderer::~SpriteRenderer()
{
	GL_CALL(glDeleteProgram(m_glProgramID))
}

void SpriteRenderer::setTexture(RenderMe::Base::Texture p_texture)
{
	m_texture = p_texture;
}

void RenderMe::RenderMe2D::SpriteRenderer::setUniforms_1f(RenderMe::Base::Uniform1f p_uniform)
{
	GL_CALL(glUniform1f(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1))
}

void RenderMe::RenderMe2D::SpriteRenderer::setUniforms_2f(RenderMe::Base::Uniform2f p_uniform)
{
	GL_CALL(glUniform2f(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2))
}

void RenderMe::RenderMe2D::SpriteRenderer::setUniforms_3f(RenderMe::Base::Uniform3f p_uniform)
{
	GL_CALL(glUniform3f(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2,p_uniform.value3))
}

void RenderMe::RenderMe2D::SpriteRenderer::setUniforms_4f(RenderMe::Base::Uniform4f p_uniform)
{
	GL_CALL(glUniform4f(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2, p_uniform.value3, p_uniform.value4))
}

void RenderMe::RenderMe2D::SpriteRenderer::setUniforms_1i(RenderMe::Base::Uniform1i p_uniform)
{
	GL_CALL(glUniform1i(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1))
}

void RenderMe::RenderMe2D::SpriteRenderer::setUniforms_2i(RenderMe::Base::Uniform2i p_uniform)
{
	GL_CALL(glUniform2i(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2))

}

void RenderMe::RenderMe2D::SpriteRenderer::setUniforms_3i(RenderMe::Base::Uniform3i p_uniform)
{
	GL_CALL(glUniform3i(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2, p_uniform.value3))

}

void RenderMe::RenderMe2D::SpriteRenderer::setUniforms_4i(RenderMe::Base::Uniform4i p_uniform)
{
	GL_CALL(glUniform4i(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2, p_uniform.value3, p_uniform.value4))

}
 
void RenderMe::RenderMe2D::SpriteRenderer::setUniforms_1ui(RenderMe::Base::Uniform1ui p_uniform)
{
	GL_CALL(glUniform1ui(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1))
}

void RenderMe::RenderMe2D::SpriteRenderer::setUniforms_2ui(RenderMe::Base::Uniform2ui p_uniform)
{
	GL_CALL(glUniform2ui(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2))
}

void RenderMe::RenderMe2D::SpriteRenderer::setUniforms_3ui(RenderMe::Base::Uniform3ui p_uniform)
{
	GL_CALL(glUniform3ui(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2, p_uniform.value3))
}

void RenderMe::RenderMe2D::SpriteRenderer::setUniforms_4ui(RenderMe::Base::Uniform4ui p_uniform)
{
	GL_CALL(glUniform4ui(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2, p_uniform.value3, p_uniform.value4))
}

 RenderMe::Base::Texture SpriteRenderer::getTexture() const
{
	return m_texture;
}

unsigned int SpriteRenderer::getShaderProgram() const 
{
	return m_glProgramID;
}