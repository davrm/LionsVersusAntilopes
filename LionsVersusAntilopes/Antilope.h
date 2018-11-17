#pragma once
#include "GameObjectAnimal.h"
namespace LionsVersusAntilopes
{
	class Antilope :
		public GameObjectAnimal
	{
	public:
		Antilope(const std::shared_ptr<DX::DeviceResources>& deviceResources) : GameObjectAnimal(deviceResources) {}
		~Antilope();
		void Update(DX::StepTimer const& timer) override;
	};
}

