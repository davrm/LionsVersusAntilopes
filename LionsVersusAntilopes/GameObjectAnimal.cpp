#include "pch.h"
#include "GameObjectAnimal.h"

using namespace LionsVersusAntilopes;

GameObjectAnimal::~GameObjectAnimal()
{
}

// Get the Ally who is closer to this Animal 
GameObjectAnimal* GameObjectAnimal::GetNearestAlly() {
	GameObjectAnimal* result = nullptr;
	double shorter_distance = std::numeric_limits<double>::infinity();
	for (std::vector<GameObjectAnimal*>::iterator it = m_alliesInView.begin(); it != m_alliesInView.end(); it++) {
		if (shorter_distance > DirectX::SimpleMath::Vector2::Distance((*it)->GetPos(),GetPos())) 
			result = *it;
	}
	return result;
}

// Returns true if this animal is far from its teammates
bool GameObjectAnimal::IsFarFromOtherAnimalsOfMyTeam()
{
	GameObjectAnimal* nearest_ally = GetNearestAlly();
	if (nearest_ally == nullptr) return false;
	if(m_distanceWhenAnimalIsFar < DirectX::SimpleMath::Vector2::Distance(nearest_ally->GetPos(), GetPos())) return true;
	else return false;
}

// Returns true if an ally have the enemy flag
bool GameObjectAnimal::IsOurTeamHavingTheFlag()
{
	for (std::vector<GameObjectAnimal*>::iterator it = m_alliesInView.begin(); it != m_alliesInView.end(); it++) {
		if ((*it)->m_hasTheFlag) return true;
	}
	return false;
}

// Return true if an enemy have the team flag
bool GameObjectAnimal::IsEnemyTeamHavingTheFlag()
{
	for (std::vector<GameObjectAnimal*>::iterator it = m_enemiesInView.begin(); it != m_enemiesInView.end(); it++) {
		if ((*it)->m_hasTheFlag) return true;
	}
	return false;
}

// Returns true if this animal have the flag
bool GameObjectAnimal::IsThisAnimalHavinfTheFlag()
{
	return m_hasTheFlag;
}

Node::Status GameObjectAnimal::GoTotheNearestTeammate() {
	GameObjectAnimal* nearest_ally = GetNearestAlly();
	if (m_distanceToComeClose > DirectX::SimpleMath::Vector2::Distance(nearest_ally->GetPos(), GetPos()))
		return Node::Status::Ok;
	else {
		setTargetPoint(nearest_ally->GetPos(), m_distanceToApproach, GetPos());
		return Node::Status::Active;
	}
}

Node::Status GameObjectAnimal::GotoTheEnemyFlag() {

	DirectX::SimpleMath::Vector2 flag_pos = m_enemyFlag->GetPos();
	double dist = DirectX::SimpleMath::Vector2::Distance(GetPos(), flag_pos);
	if (dist > m_distanceToCaptureFlag) {
		setTargetPoint(flag_pos);
		return Node::Status::Active;
	}
	else
	{
		return Node::Status::Ok;
	}
	

	return Node::Status::Fail;
}

Node::Status GameObjectAnimal::CaptureEnemyFlag() {
	return Node::Status::Fail;
}

Node::Status GameObjectAnimal::GoToOurFlag() {
	return Node::Status::Fail;
}

Node::Status GameObjectAnimal::AttackEnemy() {
	return Node::Status::Fail;
}

void GameObjectAnimal::setEnemyFlag(Flag * flag)
{
	m_enemyFlag = flag;
}

void GameObjectAnimal::setTeamFlag(Flag * flag)
{
	m_myFlag = flag;
}

void GameObjectAnimal::setAllies(std::vector<GameObjectAnimal*> allies)
{
	m_alliesInView = allies;
}

void GameObjectAnimal::setEnemies(std::vector<GameObjectAnimal*> enemies)
{
	m_enemiesInView = enemies;
}
