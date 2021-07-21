/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *		- Chris Deitch. (Because he asked)
 */

#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

// OpenGL Error Checking, use wisely.
#define OPENGL_CHECK(x) Kross::OpenGLClearError();\
						x;\
						KROSS_ASSERT(Kross::OpenGLStatus(#x, __FILE__, __LINE__))

namespace Kross
{
	void OpenGLClearError();

	bool OpenGLStatus(const char* funcName, const char* fileName, int line);
}