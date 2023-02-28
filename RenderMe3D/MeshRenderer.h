#pragma once

#include "Texture.h"
#include "Mesh.h"
#include "Uniforms.h"

namespace RenderMe
{
	namespace RenderMe3D
	{
		class MeshRenderer
		{
		public :
			MeshRenderer();
			MeshRenderer(Mesh p_mesh,RenderMe::Base::Texture p_texture,unsigned int p_vertexShader,unsigned int p_fragmentShader);
			~MeshRenderer();

			unsigned int getShaderProgram() const;

			void setUniforms_1f(RenderMe::Base::Uniform1f p_uniform);
			void setUniforms_2f(RenderMe::Base::Uniform2f p_uniform);
			void setUniforms_3f(RenderMe::Base::Uniform3f p_uniform);
			void setUniforms_4f(RenderMe::Base::Uniform4f p_uniform);

			void setUniforms_1i(RenderMe::Base::Uniform1i p_uniform);
			void setUniforms_2i(RenderMe::Base::Uniform2i p_uniform);
			void setUniforms_3i(RenderMe::Base::Uniform3i p_uniform);
			void setUniforms_4i(RenderMe::Base::Uniform4i p_uniform);

			void setUniforms_1ui(RenderMe::Base::Uniform1ui p_uniform);
			void setUniforms_2ui(RenderMe::Base::Uniform2ui p_uniform);
			void setUniforms_3ui(RenderMe::Base::Uniform3ui p_uniform);
			void setUniforms_4ui(RenderMe::Base::Uniform4ui p_uniform);


			Mesh g_mesh;
			RenderMe::Base::Texture g_texture;

		private :
			unsigned int m_shaderProgramID;
		};
	}
}
