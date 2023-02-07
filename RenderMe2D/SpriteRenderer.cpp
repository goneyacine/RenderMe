#include "SpriteRenderer.h"


using namespace RenderMe::RenderMe2D;



SpriteRenderer::SpriteRenderer() 
	:m_texture(RenderMe::Base::Texture())
{
	computeVertices();
}

SpriteRenderer::SpriteRenderer(RenderMe::Base::Texture p_texture)
	: m_texture(p_texture)
{
	computeVertices();
}


SpriteRenderer::SpriteRenderer(RenderMe::Base::Texture p_texture,unsigned int p_PPU = 100)
	: m_texture(p_texture),m_PPU(p_PPU)
{
	computeVertices();
}

SpriteRenderer::SpriteRenderer(RenderMe::Base::Texture p_texture,float* p_color, unsigned int p_PPU = 100)
	:m_texture(p_texture),m_PPU(p_PPU)
{
	m_color[0] = p_color[0];
	m_color[1] = p_color[1];
	m_color[2] = p_color[2];
	m_color[3] = p_color[3];
	computeVertices();

}

SpriteRenderer::~SpriteRenderer()
{

}

void SpriteRenderer::setPixelsPerUnit(unsigned int p_PPU)
{
	m_PPU = p_PPU;
	computeVertices();
}

inline unsigned int SpriteRenderer::getPixelsPerUnit() const
{
	return m_PPU;
}

inline std::vector<float> SpriteRenderer::getVertices() const
{
	return m_vertices;
}

inline std::vector<unsigned int> SpriteRenderer::getIndices() const
{
	return m_indices;
}


void SpriteRenderer::setTexture(RenderMe::Base::Texture p_texture)
{
	m_texture = p_texture;
	computeVertices();
}

inline RenderMe::Base::Texture SpriteRenderer::getTexture() const
{
	return m_texture;
}

void SpriteRenderer::computeVertices()
{
	//TODO : implement this function
}