#include "pch.h"
#include "GameObjectSprite.h"
#include "Common\DirectXHelper.h"

using namespace Windows::Foundation;
using namespace LionsVersusAntilopes;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

GameObjectSprite::GameObjectSprite(const std::shared_ptr<DX::DeviceResources>& deviceResources, 
	std::string file_name, double image_scale, Vector2 init_point):
	m_deviceResources(deviceResources) , m_fileImageName(file_name) , m_imageScale(image_scale)
{	
	// std::string to std::wstring for conversion to const wchar_t *
	std::wstring widestr = std::wstring(m_fileImageName.begin(), m_fileImageName.end());
	// Create Sprite
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), widestr.c_str(), nullptr,
			m_texture.ReleaseAndGetAddressOf()));
	m_spriteBatch = std::make_unique<SpriteBatch>(m_deviceResources->GetD3DDeviceContext());

	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), widestr.c_str(),
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
	setPos(init_point);
	// Get State for Alpha Mode in the Sprite
	m_states = std::make_unique<CommonStates>(m_deviceResources->GetD3DDevice());
}


void GameObjectSprite::UpdateMovement(DX::StepTimer const & timer)
{
	Vector2 v = Vector2(m_targetPoint.x - m_screenPos.x, m_targetPoint.y - m_screenPos.y);
	v.Normalize();
	m_screenPos += v*m_speed;
}

void GameObjectSprite::Update(DX::StepTimer const & timer)
{
}

void GameObjectSprite::setColor(DirectX::XMVECTOR color)
{
	m_colorSprite = color;
}

void GameObjectSprite::Render()
{
	// Calculate Offset point if the window change size
	Size outputSize = m_deviceResources->GetOutputSize();
	DirectX::SimpleMath::Vector2 offset = Vector2(outputSize.Width / 2.f, outputSize.Height / 2.f);
	// Render Of the Sprite
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());
	m_spriteBatch->Draw(m_texture.Get(), offset + m_screenPos, nullptr, m_colorSprite,
		0.f, m_origin, m_imageScale);
	m_spriteBatch->End();
}

void GameObjectSprite::Reset()
{
	m_texture.Reset();
	m_spriteBatch.reset();
	m_states.reset();
}

void LionsVersusAntilopes::GameObjectSprite::setPos(DirectX::SimpleMath::Vector2 pos)
{
	m_screenPos = pos * m_multScalePosition;
}

void LionsVersusAntilopes::GameObjectSprite::setTargetPoint(DirectX::SimpleMath::Vector2 pos, double dist, DirectX::SimpleMath::Vector2 origin)
{
	if (dist == 0) m_targetPoint = pos * m_multScalePosition;
	else {
		DirectX::SimpleMath::Vector2 dir = DirectX::SimpleMath::Vector2(origin.x - pos.x, origin.y - pos.y);
		dir.Normalize();
		m_targetPoint = dir * dist;
	}
}

DirectX::SimpleMath::Vector2 LionsVersusAntilopes::GameObjectSprite::GetPos()
{
	return m_screenPos / m_multScalePosition;
}

