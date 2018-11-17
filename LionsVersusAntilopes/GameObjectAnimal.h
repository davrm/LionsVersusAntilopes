#pragma once
#include "GameObjectSprite.h"
#include "Flag.h"

namespace LionsVersusAntilopes
{

	class GameObjectAnimal :
		public GameObjectSprite
	{
	public:
		GameObjectAnimal(const std::shared_ptr<DX::DeviceResources>& deviceResources, std::string file_name) : GameObjectSprite(deviceResources,file_name) {}
		~GameObjectAnimal();
	private:
		double m_life;
		double m_damage;
		int m_numberOfEnemiesAttacking;
		int m_minNumberEnemiesForDamage;
		std::vector<GameObjectAnimal*> m_alliesInView;
		std::vector<GameObjectAnimal*> m_enemiesInView;
		Flag* m_myFlag;
		Flag* m_enemyFlag;
	};
}

