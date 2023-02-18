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
	computeVertices();
	m_glProgramID = glCreateProgram();

	GL_CALL(glAttachShader(m_glProgramID, p_vertexShaderID))
	GL_CALL(glAttachShader(m_glProgramID, p_fragmentShaderID))


	GL_CALL(glLinkProgram(m_glProgramID))
	
	//TODO : add some error hadling here to check for programm linking errors

}


SpriteRenderer::SpriteRenderer(RenderMe::Base::Texture p_texture, unsigned int p_vertexShaderID , unsigned int p_fragmentShaderID, unsigned int p_PPU)
	: m_texture(p_texture), m_PPU(p_PPU)
{
	computeVertices();
	m_glProgramID = glCreateProgram();

	GL_CALL(glAttachShader(m_glProgramID, p_vertexShaderID))
	GL_CALL(glAttachShader(m_glProgramID, p_fragmentShaderID))


	GL_CALL(glLinkProgram(m_glProgramID))
	//TODO : add some error hadling here to check for programm linking errors
}

SpriteRenderer::SpriteRenderer(RenderMe::Base::Texture p_texture,float* p_color, unsigned int p_vertexShaderID, unsigned int p_fragmentShaderID, unsigned int p_PPU)
	:m_texture(p_texture), m_PPU(p_PPU)
{

	m_color[0] = p_color[0];
	m_color[1] = p_color[1];
	m_color[2] = p_color[2];
	m_color[3] = p_color[3];
	
	computeVertices();

	m_glProgramID = glCreateProgram();

	GL_CALL(glAttachShader(m_glProgramID, p_vertexShaderID))
	GL_CALL(glAttachShader(m_glProgramID, p_fragmentShaderID))


	GL_CALL(glLinkProgram(m_glProgramID))

	//TODO : add some error hadling here to check for programm linking errors
}

SpriteRenderer::~SpriteRenderer()
{

}

void SpriteRenderer::setPixelsPerUnit(unsigned int p_PPU)
{
	m_PPU = p_PPU;
	computeVertices();
}

 unsigned int SpriteRenderer::getPixelsPerUnit() const
{
	return m_PPU;
}
/// <summary>
/// returns 4 vertices each vetex contains it's relative position (x & y only), color in RGBA format (nomalized) and texture coordinates (x,y)
/// so each vertex has 8 floats of data
/// </summary>
/// <returns></returns>
 std::vector<Vertex> SpriteRenderer::getVertices() const
{
	return m_vertices;
}

 std::vector<unsigned int> SpriteRenderer::getIndices() const
{
	return m_indices;
}


void SpriteRenderer::setTexture(RenderMe::Base::Texture p_texture)
{
	m_texture = p_texture;
	computeVertices();
}

 RenderMe::Base::Texture SpriteRenderer::getTexture() const
{
	return m_texture;
}

void SpriteRenderer::computeVertices()
{
	if (&m_texture == nullptr)
		return;

	std::vector<Vertex> vertices(4);

	//ws stands for world space
	float ws_Width= (float)m_texture.getWidth() / m_PPU;
	float ws_Height= (float)m_texture.getHeight() / m_PPU;

	//setting up position data
	 //top left vertex
	vertices[0].position[0] = -0.5f * ws_Width;
	vertices[0].position[1] = 0.5f * ws_Height;
	//buttom left vertex
	vertices[1].position[0] = -0.5f * ws_Width;
	vertices[1].position[1] = -0.5f * ws_Height;
	//buttom right vertex
	vertices[2].position[0] = 0.5f * ws_Width;
	vertices[2].position[1] = -0.5f * ws_Height;
	//top right vertex
	vertices[3].position[0] = 0.5f * ws_Width;
	vertices[3].position[1] = 0.5f * ws_Height;
	
	
	//setting up color data 
	 //top left vertex 
	vertices[0].color[0] = m_color[0];
	vertices[0].color[1] = m_color[1];
	vertices[0].color[2]= m_color[2];
	vertices[0].color[3] = m_color[3];
	//buttom left vertex
	vertices[1].color[0] = m_color[0];
	vertices[1].color[1] = m_color[1];
	vertices[1].color[2] = m_color[2];
	vertices[1].color[3] = m_color[3];
	//buttom right vertex 
	vertices[2].color[0] = m_color[0];
	vertices[2].color[1] = m_color[1];
	vertices[2].color[2] = m_color[2];
	vertices[2].color[3] = m_color[3];
	//top right vertex 
	vertices[3].color[0] = m_color[0];
	vertices[3].color[1] = m_color[1];
	vertices[3].color[2] = m_color[2];
	vertices[3].color[3] = m_color[3];


	//setting up texture coordinate data
	//top left vertex
	vertices[0].uv[0] = 1;
	vertices[0].uv[1] = 0;
	//buttom left vertex
	vertices[1].uv[0] = 1;
	vertices[1].uv[1] = 0;
	//buttom right vertex 
	vertices[2].uv[0] = 1;
	vertices[2].uv[1] = 0;
	//top right vertex 
	vertices[3].uv[0] = 1;
	vertices[3].uv[1] = 0;

	m_vertices = vertices;
}

unsigned int SpriteRenderer::getShaderProgram() const 
{
	return m_glProgramID;
}