/*
 *  Author: Finn Morgan.
 *  Editors:
 *		- Finn Morgan.
 *      - Jake Warren.
 */

#pragma once


#include "../Core.h"

#include "../Math/Math.h"
#include <vector>
#include "GL/glew.h"
#include "../Physics/Physics.h"


namespace Kross
{
	class KROSS_API LineRenderer
	{
		std::vector<glm::vec2> positions;
		std::vector<glm::vec3> colours;
		bool initialised = false;

		glm::vec3 currentColour = { 1.0f,1.0f,1.0f };

		glm::vec2 firstPos;
		glm::vec2 lastPos;
		glm::vec3 firstColour;
		glm::vec3 lastColour;
		bool lineActive = false;

		GLuint positionBufferID;
		GLuint colourBufferID;


	public:
		LineRenderer();
		~LineRenderer();

		//LineRenderer(const LineRenderer&) = delete;
		//LineRenderer(const LineRenderer&&) = delete;
		//const LineRenderer& operator=(const LineRenderer&) = delete;
		//const LineRenderer& operator=(LineRenderer&&) = delete;

		void Initialise();

		void SetColour(glm::vec3 colour);

		void DrawLineSegment(glm::vec2 start, glm::vec2 end);
		void DrawLineSegment(glm::vec2 start, glm::vec2 end, glm::vec3 colour);

		void FinishLineStrip();
		void FinishLineLoop();

		void AddPointToLine(glm::vec2 point);
		void AddPointToLine(glm::vec2 point, glm::vec3 colour);

		void DrawCross(glm::vec2 centre, float size);
		void DrawCross(glm::vec2 centre, float size, glm::vec3 colour);

		void DrawCircle(glm::vec2 centre, float size, int segmentCount = 64);
		void DrawCircle(glm::vec2 centre, float size, glm::vec3 colour, int segmentCount = 64);

		void DrawCapsule(glm::vec2 centre, glm::vec2 dimensions, int segmentCount = 64);
		void DrawCapsule(glm::vec2 centre, glm::vec2 dimensions, glm::vec3 colour, int segmentCount = 64);

		//This takes a pointer to what is presumed to be an array of pairs of floats, and draws a shape.
		//Might be useful for debug drawing if you integrate certain third party engines HINT HINT
		void DrawRawShape(float* data, unsigned int pointCount);
		void DrawRawShape(float* data, unsigned int pointCount, glm::vec3 colour);


		void DrawRigidBody(b2Body* body);

		void UpdateFrame();


		void Clear();
		void Compile();
		void Draw();
	};
}