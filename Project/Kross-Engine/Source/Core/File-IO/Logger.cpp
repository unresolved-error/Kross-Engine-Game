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
		outputStream << "Log Start: " << title << "\n";
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
		outputStream << "Log End: " << title << "\n";
		outputStream << "==================================\n\n";

		/* Close the stream. */
		outputStream.close();

		/* Clear the Log. */
		m_LogLines.clear();
	}
}