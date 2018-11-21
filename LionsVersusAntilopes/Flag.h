#pragma once
#include "GameObjectSprite.h"
namespace LionsVersusAntilopes
{
	class Flag :
		public GameObjectSprite
	{
	public:
		Flag(
			const std::shared_ptr<DX::DeviceResources>& deviceResources, 
			std::string file_name, double image_scale, 
			DirectX::SimpleMath::Vector2 origin_point
		) : GameObjectSprite(deviceResources,file_name, image_scale, origin_point), m_originPoint(origin_point){}
		~Flag();
		void Update(DX::StepTimer const& timer) override;
		bool IsInspawn();
		void SetTransporter(GameObjectSprite* transporter);
		GameObjectSprite* getTransporter() { return m_transporter; }
		void Release();
	

	private:
		DirectX::SimpleMath::Vector2 m_originPoint;
		GameObjectSprite*  m_transporter;
		bool m_isTransported;

	};
}

