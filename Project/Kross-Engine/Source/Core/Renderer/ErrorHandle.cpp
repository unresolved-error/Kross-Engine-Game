/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *		- Chris Deitch. (Because he asked)
 */

#include "ErrorHandle.h"

#include "../Debug.h"

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
		/* While there is a Error. */
		while (GLenum error = glGetError())
		{
			/* Grab the Code Type. */
			std::string errorCodeType;
			if (error == GL_INVALID_ENUM)
			{
				errorCodeType = "INVALID ENUM";
			}
			else if (error == GL_INVALID_VALUE)
			{
				errorCodeType = "INVALID VALUE";
			}
			else if (error == GL_INVALID_OPERATION)
			{
				errorCodeType = "INVALID OPERATION";
			}
			else if (error == GL_INVALID_FRAMEBUFFER_OPERATION)
			{
				errorCodeType = "INVALID FRAMEBUFFER OPERATION";
			}
			else if (error == GL_OUT_OF_MEMORY)
			{
				errorCodeType = "OUT OF MEMORY";
			}
			else if (error == GL_STACK_UNDERFLOW)
			{
				errorCodeType = "STACK UNDERFLOW";
			}
			else if (error == GL_STACK_OVERFLOW)
			{
				errorCodeType = "STACK OVERFLOW";
			}
			else
			{
				errorCodeType = "UNKNOWN";
			}
			/* Report it. */
			Debug::LogGLError(errorCodeType + (std::string)", Called on " + (std::string)funcName);
			Debug::Log((std::string)"in " + (std::string)fileName + (std::string)" on line " + (std::string)std::to_string(line));
			Debug::EndLine();

			return false;
		}
		#endif

		/* All is good. */
		return true;
	}
}