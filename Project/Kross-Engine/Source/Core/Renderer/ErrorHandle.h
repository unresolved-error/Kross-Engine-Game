/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *		- Chris Deitch. (Because he asked)
 */

#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "../Debug.h"

// OpenGL Error Checking, use wisely.
#define OPENGL_CHECK(x) Kross::OpenGLClearError();\
						x;\
						KROSS_ASSERT(Kross::OpenGLStatus(#x, __FILE__, __LINE__))

namespace Kross
{
	void OpenGLClearError()
	{
		#ifdef KROSS_DEBUG
		while (glGetError() != GL_NO_ERROR);
		#endif
	}

	bool OpenGLStatus(const char* funcName, const char* fileName, int line)
	{
		#ifdef KROSS_DEBUG
		while (GLenum error = glGetError())
		{
			std::string errorCodeType;
			if (error == GL_INVALID_OPERATION)
			{
				errorCodeType = "INVALID OPERATION";
			}

			Debug::LogError("GL ERROR!");
			Debug::Log(errorCodeType);
			Debug::Log((std::string)", Called on");
			Debug::Log((std::string)funcName);
			Debug::Log((std::string)"in");
			Debug::Log((std::string)fileName);
			Debug::Log((std::string)"on line");
			Debug::LogLine((std::string)std::to_string(line));

			return false;
		}
		#endif
		return true;
	}
}