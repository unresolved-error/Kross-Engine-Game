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
#ifndef KROSS_RELEASE
	#define OPENGL_CHECK(x) Kross::OpenGLClearError();\
						x;\
						KROSS_ASSERT(Kross::OpenGLStatus(#x, __FILE__, __LINE__))
#else
	#define OPENGL_CHECK(x) x
#endif

namespace Kross
{
	void OpenGLClearError();

	bool OpenGLStatus(const char* funcName, const char* fileName, int line);
}