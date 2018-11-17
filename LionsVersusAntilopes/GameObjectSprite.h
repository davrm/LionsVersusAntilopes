#pragma once

#include "..\Common\DeviceResources.h"
#include "..\Common\StepTimer.h"

namespace LionsVersusAntilopes
{
	class GameObjectSprite
	{
	public:
		GameObjectSprite(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~GameObjectSprite();
		void UpdateMovement(DX::StepTimer const& timer);
		virtual void Update(DX::StepTimer const& timer);
		void Render();
		void Reset();
		void SetTargetpoint(DirectX::SimpleMath::Vector2 target);
	private:
		// Sprite 
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		DirectX::SimpleMath::Vector2 m_screenPos;
		DirectX::SimpleMath::Vector2 m_origin;
		const std::shared_ptr<DX::DeviceResources> m_deviceResources;
		std::unique_ptr<DirectX::CommonStates> m_states;
	protected:
		// Movement
		DirectX::SimpleMath::Vector2 m_targetPoint;
		double m_speed = 0.2f;
		double m_cont = 0;
	};
}

