#pragma once

#include "../Debug.h"

#include "GLFW/glfw3.h"
#include "GL/glew.h"

namespace Kross
{
	void GLErrorCheck()
	{
		GLuint glError = glGetError();
		std::string errorValue;

		if (glError == GL_INVALID_ENUM)
		{
			errorValue = "GL Error: Invalid enumeration.";
		}
		else if (glError == GL_INVALID_VALUE)
		{
			errorValue = "GL Error: Invalid value.";
		}
		else if (glError == GL_INVALID_OPERATION)
		{
			errorValue = "GL Error: Invalid operation.";
		}
		else if (glError == GL_INVALID_FRAMEBUFFER_OPERATION)
		{
			errorValue = "GL Error: Invalid framebuffer operation.";
		}
		else if (glError == GL_OUT_OF_MEMORY)
		{
			errorValue = "GL Error: Out of memory.";
		}
		else if (glError == GL_STACK_UNDERFLOW)
		{
			errorValue = "GL Error: Stack underflow.";
		}
		else if (glError == GL_STACK_OVERFLOW)
		{
			errorValue = "GL Error: Stack overflow.";
		}
		else if (glError == GL_NO_ERROR)
		{
			errorValue = "No error.";
			return;
		}
		else
		{
			errorValue = "GL Error: Mysterious.";
		}

		Debug::LogErrorLine(errorValue);
		return;
	}
}