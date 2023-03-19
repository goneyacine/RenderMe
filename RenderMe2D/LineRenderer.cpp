#include "LineRenderer.h"
#include "ErrorHandler.h"


using namespace RenderMe::RenderMe2D;

LineRenderer::LineRenderer()
{
}

LineRenderer::LineRenderer(unsigned int p_vertexShader, unsigned int p_fragmentShader, Vector4 p_color)
	: m_color(p_color)
{
	setShaders(p_vertexShader, p_fragmentShader);
}

LineRenderer::LineRenderer(std::vector<Vector2> p_points, unsigned int p_vertexShader, unsigned int p_fragmentShader, Vector4 p_color)
	: m_color(p_color)
{
	addPoints(p_points);
	setShaders(p_vertexShader, p_fragmentShader);
}

void LineRenderer::addPoint(Vector2 p_point)
{
	m_points.push_back(p_point);
	//TODO : I need to make the shape of the line smoother
	Vertex v1 =
	{
		{p_point.x + m_thikness,p_point.y + m_thikness},
		{m_color.x,m_color.y,m_color.z,m_color.w}
	};
	Vertex v2 =
	{
		{p_point.x - m_thikness,p_point.y - m_thikness},
		{m_color.x,m_color.y,m_color.z,m_color.w}
	};

	m_vertices.push_back(v1);
	m_vertices.push_back(v2);
	//0, 1, 2, 2, 3, 0
	if (m_points.size() >= 2)
	{
		m_indices.push_back(m_vertices.size() - 4);
		m_indices.push_back(m_vertices.size() - 3);
		m_indices.push_back(m_vertices.size() - 2);
		m_indices.push_back(m_vertices.size() - 2);
		m_indices.push_back(m_vertices.size() - 1);
		m_indices.push_back(m_vertices.size() - 4);
	}

}

void LineRenderer::removePoint(int p_index)
{
	if (p_index > m_points.size() - 1 || p_index < 0)
		return;


	//remove the point
	m_points.erase(m_points.begin() + p_index);
	//remove vertices
	m_vertices.erase(m_vertices.begin() + (p_index * 2));
	m_vertices.erase(m_vertices.begin() + (p_index * 2) + 1);
	//remove and update indices
	m_indices.erase(m_indices.begin() + (p_index * 2));
	m_indices.erase(m_indices.begin() + (p_index * 2) + 1);
	m_indices.erase(m_indices.begin() + (p_index * 2) + 2);
	m_indices.erase(m_indices.begin() + (p_index * 2) + 3);
	m_indices.erase(m_indices.begin() + (p_index * 2) + 4);
	m_indices.erase(m_indices.begin() + (p_index * 2) + 5);

	for (int i = 0; i < m_indices.size(); i++)
		m_indices[i] = m_indices[i] - 2;
}

void LineRenderer::addPoints(std::vector<Vector2> p_points)
{
	for (const auto point : p_points)
		addPoint(point);
}

void LineRenderer::removePoints(std::vector<int> p_indices)
{
	for (const auto index : p_indices)
		removePoint(index);
}

void LineRenderer::setPoint(int p_index, Vector2 p_point)
{
	if (p_index > m_points.size() - 1 || p_index < 0)
		return;

	m_points[p_index] = p_point;

	Vertex v1 =
	{
		{p_point.x + m_thikness,p_point.y + m_thikness},
		{m_color.x,m_color.y,m_color.z,m_color.w}
	};
	Vertex v2 =
	{
		{p_point.x - m_thikness,p_point.y - m_thikness},
		{m_color.x,m_color.y,m_color.z,m_color.w}
	};


	m_vertices[p_index * 2] = v1;
	m_vertices[(p_index * 2) + 1] = v2;

}

Vector2 LineRenderer::getPoint(int p_index)
{
	return m_points[p_index];
}

std::vector<Vector2> LineRenderer::getPoints()
{
	return m_points;
}

void LineRenderer::setShaders(unsigned int p_vertexShader, unsigned int p_fragmentShader)
{
	if (m_shaderProgram != 0)
		glDeleteProgram(m_shaderProgram);

	m_shaderProgram = glCreateProgram();
	GL_CALL(glAttachShader(m_shaderProgram, p_vertexShader))
		GL_CALL(glAttachShader(m_shaderProgram, p_fragmentShader))
		GL_CALL(glLinkProgram(m_shaderProgram))
}

unsigned int LineRenderer::getShaderProgram()
{
	return m_shaderProgram;
}

void LineRenderer::setThikness(float p_thikness)
{
	m_thikness = p_thikness;

	for (int i = 0; i < m_points.size(); i++)
	{
		Vector2 point = m_points[i];
		Vertex v1 =
		{
			{point.x + m_thikness,point.y + m_thikness},
			{m_color.x,m_color.y,m_color.z,m_color.w}
		};
		Vertex v2 =
		{
			{point.x - m_thikness,point.y - m_thikness},
			{m_color.x,m_color.y,m_color.z,m_color.w}
		};


		m_vertices[i * 2] = v1;
		m_vertices[(i * 2) + 1] = v2;
	}
}

void LineRenderer::setColor(Vector4 p_color)
{
	m_color = p_color;
	for (int i = 0; i < m_vertices.size(); i++)
	{
		m_vertices[i].color[0] = p_color.x;
		m_vertices[i].color[1] = p_color.y;
		m_vertices[i].color[2] = p_color.z;
		m_vertices[i].color[3] = p_color.w;
	}
}

Vector4 LineRenderer::getColor()
{
	return m_color;
}

float LineRenderer::getThikness()
{
	return m_thikness;
}

std::vector<Vertex> LineRenderer::getVertices()
{
	return m_vertices;
}

std::vector<Index> LineRenderer::getIndices()
{
	return m_indices;
}
