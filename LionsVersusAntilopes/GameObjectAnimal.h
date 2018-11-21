#pragma once
#include "GameObjectSprite.h"
#include "BehaviourTree.h"
#include "Flag.h"

namespace LionsVersusAntilopes
{

	class GameObjectAnimal :
		public GameObjectSprite
	{
	public:
		GameObjectAnimal(
			const std::shared_ptr<DX::DeviceResources>& deviceResources, 
			std::string file_name, 
			double image_scale, 
			DirectX::SimpleMath::Vector2 init_point
		) : GameObjectSprite(deviceResources,file_name,image_scale, init_point) {}

		~GameObjectAnimal();
		GameObjectAnimal * GetNearestAlly();
		bool IsFarFromOtherAnimalsOfMyTeam();
		bool IsOurTeamHavingTheFlag();
		bool IsEnemyTeamHavingTheFlag();
		bool IsThisAnimalHavinfTheFlag();
		Node::Status GoTotheNearestTeammate();
		Node::Status GotoTheEnemyFlag();
		Node::Status CaptureEnemyFlag();
		Node::Status GoToOurFlag();
		Node::Status AttackEnemy();

		void setEnemyFlag(Flag * flag);
		void setTeamFlag(Flag * flag);
		void setAllies(std::vector<GameObjectAnimal*> allies);
		void setEnemies(std::vector<GameObjectAnimal*> enemies);
	private:
		double m_life;
		double m_damage;
		const double m_distanceWhenAnimalIsFar = 20.0;
		const double m_distanceToApproach = 3.0;
		const double m_distanceToComeClose = 6.0;
		const double m_distanceToCaptureFlag = 2.0;
		bool m_hasTheFlag = false;
		int m_numberOfEnemiesAttacking;
		int m_minNumberEnemiesForDamage;
		std::vector<GameObjectAnimal*> m_alliesInView;
		std::vector<GameObjectAnimal*> m_enemiesInView;
		Flag* m_myFlag;
		Flag* m_enemyFlag;
	};
}

