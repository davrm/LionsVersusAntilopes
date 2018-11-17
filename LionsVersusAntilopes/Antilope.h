#pragma once
#include "GameObjectAnimal.h"
namespace LionsVersusAntilopes
{
	class Antilope :
		public GameObjectAnimal
	{
	public:
		Antilope(const std::shared_ptr<DX::DeviceResources>& deviceResources, std::string file_name) : GameObjectAnimal(deviceResources, file_name) {}
		~Antilope();
		void Update(DX::StepTimer const& timer) override;
	};
}

