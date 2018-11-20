#pragma once
#include "GameObjectAnimal.h"

namespace LionsVersusAntilopes
{
	class Lion : public GameObjectAnimal
	{
	public:
		Lion(
			const std::shared_ptr<DX::DeviceResources>& deviceResources,
			std::string file_name,
			double image_scale,
			DirectX::SimpleMath::Vector2 init_point
		) : GameObjectAnimal(deviceResources, file_name, image_scale, init_point) {}

		~Lion();
		void Update(DX::StepTimer const& timer) override;
	};
}

