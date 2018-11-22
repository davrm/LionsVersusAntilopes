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
			Vector2 init_point

		) : GameObjectSprite(deviceResources,file_name,image_scale, init_point) 
		{
			
		}

		~GameObjectAnimal();
		GameObjectAnimal * GetNearestAlly();
		GameObjectAnimal * GetNearesEnemy();
		bool IsFarFromOtherAnimalsOfMyTeam();
		bool IsNearFromEnemies();
		bool IsOurTeamHavingTheFlag();
		bool IsEnemyTeamHavingTheFlag();
		bool IsThisAnimalHavinfTheFlag();
		Node::Status GoTotheNearestTeammate();
		Node::Status GotoTheEnemyFlag();
		Node::Status CaptureEnemyFlag();
		Node::Status DefendTheTransporter();
		Node::Status GoToOurFlag();
		Node::Status AttackEnemy();

		void InflictDamage(double damage);

		void setEnemyFlag(Flag * flag);
		void setTeamFlag(Flag * flag);
		void setAllies(std::vector<GameObjectAnimal*> allies);
		void setEnemies(std::vector<GameObjectAnimal*> enemies);
		void ResetAttackTime() { m_timeNextAttack = m_timeBetweenAttacks; }

		//// Getters 
		double getLife() { return m_life; }
		double getDamage() { return m_damage; }



	protected:
		double m_life = 100.0;
		double m_damage = 10.0;
		double m_timeNextAttack = 3.0;
		const double m_timeBetweenAttacks = 3.0;
		const double m_distanceWhenAnimalIsFar = 20.0;
		const double m_distanceToApproach = 3.0;
		const double m_distanceToComeClose = 6.0;
		const double m_distanceToCaptureFlag = 2.0;
		const double m_distanceWhenEnemieIsNear = 10.0;
		const double m_distanceToDefendTransporter = 5.0;
		bool m_isDead = false;
		bool m_hasTheFlag = false;
		int m_numberOfEnemiesAttacking;
		int m_minNumberEnemiesForDamage;
		std::vector<GameObjectAnimal*> m_alliesInView;
		std::vector<GameObjectAnimal*> m_enemiesInView;
		Flag* m_myFlag;
		Flag* m_enemyFlag;
	};
}

