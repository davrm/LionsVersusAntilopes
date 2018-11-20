#pragma once
#include "GameObjectAnimal.h"

namespace LionsVersusAntilopes
{
	class Antilope : public GameObjectAnimal
	{
	public:
		Antilope(
			const std::shared_ptr<DX::DeviceResources>& deviceResources, 
			std::string file_name,
			double image_scale,
			DirectX::SimpleMath::Vector2 init_point
		) : GameObjectAnimal(deviceResources, file_name, image_scale, init_point) 
		{
			InitBehaviourTree();
		}
		~Antilope();
		void Update(DX::StepTimer const& timer) override;

	private:
		BehaviourTree * m_tree;
		void InitBehaviourTree();


	};
}

