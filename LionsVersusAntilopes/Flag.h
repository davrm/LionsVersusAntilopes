#pragma once
#include "GameObjectSprite.h"
namespace LionsVersusAntilopes
{
	class Flag :
		public GameObjectSprite
	{
	public:
		Flag(const std::shared_ptr<DX::DeviceResources>& deviceResources, std::string file_name) : GameObjectSprite(deviceResources,file_name) {}
		~Flag();
		void Update(DX::StepTimer const& timer) override;
		bool IsInspawn();
		void SetTransporter(GameObjectSprite* transporter);
		void Release();

	private:
		DirectX::SimpleMath::Vector2 m_originPoint;
		GameObjectSprite*  m_transporter;
		bool m_isTransported;

	};
}

