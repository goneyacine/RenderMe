#include "MeshRenderer.h"
#include "ErrorHandler.h"
using namespace RenderMe::RenderMe3D;

MeshRenderer::MeshRenderer()
{
}

MeshRenderer::MeshRenderer(Mesh p_mesh, RenderMe::Base::Texture p_texture, unsigned int p_vertexShader, unsigned int p_fragmentShader) :
	g_mesh(p_mesh),g_texture(p_texture)
{
	m_shaderProgramID = glCreateProgram();

	GL_CALL(glAttachShader(m_shaderProgramID, p_vertexShader))
	GL_CALL(glAttachShader(m_shaderProgramID, p_fragmentShader))
    GL_CALL(glLinkProgram(m_shaderProgramID))
}

MeshRenderer::~MeshRenderer()
{
	GL_CALL(glDeleteProgram(m_shaderProgramID))
}

unsigned int MeshRenderer::getShaderProgram() const
{
	return m_shaderProgramID;
}


void MeshRenderer::setUniforms_1f(RenderMe::Base::Uniform1f p_uniform)
{
	GL_CALL(glUniform1f(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1))
}

void MeshRenderer::setUniforms_2f(RenderMe::Base::Uniform2f p_uniform)
{
	GL_CALL(glUniform2f(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2))
}

void MeshRenderer::setUniforms_3f(RenderMe::Base::Uniform3f p_uniform)
{
	GL_CALL(glUniform3f(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2, p_uniform.value3))
}

void MeshRenderer::setUniforms_4f(RenderMe::Base::Uniform4f p_uniform)
{
	GL_CALL(glUniform4f(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2, p_uniform.value3, p_uniform.value4))
}

void MeshRenderer::setUniforms_1i(RenderMe::Base::Uniform1i p_uniform)
{
	GL_CALL(glUniform1i(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1))
}

void MeshRenderer::setUniforms_2i(RenderMe::Base::Uniform2i p_uniform)
{
	GL_CALL(glUniform2i(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2))

}

void MeshRenderer::setUniforms_3i(RenderMe::Base::Uniform3i p_uniform)
{
	GL_CALL(glUniform3i(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2, p_uniform.value3))

}

void MeshRenderer::setUniforms_4i(RenderMe::Base::Uniform4i p_uniform)
{
	GL_CALL(glUniform4i(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2, p_uniform.value3, p_uniform.value4))

}

void MeshRenderer::setUniforms_1ui(RenderMe::Base::Uniform1ui p_uniform)
{
	GL_CALL(glUniform1ui(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1))
}

void MeshRenderer::setUniforms_2ui(RenderMe::Base::Uniform2ui p_uniform)
{
	GL_CALL(glUniform2ui(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2))
}

void MeshRenderer::setUniforms_3ui(RenderMe::Base::Uniform3ui p_uniform)
{
	GL_CALL(glUniform3ui(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2, p_uniform.value3))
}

void MeshRenderer::setUniforms_4ui(RenderMe::Base::Uniform4ui p_uniform)
{
	GL_CALL(glUniform4ui(glGetUniformLocation(getShaderProgram(), p_uniform.name.c_str()), p_uniform.value1, p_uniform.value2, p_uniform.value3, p_uniform.value4))
}
