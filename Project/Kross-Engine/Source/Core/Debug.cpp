/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *		- Chris Deitch.
 */

#include "Debug.h"

namespace Kross
{
	bool Debug::m_HasEnteredLog = false;

	void Debug::Log(std::string message)
	{
		#ifdef KROSS_RELEASE
		return;
		#endif

		if (!Debug::m_HasEnteredLog)
			Debug::StartLog();

		std::cout << " " << message;
	}

	void Debug::Log(const char* message)
	{
		#ifdef KROSS_RELEASE
		return;
		#endif

		if (!Debug::m_HasEnteredLog)
			Debug::StartLog();

		std::cout << " " << message;
	}

	void Debug::Log(bool value)
	{
		#ifdef KROSS_RELEASE
		return;
		#endif

		if (!Debug::m_HasEnteredLog)
			Debug::StartLog();

		if(value)
			std::cout << " True";

		else
			std::cout << " False";

		
	}

	void Debug::Log(float value)
	{
		#ifdef KROSS_RELEASE
		return;
		#endif

		if (!Debug::m_HasEnteredLog)
			Debug::StartLog();

		std::cout << " " << value << "f";
	}

	void Debug::Log(int value)
	{
		#ifdef KROSS_RELEASE
		return;
		#endif

		if (!Debug::m_HasEnteredLog)
			Debug::StartLog();

		std::cout << " " << value;
	}

	void Debug::Log(Vector1 vector)
	{
		#ifdef KROSS_RELEASE
		return;
		#endif

		if (!Debug::m_HasEnteredLog)
			Debug::StartLog();

		std::cout << " Vector1(" << vector.x << ")";
	}

	void Debug::Log(Vector2 vector)
	{
		#ifdef KROSS_RELEASE
		return;
		#endif

		if (!Debug::m_HasEnteredLog)
			Debug::StartLog();

		std::cout << " Vector2(" << vector.x << "," << vector.y << ")";
	}

	void Debug::Log(Vector3 vector)
	{
		#ifdef KROSS_RELEASE
		return;
		#endif

		if (!Debug::m_HasEnteredLog)
			Debug::StartLog();

		std::cout << " Vector3(" << vector.x << "," << vector.y << "," << vector.z << ")";
	}

	void Debug::Log(Vector4 vector)
	{
		#ifdef KROSS_RELEASE
		return;
		#endif

		if (!Debug::m_HasEnteredLog)
			Debug::StartLog();

		std::cout << " Vector4(" << vector.x << "," << vector.y << "," << vector.z << "," << vector.w << ")";
	}

	void Debug::Log(Matrix2 matrix)
	{
		#ifdef KROSS_RELEASE
		return;
		#endif

		if (!Debug::m_HasEnteredLog)
			Debug::StartLog();

		std::cout << " Matrix2\n [";
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 2; x++)
			{
				if (x != 1)
					std::cout << matrix[x][y] << ",";

				else
					std::cout << matrix[x][y];
			}

			std::cout << "]\n";
		}
	}

	void Debug::Log(Matrix3 matrix)
	{
		#ifdef KROSS_RELEASE
		return;
		#endif

		if (!Debug::m_HasEnteredLog)
			Debug::StartLog();

		std::cout << " Matrix3\n [";
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				if (x != 2)
					std::cout << matrix[x][y] << ",";

				else
					std::cout << matrix[x][y];
			}

			std::cout << "]\n";
		}
	}

	void Debug::Log(Matrix4 matrix)
	{
		#ifdef KROSS_RELEASE
		return;
		#endif

		if (!Debug::m_HasEnteredLog)
			Debug::StartLog();

		std::cout << " Matrix4\n [";
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (x != 3)
					std::cout << matrix[x][y] << ",";

				else
					std::cout << matrix[x][y];
			}

			std::cout << "]\n";
		}
	}

	void Debug::LogLine(std::string message)
	{
		Log(message);
		EndLine();
	}

	void Debug::LogLine(const char* message)
	{
		Log(message);
		EndLine();
	}

	void Debug::LogLine(bool value)
	{
		Log(value);
		EndLine();
	}

	void Debug::LogLine(float value)
	{
		Log(value);
		EndLine();
	}

	void Debug::LogLine(int value)
	{
		Log(value);
		EndLine();
	}

	void Debug::LogLine(Vector1 vector)
	{
		Log(vector);
		EndLine();
	}

	void Debug::LogLine(Vector2 vector)
	{
		Log(vector);
		EndLine();
	}

	void Debug::LogLine(Vector3 vector)
	{
		Log(vector);
		EndLine();
	}

	void Debug::LogLine(Vector4 vector)
	{
		Log(vector);
		EndLine();
	}

	void Debug::LogLine(Matrix2 matrix)
	{
		Log(matrix);
		EndLine();
	}

	void Debug::LogLine(Matrix3 matrix)
	{
		Log(matrix);
		EndLine();
	}

	void Debug::LogLine(Matrix4 matrix)
	{
		Log(matrix);
		EndLine();
	}

	void Debug::LogWarning(std::string message)
	{
		#ifdef KROSS_RELEASE
		return;
		#endif

		if (!Debug::m_HasEnteredLog)
			Debug::StartWarning();

		std::cout << " " << message;
	}

	void Debug::LogWarningLine(std::string message)
	{
		LogWarning(message);
		EndLine();
	}

	void Debug::LogError(std::string message)
	{
		#ifdef KROSS_RELEASE
		return;
		#endif

		if (!Debug::m_HasEnteredLog)
			Debug::StartError();

		std::cout << " " << message;
	}

	void Debug::LogErrorLine(std::string message)
	{
		LogError(message);
		EndLine();
	}
	void Debug::LogGLError(std::string message)
	{
		#ifdef KROSS_RELEASE
			return;
		#endif

		if (!Debug::m_HasEnteredLog)
			Debug::StartGLError();

		std::cout << " " << message;
	}
	void Debug::LogGLErrorLine(std::string message)
	{
		LogGLError(message);
		EndLine();
	}
}
