#include "pch.h"
#include "GameManager.h"

using namespace LionsVersusAntilopes;

GameManager::GameManager(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{

	int num_antilopes = std::stoi(DataLoader::getInstance()->getNumbersAnimalAttribute("antilopes"));
	int num_lions = std::stoi(DataLoader::getInstance()->getNumbersAnimalAttribute("lions"));

	DirectX::SimpleMath::Vector2 m_originPointFlagLion = DirectX::SimpleMath::Vector2(500, 0);
	DirectX::SimpleMath::Vector2 m_originPointFlagAntilope = DirectX::SimpleMath::Vector2(-500, 0);

	Flag * m_flagLion = new Flag(deviceResources, DataLoader::getInstance()->getFlagAttribute("image"), 
		std::stod(DataLoader::getInstance()->getFlagAttribute("imageScale")), m_originPointFlagLion);
	m_objectsToRender.push_back(m_flagLion);

	Flag * m_flagAntilope = new Flag(deviceResources, DataLoader::getInstance()->getFlagAttribute("image"),
		std::stod(DataLoader::getInstance()->getFlagAttribute("imageScale")), m_originPointFlagAntilope);
	m_objectsToRender.push_back(m_flagAntilope);

}

GameManager * GameManager::m_instance = 0;

GameManager * GameManager::getInstance(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{
	if (m_instance == 0) m_instance = new GameManager(deviceResources);
	return m_instance;
}

void LionsVersusAntilopes::GameManager::Update(DX::StepTimer const & timer)
{
}

void LionsVersusAntilopes::GameManager::Render()
{
}

void LionsVersusAntilopes::GameManager::Reset()
{
}
