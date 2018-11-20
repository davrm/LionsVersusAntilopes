#include "pch.h"
#include "GameManager.h"

using namespace LionsVersusAntilopes;

GameManager::GameManager(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{

	DataLoader * d_loader = DataLoader::getInstance();

	int num_antilopes = std::stoi(d_loader->getNumbersAnimalAttribute("antilopes"));
	int num_lions = std::stoi(d_loader->getNumbersAnimalAttribute("lions"));

	DirectX::SimpleMath::Vector2 m_originPointFlagLion = DirectX::SimpleMath::Vector2(50, 0);
	DirectX::SimpleMath::Vector2 m_originPointFlagAntilope = DirectX::SimpleMath::Vector2(-50, 0);



	m_lionTeamFlag = new Flag(deviceResources, d_loader->getFlagAttribute("image"),
		std::stod(d_loader->getFlagAttribute("imageScale")), m_originPointFlagLion);
	m_objectsToRender.push_back(m_lionTeamFlag);

	m_antilopeTeamFlag = new Flag(deviceResources, d_loader->getFlagAttribute("image"),
		std::stod(d_loader->getFlagAttribute("imageScale")), m_originPointFlagAntilope);
	m_objectsToRender.push_back(m_antilopeTeamFlag);

	m_antilopeTeamFlag->setColor(DirectX::Colors::Blue);
	m_lionTeamFlag->setColor(DirectX::Colors::Red);

	for (int i = num_antilopes; i--;) {
		Antilope * temp_antilope = new Antilope(deviceResources, d_loader->getAntilopeAttribute("image"),
			std::stod(d_loader->getAntilopeAttribute("imageScale")), m_originPointFlagAntilope);
		temp_antilope->setEnemyFlag(m_lionTeamFlag);
		temp_antilope->setTeamFlag(m_antilopeTeamFlag);
		m_objectsToRender.push_back(temp_antilope);
		m_antilopeTeam.push_back(temp_antilope);
	}

	for (int i = num_lions; i--;) {
		Lion * temp_lion = new Lion(deviceResources, d_loader->getLionAttribute("image"),
			std::stod(d_loader->getLionAttribute("imageScale")), m_originPointFlagLion);
		temp_lion->setEnemyFlag(m_antilopeTeamFlag);
		temp_lion->setTeamFlag(m_lionTeamFlag);
		m_objectsToRender.push_back(temp_lion);
		m_lionTeam.push_back(temp_lion);
	}


	for (std::vector<GameObjectAnimal *>::iterator it = m_antilopeTeam.begin(); it != m_antilopeTeam.end(); ++it) {
		std::vector<GameObjectAnimal*> tempCopy(m_antilopeTeam);
		tempCopy.erase(std::find(tempCopy.begin(), tempCopy.end(), *it));
		(*it)->setAllies(tempCopy);
		(*it)->setEnemies(m_lionTeam);
	}

	for (std::vector<GameObjectAnimal *>::iterator it = m_lionTeam.begin(); it != m_lionTeam.end(); ++it) {
		std::vector<GameObjectAnimal*> tempCopy(m_lionTeam);
		tempCopy.erase(std::find(tempCopy.begin(), tempCopy.end(), *it));
		(*it)->setAllies(tempCopy);
		(*it)->setEnemies(m_antilopeTeam);
	}

}

GameManager * GameManager::m_instance = 0;

GameManager * GameManager::getInstance(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{
	if (m_instance == 0) m_instance = new GameManager(deviceResources);
	return m_instance;
}

void LionsVersusAntilopes::GameManager::Update(DX::StepTimer const & timer)
{
	for (std::vector<GameObjectSprite*>::iterator it = m_objectsToRender.begin(); it != m_objectsToRender.end(); it++)
	{
		(*it)->Update(timer);
	}
}

void LionsVersusAntilopes::GameManager::Render()
{
	for (std::vector<GameObjectSprite*>::iterator it = m_objectsToRender.begin(); it != m_objectsToRender.end(); it++)
	{
		(*it)->Render();
	}
}

void LionsVersusAntilopes::GameManager::Reset()
{
	for (std::vector<GameObjectSprite*>::iterator it = m_objectsToRender.begin(); it != m_objectsToRender.end(); it++)
	{
		(*it)->Reset();
	}
}
