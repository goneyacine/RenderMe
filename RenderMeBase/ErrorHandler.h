#pragma once
#include <cassert>
#include "GL/glew.h"

#define GL_CALL(x) ClearGLErrors();\
 x;\
 assert(LogGLErrors());

namespace RenderMe
{
	namespace Base

	{
		 void ClearGLErrors();
		 bool LogGLErrors();
	}
}