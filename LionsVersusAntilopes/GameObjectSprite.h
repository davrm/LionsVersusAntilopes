#pragma once

#include "..\Common\DeviceResources.h"
#include "..\Common\StepTimer.h"

namespace LionsVersusAntilopes
{
	class GameObjectSprite
	{
	public:
		GameObjectSprite(
			const std::shared_ptr<DX::DeviceResources>& deviceResources, 
			std::string file_name, 
			double image_scale = 0.1, 
			DirectX::SimpleMath::Vector2 init_point = DirectX::SimpleMath::Vector2::Zero
		);
		void setColor(DirectX::XMVECTOR color);
		void UpdateMovement(DX::StepTimer const& timer);
		virtual void Update(DX::StepTimer const& timer);
		void Render();
		void Reset();
		void SetTargetpoint(DirectX::SimpleMath::Vector2 target);
		void SetPos(DirectX::SimpleMath::Vector2 pos);
		void SetTargetPoint(
			DirectX::SimpleMath::Vector2 pos, 
			double dist = 0.0, 
			DirectX::SimpleMath::Vector2 origin = DirectX::SimpleMath::Vector2::Zero
		);
		DirectX::SimpleMath::Vector2 GetPos();
	protected:
		// Movement
		double m_speed = 0.2f;
		double m_cont = 0;
	private:
		// Sprite 
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		DirectX::SimpleMath::Vector2 m_screenPos;
		DirectX::SimpleMath::Vector2 m_origin;
		const std::shared_ptr<DX::DeviceResources> m_deviceResources;
		std::unique_ptr<DirectX::CommonStates> m_states;
		std::string m_fileImageName;
		// Movement
		DirectX::SimpleMath::Vector2 m_targetPoint;
		// Scale Position
		const double m_multScalePosition = 10.0;
		const double m_imageScale = 0.1;
		DirectX::XMVECTOR m_colorSprite = DirectX::Colors::White;
	};
}

