/*
	Author: Deklyn Palmer.
	Editors:
		- Deklyn Palmer.
*/

#pragma once

#include "Core.h"

namespace Kross
{
	class KROSS_API FileSystem
	{
	private:
		FileSystem() {};
		~FileSystem() {};
	protected:

	public:
		// Obtains the file contents in a string. (LAID OUT AS REPRESENTED IN FILE)
		static std::string GetFileContents(const std::string& filepath);

		// Obtains the file contents in a string. (ONLY ONE LINE FROM THE FILE)
		static std::string GetFileContentsSingle(const std::string& filepath, int line);
	};
}