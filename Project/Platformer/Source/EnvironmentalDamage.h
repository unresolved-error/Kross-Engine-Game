#pragma once

#include <Kross.h>

#include "HealthManager.h"

using namespace Kross;

class EnvironmentalDamage : public Script
{
private:
	float baseHotLiquidsDamage;

	HealthManager* healthManager = nullptr;

	Object* level;
	Object* player;

	Rigidbody2D* rigidbody;

public:
	EnvironmentalDamage() :
		baseHotLiquidsDamage	(1.0f),
		level					(nullptr),
		player					(nullptr),
		rigidbody				(nullptr)
	{
		m_Name = "EnvironmentalDamage";
	}
	~EnvironmentalDamage() {}

	Script* Duplicate() override
	{
		return KROSS_NEW EnvironmentalDamage();
	}

	void Start() override
	{
		level = SceneManager::GetScene()->FindObject("Level");
		player = SceneManager::GetScene()->FindObject("Player");

		healthManager = level->GetComponent<HealthManager>();
		rigidbody = player->GetComponent<Rigidbody2D>();
	}

	void Update() override
	{
		HotLiquidDamage(player);
	}

	void HotLiquidDamage(Object* obj)
	{
		if (rigidbody->GetCloseParticles().size() > 25)
		{
			healthManager->DoDamage(obj, baseHotLiquidsDamage);
		}
		//Debug::LogLine("Current player health: " + std::to_string((float)healthManager->m_Health[0]->GetHealth()));
	}

};