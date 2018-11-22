#include "pch.h"
#include "GameObjectSprite.h"
#include "Common\DirectXHelper.h"

using namespace LionsVersusAntilopes;


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

	// Attempt to put a type of physics in the game object sprite
	// Iterate all the Objects that we want to have a type of collider
	// If they are at a certain distance forces these objects away
	// Calculates all the repulsion vectors and add it

	Vector2 sum = Vector2::Zero;
	for (std::vector<GameObjectSprite*>::iterator it = m_gameObjectsCollision.begin(); it != m_gameObjectsCollision.end(); it++)
	{
		if (Vector2::Distance((*it)->getPos(), this->getPos()) < 4 && (*it) != this)
		{
			Vector2 v = Vector2(this->getPos().x - (*it)->getPos().x, this->getPos().y - (*it)->getPos().y);
			v.Normalize();
			sum += v;
		}
	}

	// Calculate the vector to the Objective and add it

	Vector2 v = Vector2(m_targetPoint.x - m_screenPos.x, m_targetPoint.y - m_screenPos.y);
	v.Normalize();
	sum += v;
	sum.Normalize();

	// If the target Point is more than 2 pixel of distance, update new position
	if(Vector2::Distance(m_screenPos, m_targetPoint)>2) m_screenPos += sum*m_speed;
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
		m_targetPoint = ((dir * dist)+pos) * m_multScalePosition;
	}
}

DirectX::SimpleMath::Vector2 LionsVersusAntilopes::GameObjectSprite::getPos()
{
	return m_screenPos / m_multScalePosition;
}

