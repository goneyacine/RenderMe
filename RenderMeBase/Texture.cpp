#include "Texture.h"


using namespace RenderMe::Base;

Texture::Texture() :
	m_width(0),m_height(0),m_textureGL(0)
{

}
Texture::Texture(unsigned int p_width, unsigned int p_height, unsigned int p_textureGL) 
	: m_width(p_width),m_height(p_height),m_textureGL(p_textureGL)
{

}

Texture::~Texture()
{

}

unsigned int Texture::getWidth() const
{
	return m_width;
}

unsigned int Texture::getHeight() const
{
	return m_height;
}

unsigned int Texture::getOpenGL_ID() const
{
	return m_textureGL;
}
