#pragma once

#include <Kross.h>

using namespace Kross;

class EndLevel : public Script
{
public:
	EndLevel()
	{
		/* Every Script Must do this! */
		m_Name = "EndLevel";
	};
	~EndLevel() {};
	Object* sceneCam;
	Transform2D* transform;
	Object* player;
	Object* EndText;
	TextRenderer* renderer;

	Script* Duplicate() override
	{
		return KROSS_NEW EndLevel();
	}


	void Start() override
	{
		renderer = GetComponent<TextRenderer>();
		player = SceneManager::GetCurrentScene()->FindObject("Player");
	}


	void Update() override 
	{
		
	}


};
