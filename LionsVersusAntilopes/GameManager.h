#pragma once
#include "Antilope.h"
#include "Lion.h"
#include "Flag.h"
#include "DataLoader.h"

namespace LionsVersusAntilopes
{
	class GameManager
	{
	public:
		static GameManager * getInstance(const std::shared_ptr<DX::DeviceResources>& deviceResources = nullptr);
		void Update(DX::StepTimer const & timer);
		void Render();
		void Reset();
	private:
		static GameManager * m_instance;
		std::vector<GameObjectSprite*> m_objectsToRender;
		std::vector<GameObjectAnimal*> m_lionTeam;
		std::vector<GameObjectAnimal*> m_antilopeTeam;
		Flag * m_lionTeamFlag;
		Flag * m_antilopeTeamFlag;

		GameManager(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void InitObjects(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		std::vector<DirectX::SimpleMath::Vector2> getSpwanPoints(int num_spawns, double dist, DirectX::SimpleMath::Vector2 center, double offset_angle);
	};
}

