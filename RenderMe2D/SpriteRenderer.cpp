#include "SpriteRenderer.h"

using namespace RenderMe::RenderMe2D;



SpriteRenderer::SpriteRenderer() 
	:m_texture(RenderMe::Base::Texture())
{
	computeVertices();
}

SpriteRenderer::SpriteRenderer(RenderMe::Base::Texture p_texture,unsigned int p_shaderID)
	: m_texture(p_texture),m_shaderID(p_shaderID)
{
	computeVertices();
}


SpriteRenderer::SpriteRenderer(RenderMe::Base::Texture p_texture,unsigned int p_shaderID,unsigned int p_PPU)
	: m_texture(p_texture),m_shaderID(p_shaderID), m_PPU(p_PPU)
{
	computeVertices();
}

SpriteRenderer::SpriteRenderer(RenderMe::Base::Texture p_texture,float* p_color,unsigned int p_shaderID, unsigned int p_PPU)
	:m_texture(p_texture),m_shaderID(p_shaderID), m_PPU(p_PPU)
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
/// <summary>
/// returns 4 vertices each vetex contains it's relative position (x & y only), color in RGBA format (nomalized) and texture coordinates (x,y)
/// so each vertex has 8 floats of data
/// </summary>
/// <returns></returns>
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
	std::vector<float> vertices(32);

	//ws stands for world space
	float ws_Width= m_texture.getWidth() / m_PPU;
	float ws_Height= m_texture.getHeight() / m_PPU;

	//setting up position data
	 //top left vertex
	vertices[0] = -0.5f * ws_Width;
	vertices[1] = 0.5f * ws_Height;
	//buttom left vertex
	vertices[8] = -0.5f * ws_Width;
	vertices[9] = -0.5f * ws_Height;
	//buttom right vertex
	vertices[16] = 0.5f * ws_Width;
	vertices[17] = -0.5f * ws_Height;
	//top right vertex
	vertices[24] = 0.5f * ws_Width;
	vertices[25] = 0.5f * ws_Height;
	

	//setting up color data 
	 //top left vertex 
	vertices[2] = m_color[0];
	vertices[3] = m_color[1];
	vertices[4] = m_color[2];
	vertices[5] = m_color[3];
	//buttom left vertex
	vertices[10] = m_color[0];
	vertices[11] = m_color[1];
	vertices[12] = m_color[2];
	vertices[13] = m_color[3];
	//buttom right vertex 
	vertices[18] = m_color[0];
	vertices[19] = m_color[1];
	vertices[20] = m_color[2];
	vertices[21] = m_color[3];
	//top right vertex 
	vertices[26] = m_color[0];
	vertices[27] = m_color[1];
	vertices[28] = m_color[2];
	vertices[29] = m_color[3];

	//setting up texture coordinate data
	//top left vertex
	vertices[6] = 1;
	vertices[7] = 0;
	//buttom left vertex
	vertices[14] = 1;
	vertices[15] = 0;
	//buttom right vertex 
	vertices[22] = 1;
	vertices[23] = 0;
	//top right vertex 
	vertices[30] = 1;
	vertices[31] = 0;

	m_vertices = vertices;
}