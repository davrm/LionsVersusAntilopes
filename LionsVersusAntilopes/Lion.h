#pragma once
#include "GameObjectAnimal.h"

namespace LionsVersusAntilopes
{
	class Lion : public GameObjectAnimal
	{
	public:
		Lion(const std::shared_ptr<DX::DeviceResources>& deviceResources) : GameObjectAnimal(deviceResources) {}
		~Lion();
		void Update(DX::StepTimer const& timer) override;
	};
}

