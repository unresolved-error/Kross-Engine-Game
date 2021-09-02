#pragma once

#include <Kross.h>

using namespace Kross;

class Button : public Script
{
public:
	Button() :
		renderer(nullptr),
		rigidBody(nullptr)
	{
		/* Every Script Must do this! */
		m_Name = "Button";
	};
	~Button() {};

	SpriteRenderer* renderer;
	Rigidbody2D* rigidBody;
	bool isPressed = false;
	

	float weightRequired = 1.0f;

	Script* Duplicate() override
	{
		return KROSS_NEW Button();
	}

	void Start() override
	{
		renderer = GetComponent<SpriteRenderer>();
		rigidBody = GetComponent<Rigidbody2D>();
	}

	void Update() override
	{
		if (isPressed) 
		{ 
			return; 
		}
		CheckIfPressed();
		if (isPressed) 
		{
			Debug::Log("Button has been pressed.");
		}
	}

	void CheckIfPressed() 
	{
		std::vector<Body*> surroundingBodies = rigidBody->GetSurroundingObjects(1.0f, rigidBody->GetBody());
		float weightAccumulator = 0.0f;
		for (int i = 0; i < surroundingBodies.size(); i++)
		{
			weightAccumulator += surroundingBodies[i]->GetMass();
		}
		if (weightAccumulator >= weightRequired)
		{
			isPressed = true;
		}

	}




};