/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Logger.h"

namespace Kross
{
	void Logger::Dump(const std::string& title, const std::string& filepath)
	{
		/* Make a File to Output to. */
		std::ofstream outputStream;
		outputStream.open(filepath.c_str());

		/* Start the Dump. */
		outputStream << "==================================\n";
		outputStream << "Log Start: [" << title << "]\n";
		outputStream << "Log Dump File Created: " << GetLogTime() << "\n";
		outputStream << "==================================\n\n";

		/* Go through all Logger Lines and Write them. */
		for (int i = 0; i < m_LogLines.size(); i++)
		{
			/* Write each line. */
			outputStream << m_LogLines[i];

			/* Start a New Line. */
			if (i != m_LogLines.size() - 1)
			{
				outputStream << "\n";
			}
		}

		/* End the Dump. */
		outputStream << "\n\n==================================\n";
		outputStream << "Log End: [" << title << "]\n";
		outputStream << "==================================";

		/* Close the stream. */
		outputStream.close();

		/* Clear the Log. */
		m_LogLines.clear();
	}

	std::string Logger::GetLogTime()
	{
		/* Log Time Creation. */
		std::time_t timeLogged = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::string timeLoggedStr = "[" + (std::string)std::ctime(&timeLogged) + "]";

		/* Removing the newline character. */
		timeLoggedStr.erase(std::remove(timeLoggedStr.begin(), timeLoggedStr.end(), '\n'), timeLoggedStr.end());

		/* Return the String. */
		return timeLoggedStr;
	}

	void Logger::WriteLog(const std::string& line)
	{
		m_LogLines.push_back("[Log] " + GetLogTime() + " " + line);
	}

	void Logger::WriteWarning(const std::string& line)
	{
		m_LogLines.push_back("[Warning] " + GetLogTime() + " " + line);
	}

	void Logger::WriteError(const std::string& line)
	{
		m_LogLines.push_back("[Error] " + GetLogTime() + " " + line);
	}
}