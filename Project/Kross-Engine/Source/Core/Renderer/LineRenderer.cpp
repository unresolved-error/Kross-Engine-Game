/*
 *  Author: Finn Morgan.
 *  Editors:
 *		- Finn Morgan.
 *		- Jake Warren.
 *		- Deklyn Palmer.
 */

#include "LineRenderer.h"
#include <iostream>

//#include "../Physics/Physics.h"

namespace Kross
{
	void LineRenderer::Initialise()
	{
		glGenBuffers(1, &positionBufferID);
		glGenBuffers(1, &colourBufferID);
		initialised = true;
	}

	void LineRenderer::SetColour(glm::vec3 colour)
	{
		currentColour = colour;
	}

	void LineRenderer::DrawLineSegment(glm::vec2 start, glm::vec2 end)
	{
		DrawLineSegment(start, end, currentColour);
	}

	void LineRenderer::DrawLineSegment(glm::vec2 start, glm::vec2 end, glm::vec3 colour)
	{
		positions.push_back(start);
		positions.push_back(end);
		colours.push_back(colour);
		colours.push_back(colour);
	}

	void LineRenderer::FinishLineStrip()
	{
		if (lineActive)
		{
			lineActive = false;
		}
	}

	void LineRenderer::FinishLineLoop()
	{
		if (lineActive)
		{
			positions.push_back(lastPos);
			positions.push_back(firstPos);
			colours.push_back(lastColour);
			colours.push_back(firstColour);
			lineActive = false;
		}
	}

	void LineRenderer::AddPointToLine(glm::vec2 point)
	{
		AddPointToLine(point, currentColour);
	}

	void LineRenderer::AddPointToLine(glm::vec2 point, glm::vec3 colour)
	{
		if (lineActive)
		{
			positions.push_back(lastPos);
			positions.push_back(point);
			colours.push_back(lastColour);
			colours.push_back(colour);
			lastPos = point;
			lastColour = colour;
		}
		else
		{
			lineActive = true;
			lastPos = point;
			firstPos = point;
			lastColour = colour;
			firstColour = colour;
		}
	}

	void LineRenderer::DrawCross(glm::vec2 centre, float size)
	{
		DrawCross(centre, size, currentColour);
	}

	void LineRenderer::DrawCross(glm::vec2 centre, float size, glm::vec3 colour)
	{
		positions.push_back({ centre.x - size, centre.y - size });
		positions.push_back({ centre.x + size, centre.y + size });
		positions.push_back({ centre.x + size, centre.y - size });
		positions.push_back({ centre.x - size, centre.y + size });
		colours.push_back(colour);
		colours.push_back(colour);
		colours.push_back(colour);
		colours.push_back(colour);
	}

	void LineRenderer::DrawCircle(glm::vec2 centre, float size, int segmentCount)
	{
		DrawCircle(centre, size, currentColour, segmentCount);
	}

	void LineRenderer::DrawCircle(glm::vec2 centre, float size, glm::vec3 colour, int segmentCount)
	{
		float cosAngle = cos(2 * 3.14159f / segmentCount);
		float sinAngle = sin(2 * 3.14159f / segmentCount);

		glm::mat2 rotMat = { {cosAngle, -sinAngle},{sinAngle, cosAngle} };

		glm::vec2 plotPoint(0, size);

		for (int i = 0; i <= segmentCount; i++)
		{
			positions.push_back(centre + plotPoint);
			plotPoint = rotMat * plotPoint;
			positions.push_back(centre + plotPoint);
			colours.push_back(colour);
			colours.push_back(colour);
		}
	}

	void LineRenderer::DrawCapsule(Body* body, glm::vec2 dimensions, int segmentCount)
	{
		DrawCapsule(body, dimensions, currentColour, segmentCount);
	}

	void LineRenderer::DrawCapsule(Body* body, glm::vec2 dimensions, glm::vec3 colour, int segmentCount)
	{
		int side = 0;
		b2Transform bodyTransform = body->GetTransform();

		for (b2Fixture* thisFixture = body->GetFixtureList(); thisFixture; thisFixture = thisFixture->GetNext())
		{
			b2Shape* theShape = thisFixture->GetShape();
			b2Shape::Type theShapeType = theShape->GetType();

			this->SetColour((body->GetType() == b2BodyType::b2_staticBody) ? glm::vec3(1.0f, 0.0f, 0.0f) : glm::vec3(0.0f, 1.0f, 0.0f));

			if (theShapeType == b2Shape::Type::e_polygon)
			{
				b2PolygonShape* thePoly = (b2PolygonShape*)theShape;
				for (int i = 0; i < thePoly->m_count; i++)
				{
					b2Vec2 thisPos = b2Mul(bodyTransform, thePoly->m_vertices[i]);
					AddPointToLine({ thisPos.x, thisPos.y });
				}
				FinishLineLoop();
			}
			else if (theShapeType == b2Shape::Type::e_circle)
			{
				b2CircleShape* theCircle = (b2CircleShape*)theShape;

				if (side == 0)
				{
					this->DrawCircle({ (bodyTransform.p.x - dimensions.x * 0.5f) + dimensions.x * 0.5f,
						(bodyTransform.p.y - (dimensions.y - dimensions.x) * 0.5f) }, theCircle->m_radius);
					side++;
				}
				else
				{
					this->DrawCircle({ (bodyTransform.p.x - dimensions.x * 0.5f) + dimensions.x * 0.5f, 
						(bodyTransform.p.y - (dimensions.y - dimensions.x) * 0.5f) + (dimensions.y - dimensions.x) }, theCircle->m_radius);
				}

				if (body->GetType() != b2BodyType::b2_staticBody)
				{
					glm::vec2 centre = { bodyTransform.p.x, bodyTransform.p.y + theCircle->m_p.y };
					b2Vec2 offset = { theCircle->m_radius, 0 };
					offset = b2Mul(bodyTransform, offset);
					DrawLineSegment(centre, { centre.x + theCircle->m_radius, centre.y });
				}
			}
		}

	}

	void LineRenderer::DrawRawShape(float* data, unsigned int pointCount)
	{
		DrawRawShape(data, pointCount, currentColour);
	}

	void LineRenderer::DrawRawShape(float* data, unsigned int pointCount, glm::vec3 colour)
	{
		for (unsigned int i = 0; i < pointCount - 1; i++)
		{
			positions.push_back(glm::vec2(data[i * 2], data[i * 2 + 1]));
			positions.push_back(glm::vec2(data[(i + 1) * 2], data[(i + 1) * 2 + 1]));
			colours.push_back(colour);
			colours.push_back(colour);
		}

		positions.push_back(glm::vec2(data[0], data[1]));
		positions.push_back(glm::vec2(data[(pointCount - 1) * 2], data[(pointCount - 1) * 2 + 1]));
		colours.push_back(colour);
		colours.push_back(colour);
	}

	void LineRenderer::DrawRigidBody(b2Body* body)
	{
		/* Safe Check. */
		if (body)
		{
			Transform bodyTransform = body->GetTransform();

			for (b2Fixture* thisFixture = body->GetFixtureList(); thisFixture; thisFixture = thisFixture->GetNext())
			{
				b2Shape* theShape = thisFixture->GetShape();
				b2Shape::Type theShapeType = theShape->GetType();

				this->SetColour((body->GetType() == BodyType::b2_staticBody) ? glm::vec3(0.0f, 0.0f, 1.0f) : glm::vec3(0.0f, 1.0f, 0.0f));

				if (theShapeType == b2Shape::Type::e_polygon)
				{
					PolygonShape* thePoly = (PolygonShape*)theShape;
					for (int i = 0; i < thePoly->m_count; i++)
					{
						b2Vec2 thisPos = b2Mul(bodyTransform, thePoly->m_vertices[i]);
						AddPointToLine({ thisPos.x, thisPos.y });

						/* OLD */
						//AddPointToLine({ body->GetPosition().x + thePoly->m_vertices[i].x,  body->GetPosition().y + thePoly->m_vertices[i].y }); 
					}
					FinishLineLoop();
				}
				else if (theShapeType == b2Shape::Type::e_circle)
				{
					CircleShape* theCircle = (CircleShape*)theShape;
					this->DrawCircle({ bodyTransform.p.x, bodyTransform.p.y }, theCircle->m_radius);
					//this->DrawCircle({ theCircle->m_p.x, theCircle->m_p.y }, theCircle->m_radius);
					
					if (body->GetType() != BodyType::b2_staticBody)
					{
						glm::vec2 centre = { bodyTransform.p.x, bodyTransform.p.y + theCircle->m_p.y };
						b2Vec2 offset = { theCircle->m_radius, 0 };
						offset = b2Mul(bodyTransform, offset);
						DrawLineSegment(centre, { centre.x + theCircle->m_radius, centre.y });
					}
				}
			}
		}
	}


	void LineRenderer::UpdateFrame()
	{
	
		if (positions.size() != colours.size())
		{
			std::cout << "ERROR: Somehow, position and colour buffer are different sizes in the line renderer. This should never happen." << std::endl;
			return;
		}
		if (positions.size() > 0)
		{
			Compile();
			Draw();
		}
		Clear();	//It's possible to have done a single point, in which case there's nothing to draw but we do have to set 'lineActive' to false.
	}

	void LineRenderer::Clear()
	{
		lineActive = false;
		positions.clear();
		colours.clear();
	}

	void LineRenderer::Compile()
	{
		glBindBuffer(GL_ARRAY_BUFFER, positionBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * positions.size(), positions.data(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, colourBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * colours.size(), colours.data(), GL_DYNAMIC_DRAW);

	}

	void LineRenderer::Draw()
	{
		glBindBuffer(GL_ARRAY_BUFFER, positionBufferID);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);

		glBindBuffer(GL_ARRAY_BUFFER, colourBufferID);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_LINES, 0, (GLsizei)positions.size());

	}

	LineRenderer::LineRenderer()
	{
		//Do nothing here - initialise separately to avoid calling GL functions before it's set up.
	}

	LineRenderer::~LineRenderer()
	{
		if (initialised)
		{
			glDeleteBuffers(1, &positionBufferID);
			glDeleteBuffers(1, &colourBufferID);
		}
	}
}