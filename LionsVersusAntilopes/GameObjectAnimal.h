#pragma once
#include "GameObjectSprite.h"

namespace LionsVersusAntilopes
{
	class GameObjectAnimal :
		public GameObjectSprite
	{
	public:
		GameObjectAnimal(const std::shared_ptr<DX::DeviceResources>& deviceResources) : GameObjectSprite(deviceResources) {}
		~GameObjectAnimal();
	};
}

