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
		outputStream << "========================================================================\n";
		outputStream << "Log Start: [" << title << "]\n";
		outputStream << "Log Dump File Created: " << GetLogTime() << "\n";
		outputStream << "========================================================================\n\n";

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
		outputStream << "\n\n========================================================================\n";
		outputStream << "Log End: [" << title << "]\n";
		outputStream << "========================================================================";

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
		SYSTEM_INFO siSysInfo;
		GetSystemInfo(&siSysInfo);
	
		m_LogLines.push_back("[HARDWARE INFORMATION]");

		std::string proccessorArchitecture = "";
		std::string OEMID = std::to_string(siSysInfo.dwOemId);

		if (OEMID == "9")		proccessorArchitecture = "x64 AMD/Intel";
		else if(OEMID == "5")	proccessorArchitecture = "ARM";
		else if(OEMID == "12")	proccessorArchitecture = "ARM64";
		else if(OEMID == "6")	proccessorArchitecture = "Intel Itanium-based";
		else if(OEMID == "0")	proccessorArchitecture = "x86 Intel";
		else                    proccessorArchitecture = "Unknown Chip Architecture";

		m_LogLines.push_back(" -> Processor Architecture: " + proccessorArchitecture);
		m_LogLines.push_back(" -> Processor Count: " + std::to_string(siSysInfo.dwNumberOfProcessors));

		std::string proccessorType = "";
		std::string prTy = std::to_string(siSysInfo.dwProcessorType);

		if (prTy == "386")			proccessorType = "Intel 386";
		else if (prTy == "486")		proccessorType = "Intel 486";
		else if (prTy == "586")		proccessorType = "Intel Pentium";
		else if (prTy == "2200")	proccessorType = "Intel IA64";
		else if (prTy == "8664")	proccessorType = "AMD/Intel X8664";
		else						proccessorType = "ARM";
		
		m_LogLines.push_back(" -> Processor Type: " + proccessorType);
		m_LogLines.push_back("------------------------------------------------------------------------");
		m_LogLines.push_back(" -> Processor Revision: " + std::to_string(siSysInfo.wProcessorRevision));
		m_LogLines.push_back("NOTE: Refer to \"docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/ns-sysinfoapi-system_info\" for translations on some of this.");
		m_LogLines.push_back("------------------------------------------------------------------------");
		m_LogLines.push_back("");

		unsigned long long physicalMemory = 0;
		GetPhysicallyInstalledSystemMemory(&physicalMemory);
		long double memory = static_cast<long double>(physicalMemory) / 1000.0;
		memory /= 1000.0;

		physicalMemory /= 1000;
		physicalMemory /= 1000;
		
		m_LogLines.push_back("[RAM]");
		m_LogLines.push_back(std::to_string(physicalMemory) + "GB");
		m_LogLines.push_back("");

		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* defaultVideoMode = glfwGetVideoMode(primaryMonitor);
		int refreshRateGuess;
		refreshRateGuess = defaultVideoMode->refreshRate;
	
		m_LogLines.push_back("[MONITOR INFORMATION]");
		m_LogLines.push_back(" -> Refresh Rate: " + std::to_string(refreshRateGuess));
		m_LogLines.push_back(" -> Screen resolution: " + std::to_string(defaultVideoMode->width) + " / " + std::to_string(defaultVideoMode->height));
		m_LogLines.push_back("");
		
		const GLubyte* vendor = glGetString(GL_VENDOR); // Returns the vendor
		const GLubyte* renderer = glGetString(GL_RENDERER); // Returns a hint to the model
		const GLubyte* version = glGetString(GL_VERSION);

		m_LogLines.push_back("[GRAPHICS CARD INFORMATION]");
		m_LogLines.push_back(" -> Vendor: " + std::string(reinterpret_cast<const char*>(vendor)));
		m_LogLines.push_back(" -> Model: " + std::string(reinterpret_cast<const char*>(renderer)));
		m_LogLines.push_back(" -> Application Version / Driver Version: " + std::string(reinterpret_cast<const char*>(version)));
	}
}