/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Serialiser.h"

#include "../File-IO/Manifest.h"
#include "../Editor/Windows/SceneHierarchy.h"
#include "../Manager/SceneManager.h"

namespace Kross
{
	template<>
	class KROSS_API Serialiser<SceneHierarchy>
	{
	public:
		/*!
			Writes out the Folders of the Objects.
		*/
		void Write(const std::string& filepath, SceneHierarchy* serialisable)
		{

			std::ofstream writer;
			writer.open(filepath);

			if (writer.is_open())
			{
				writer << "EDITOROBJECTHIERARCHY:\n";
				for (int i = 0; i < serialisable->m_Folders.size(); i++)
				{
					writer << "FOLDER-START->\n";
					writer << "NAME->" << serialisable->m_Folders[i]->GetName() << "->\n";
					for (int c = 0; c < serialisable->m_Folders[i]->m_Contents.size(); c++)
					{
						writer << "OBJECT->" << serialisable->m_Folders[i]->m_Contents[c]->GetName() << "->\n";
					}
					writer << "FOLDER-END->\n";
				}
			}

			writer.close();
		}
		/*!
			Loads in the Scene Hierarchy.
		*/
		void Load(const std::string& filepath, SceneHierarchy* serialisable)
		{
			Logger* logger = KROSS_NEW Logger();
			/* Report and Early out if the Filepath doesn't exist. */
			if (!FileSystem::FilepathExists(filepath))
			{
				logger->WriteWarning("Loading Editor Object Hierarchy Dump from File: [" + filepath + "] Failed!");
				logger->Write("--- Reasons:");

				/* Report the Reason. */
				logger->Write("----- Kross Editor Object Hierarchy File is invalid! Filepath: [" + filepath + "]");
				logger->WriteSpace();

				logger->Dump("Editor Object Hierarchy", "Editor-Hierarchy-Log.txt");
				delete logger;

				return;
			}

			/* Open a Filestream. */
			std::fstream fileStream;
			fileStream.open(filepath.c_str());

			if (fileStream.is_open())
			{
				/* Variables for opening and reading the file. */
				std::string line = "";
				Folder<Object>* folder = nullptr;

				/* Read the file line by line. */
				while (getline(fileStream, line))
				{
					/* Ignore Comments. */
					if (line.find("//") != std::string::npos)
					{
						continue;
					}
					/* Quick Variables. */
					size_t searchPosition = 0;
					std::string editorProperty = "";
					
					if (line == "FOLDER-START->")
					{
						if (!folder)
						{
							folder = KROSS_NEW Folder<Object>();
						}

						continue;
					}

					else if (line == "FOLDER-END->")
					{
						if (folder)
						{
							serialisable->m_Folders.push_back(folder);
							folder = nullptr;
						}
						continue;
					}

					/* Keep Searching till we reach the end of the Line.*/
					while ((searchPosition = line.find("->")) != std::string::npos)
					{
						if (editorProperty.empty())
						{
							editorProperty = line.substr(0, searchPosition);
						}

						else
						{
							if (editorProperty == "NAME") /* Extract the Name. */
							{
								std::cout << "Name: |" << line.substr(0, searchPosition) << "|" << std::endl;
								folder->m_Name = line.substr(0, searchPosition);
							}
							else if (editorProperty == "OBJECT") /* Extract the Object. */
							{
								Object* object = SceneManager::GetScene()->FindObject(line.substr(0, searchPosition));
								folder->Push(object);
							}
						}

						/* Remove the Previous Data. */
						line.erase(0, searchPosition + ((std::string)"->").length());
					}
				}
			}

			/* Close the File Stream. */
			fileStream.close();

			delete logger;
		}
	};
}