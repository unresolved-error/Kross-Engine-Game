/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Chris Deitch
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

	void Logger::WriteSystemInfo()
	{
	//	SYSTEM_INFO siSysInfo;
	//	GetSystemInfo(&siSysInfo);
	//
	//	m_LogLines.push_back("[SYSTEM INFO BLOCK] Retrieved at " + GetLogTime() + " ");
	//	m_LogLines.push_back("Hardware information: \n");
	//	m_LogLines.push_back("	OEM ID: \n" + siSysInfo.dwOemId);
	//	m_LogLines.push_back("  Number of processors: \n" + siSysInfo.dwNumberOfProcessors);
	//	m_LogLines.push_back("  Page size: \n" + siSysInfo.dwPageSize);
	//	m_LogLines.push_back("  Processor type: \n" + siSysInfo.dwProcessorType);
	//	m_LogLines.push_back("  Processor Revision: \n" + siSysInfo.wProcessorRevision);
	//	m_LogLines.push_back("refer to docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/ns-sysinfoapi-system_info  for translations on some of this. \n");
	//	
	//
	//	PULONGLONG systemMem;
	//	GetPhysicallyInstalledSystemMemory(systemMem);
	//	m_LogLines.push_back("  Ram in Kilobytes: \n" + *systemMem);
	//
	//	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	//	const GLFWvidmode* defaultVideoMode = glfwGetVideoMode(primaryMonitor);
	//	int refreshRateGuess;
	//	refreshRateGuess = defaultVideoMode->refreshRate;
	//
	//	m_LogLines.push_back("  Refresh Rate Estimate: \n" + refreshRateGuess);
	//
	//	m_LogLines.push_back("END COMPUTER SPECS LOG");
	//
	}
}