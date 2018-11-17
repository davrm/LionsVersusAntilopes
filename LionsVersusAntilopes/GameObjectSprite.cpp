#include "pch.h"
#include "GameObjectSprite.h"
#include "Common\DirectXHelper.h"

using namespace Windows::Foundation;
using namespace LionsVersusAntilopes;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

GameObjectSprite::GameObjectSprite(const std::shared_ptr<DX::DeviceResources>& deviceResources):m_deviceResources(deviceResources)
{	
	// Create Sprite
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"antilope.png", nullptr,
			m_texture.ReleaseAndGetAddressOf()));
	m_spriteBatch = std::make_unique<SpriteBatch>(m_deviceResources->GetD3DDeviceContext());

	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"antilope.png",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));
	// Get Origin Point for the Sprite
	ComPtr<ID3D11Texture2D> cat;
	DX::ThrowIfFailed(resource.As(&cat));
	CD3D11_TEXTURE2D_DESC catDesc;
	cat->GetDesc(&catDesc);
	m_origin.x = float(catDesc.Width / 2);
	m_origin.y = float(catDesc.Height / 2);
	// Initial Point
	m_screenPos.x = 0;
	m_screenPos.y = 0;
	// Get State for Alpha Mode in the Sprite
	m_states = std::make_unique<CommonStates>(m_deviceResources->GetD3DDevice());
}

GameObjectSprite::~GameObjectSprite()
{
}

void GameObjectSprite::UpdateMovement(DX::StepTimer const & timer)
{
	m_screenPos = Vector2::Lerp(m_screenPos, m_targetPoint, m_speed * timer.GetElapsedSeconds());
}

void GameObjectSprite::Update(DX::StepTimer const & timer)
{
}

void GameObjectSprite::Render()
{
	// Calculate Offset point if the window change size
	Size outputSize = m_deviceResources->GetOutputSize();
	DirectX::SimpleMath::Vector2 offset = Vector2(outputSize.Width / 2.f, outputSize.Height / 2.f);
	// Render Of the Sprite
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());
	m_spriteBatch->Draw(m_texture.Get(), offset + m_screenPos, nullptr, Colors::White,
		0.f, m_origin,0.1f);
	m_spriteBatch->End();
}

void GameObjectSprite::Reset()
{
	m_texture.Reset();
	m_spriteBatch.reset();
	m_states.reset();
}

void GameObjectSprite::SetTargetpoint(Vector2 target)
{
	m_targetPoint = target;
}

