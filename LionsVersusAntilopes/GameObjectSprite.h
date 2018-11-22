#pragma once

#include "..\Common\DeviceResources.h"
#include "..\Common\StepTimer.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using namespace Windows::Foundation;

namespace LionsVersusAntilopes
{
	class GameObjectSprite
	{
	public:
		GameObjectSprite(
			const std::shared_ptr<DX::DeviceResources>& deviceResources, 
			std::string file_name, 
			double image_scale = 0.1, 
			Vector2 init_point = Vector2::Zero
		);

		virtual ~GameObjectSprite() {}
		

		void setColor(DirectX::XMVECTOR color);
		void UpdateMovement(DX::StepTimer const& timer);
		virtual void Update(DX::StepTimer const& timer);
		void Render();
		void Reset();
		void setPos(Vector2 pos);
		void setTargetPoint(
			Vector2 pos, 
			double dist = 0.0, 
			Vector2 origin = Vector2::Zero
		);
		Vector2 getPos();
	protected:
		std::vector<GameObjectSprite*> m_gameObjectsCollision;
		// Movement
		double m_speed = 3.;
		double m_cont = 0;
	private:
		// Sprite 
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		Vector2 m_screenPos;
		Vector2 m_origin;
		const std::shared_ptr<DX::DeviceResources> m_deviceResources;
		std::unique_ptr<DirectX::CommonStates> m_states;
		std::string m_fileImageName;
		// Movement
		Vector2 m_targetPoint;
		// Scale Position
		const double m_multScalePosition = 10.0;
		const double m_imageScale = 0.1;
		DirectX::XMVECTOR m_colorSprite = DirectX::Colors::White;
	};
}

