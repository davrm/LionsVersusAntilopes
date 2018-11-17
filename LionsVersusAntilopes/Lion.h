#pragma once
#include "GameObjectAnimal.h"

namespace LionsVersusAntilopes
{
	class Lion : public GameObjectAnimal
	{
	public:
		Lion(const std::shared_ptr<DX::DeviceResources>& deviceResources, std::string file_name) : GameObjectAnimal(deviceResources, file_name) {}
		~Lion();
		void Update(DX::StepTimer const& timer) override;
	};
}

