/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Serialiser.h"

#include "../File-IO/Manifest.h"

namespace Kross
{
	template<>
	class KROSS_API Serialiser<Editor>
	{
	public:
		/*!
			Loads in a Shader from the Specified Directory.
		*/
		void Load(const std::string& filepath, Object* editorCamera)
		{
			/* Open a Filestream. */
			std::fstream fileStream;
			fileStream.open(filepath.c_str());

			if (fileStream.is_open())
			{
				/* Parameter variables. */
				std::string cameraPosition = "";
				std::string cameraZoom = "";

				/* Variables for opening and reading the file. */
				std::string line;

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

					/* Keep Searching till we reach the end of the Line.*/
					while ((searchPosition = line.find("->")) != std::string::npos)
					{
						/* Grab the Property Type. */
						if (editorProperty.empty())
						{
							editorProperty = line.substr(0, searchPosition);
						}
						/* Grab the Property Value. */
						else
						{
							if (editorProperty == "CAMERA-POSITION") /* Extract Position. */
							{
								cameraPosition = line.substr(0, searchPosition);
							}
							if (editorProperty == "CAMERA-ZOOM") /* Extract Zoom. */
							{
								cameraZoom = line.substr(0, searchPosition);
							}
						}

						/* Remove the Previous Data. */
						line.erase(0, searchPosition + ((std::string)"->").length());
					}
				}

				/* Set Position.*/
				if (!cameraPosition.empty())
				{
					Vector2 position = Vector2(0.0f);
					std::string data = cameraPosition;
					data.erase(remove(data.begin(), data.end(), '['), data.end());
					data.erase(remove(data.begin(), data.end(), ']'), data.end());

					size_t searchPositionData = 0;
					std::string divider = ",";
					while ((searchPositionData = data.find(divider)) != std::string::npos)
					{
						std::string dataValue = data.substr(0, searchPositionData);
						position.x = std::stof(dataValue);

						data.erase(0, searchPositionData + divider.length());
					}

					position.y = std::stof(data);
					editorCamera->m_Transform->m_Position = position;
				}

				if (!cameraZoom.empty())
				{
					editorCamera->GetComponent<Camera>()->SetSize(std::stof(cameraZoom));
				}
			}

			/* Close the Stream. */
			fileStream.close();
		}

		void Write(const std::string& filepath, Object* serialisable)
		{
			std::ofstream writer;
			writer.open(filepath);

			if (writer.is_open())
			{
				writer << "EDITORBASE:\n";
				Vector2 position = serialisable->m_Transform->m_Position;
				float zoom = serialisable->GetComponent<Camera>()->GetSize();
				writer << "CAMERA-POSITION->[" << position.x << "," << position.y << "]->\n";
				writer << "CAMERA-ZOOM->" << zoom << "->";
			}

			writer.close();
		}
	};
}