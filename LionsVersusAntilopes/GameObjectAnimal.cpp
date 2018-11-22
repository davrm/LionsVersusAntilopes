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
		if (shorter_distance > Vector2::Distance((*it)->getPos(),getPos())) 
			result = *it;
	}
	return result;
}

// Get the Enemy who is closer to this Animal 
GameObjectAnimal* GameObjectAnimal::GetNearesEnemy() {
	GameObjectAnimal* result = nullptr;
	double shorter_distance = std::numeric_limits<double>::infinity();
	for (std::vector<GameObjectAnimal*>::iterator it = m_enemiesInView.begin(); it != m_enemiesInView.end(); it++) {
		if (shorter_distance > Vector2::Distance((*it)->getPos(), getPos()))
			result = *it;
	}
	return result;
}

// Returns true if this animal is far from its teammates
bool GameObjectAnimal::IsFarFromOtherAnimalsOfMyTeam()
{
	GameObjectAnimal* nearest_ally = GetNearestAlly();
	if (nearest_ally == nullptr) return false;
	if(m_distanceWhenAnimalIsFar < Vector2::Distance(nearest_ally->getPos(), getPos())) return true;
	else return false;
}


// Returns true if this animal is near an Enemy
bool GameObjectAnimal::IsNearFromEnemies()
{
	GameObjectAnimal* nearest_enemy = GetNearesEnemy();
	if (nearest_enemy == nullptr) return false;
	if (m_distanceWhenEnemieIsNear > Vector2::Distance(nearest_enemy->getPos(), getPos())) return true;
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
	if (m_distanceToComeClose > Vector2::Distance(nearest_ally->getPos(), getPos()))
		return Node::Status::Ok;
	else {
		setTargetPoint(nearest_ally->getPos(), m_distanceToApproach, getPos());
		return Node::Status::Active;
	}
}

Node::Status GameObjectAnimal::GotoTheEnemyFlag() {

	Vector2 flag_pos = m_enemyFlag->getPos();
	double dist = Vector2::Distance(getPos(), flag_pos);
	if (dist > m_distanceToCaptureFlag && m_enemyFlag->getTransporter() == nullptr) {
		setTargetPoint(flag_pos);
		return Node::Status::Active;
	}
	else if (m_enemyFlag->getTransporter() == nullptr || m_enemyFlag->getTransporter() == this)
	{
		m_enemyFlag->SetTransporter(this);
		m_hasTheFlag = true;
		return Node::Status::Ok;	
	}
	else return Node::Status::Fail;
}

Node::Status GameObjectAnimal::CaptureEnemyFlag() {
	// TODO Drop Flag, getPos of the origin not the actual
	Vector2 flag_pos = m_myFlag->getPos();

	double dist = Vector2::Distance(getPos(), flag_pos);
	if (dist > m_distanceToCaptureFlag) {
		setTargetPoint(flag_pos);
		return Node::Status::Active;
	}
	else if (m_enemyFlag->getTransporter() == this)
	{

		return Node::Status::Ok;
	}
	else return Node::Status::Fail;
}

Node::Status GameObjectAnimal::DefendTheTransporter() {
	Vector2 flag_pos = m_enemyFlag->getPos();
	double dist = Vector2::Distance(getPos(), flag_pos);

	if (dist > m_distanceToDefendTransporter) {
		setTargetPoint(flag_pos);
		return Node::Status::Active;
	}
	else
	{
		return Node::Status::Ok;
	}


}

Node::Status GameObjectAnimal::GoToOurFlag() {
	Vector2 flag_pos = m_enemyFlag->getPos();
	double dist = Vector2::Distance(getPos(), flag_pos);

	if (dist > m_distanceToDefendTransporter) {
		setTargetPoint(flag_pos);
		return Node::Status::Active;
	}
	else 
	{
		return Node::Status::Ok;
	}


}

Node::Status GameObjectAnimal::AttackEnemy() {

	GameObjectAnimal * near_enemy = GetNearesEnemy();

	if (m_timeNextAttack <= 0 && !near_enemy->m_isDead) {
		near_enemy->InflictDamage(m_damage);
		ResetAttackTime();
		return Node::Status::Active;
	}
	else if(m_timeNextAttack > 0)
	{
		return Node::Status::Active;
	}
	else if (near_enemy->m_isDead)
	{
		return Node::Status::Ok;
	}
	else return Node::Status::Fail;

}

void GameObjectAnimal::InflictDamage(double damage) {
	m_life -= damage;
	if (m_life < 0) 
		m_isDead = true;
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
	m_gameObjectsCollision.insert(m_gameObjectsCollision.end(),allies.begin(),allies.end());
}

void GameObjectAnimal::setEnemies(std::vector<GameObjectAnimal*> enemies)
{
	m_enemiesInView = enemies;
	m_gameObjectsCollision.insert(m_gameObjectsCollision.end(), enemies.begin(), enemies.end());
}
