/*
	Author: Deklyn Palmer.
	Editors:
		- Deklyn Palmer.
*/

#include "FileSystem.h"

namespace Kross
{
	std::string FileSystem::GetFileContents(const std::string& filepath)
	{
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;
			std::stringstream contents;

			/* Read the file line by line. */
			while (getline(fileStream, line))
				contents << line << "\n";

			fileStream.close();

			/* Return the file contents. */
			return contents.str();
		}

		else
		{
			fileStream.close();

			/* Return an empty string as it could not open the file. */
			return std::string();
		}
	}

	std::string FileSystem::GetFileContentsSingle(const std::string& filepath, int line)
	{
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string lineString;
			int lineIndex = 0;

			/* Read the file line by line. */
			while (getline(fileStream, lineString) && lineIndex < line)
				lineIndex++;

			fileStream.close();

			/* If the line index wasn't met then return a emtpy string. */
			if (lineIndex < line)
				return std::string();

			/* Return the file contents. */
			return lineString;
		}

		else
		{
			fileStream.close();

			/* Return an empty string as it could not open the file. */
			return std::string();
		}
	}
}