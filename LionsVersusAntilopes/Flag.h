#pragma once
#include "GameObjectSprite.h"
namespace LionsVersusAntilopes
{
	class Flag :
		public GameObjectSprite
	{
	public:
		Flag(const std::shared_ptr<DX::DeviceResources>& deviceResources) : GameObjectSprite(deviceResources) {}
		~Flag();
		void Update(DX::StepTimer const& timer) override;
	};
}

