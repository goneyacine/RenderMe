#pragma once

#include <iostream>
#include <unordered_map>
#include <GL/glew.h>
namespace RenderMe
{

	namespace Base
	{


		class ShaderManager
		{
		public:
			ShaderManager();
			~ShaderManager();

			/// <summary>
			///retruns shader id if it's compiled and 0 if compiling process failed
			/// </summary>
			/// <param name="p_shaderName">the name of shader that you will be using later to access the shader object</param>
			/// <param name="p_shaderType">shader type (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...)</param>
			/// <param name="p_filePath">path of shader file</param>
			/// <returns></returns>
			unsigned int compileShader_by_filePath(std::string p_shaderName, GLenum p_shaderType, std::string p_filePath);
			/// <summary>
		    ///retruns shader id if it's compiled and 0 if compiling process failed
			/// </summary>
			/// <param name="p_shaderName">the name of shader that you will be using later to access the shader object</param>
			/// <param name="p_shaderType">shader type (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...)</param>
			/// <param name="p_source">the shader source code</param>
			/// <returns></returns>
			unsigned int compileShader_by_source(std::string p_shaderName, GLenum p_shaderType, std::string p_source);
		private:
			//an unoredered map that assigns shader name (std::string) with it's shader object (or shader id (unsigned int)) and it's type (as GLenumS)
			//shader objects and types are stored pair, use pair.first to access the shader object, & pair.second to access the type
			std::unordered_map<std::string,std::pair<unsigned int,GLenum>> m_shaders;


		};
	}
}