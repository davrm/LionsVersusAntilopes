#include "pch.h"
#include "Flag.h"

using namespace LionsVersusAntilopes;


Flag::~Flag()
{
}

void Flag::Update(DX::StepTimer const & timer)
{
	if (m_isTransported) setTargetPoint(m_transporter->GetPos(), 3, GetPos());
	else setTargetPoint(m_originPoint);
}

bool Flag::IsInspawn()
{
	return DirectX::SimpleMath::Vector2::Distance(m_originPoint,GetPos()) < 3;
}

void Flag::SetTransporter(GameObjectSprite * transporter)
{
	m_transporter = transporter;
	m_isTransported = true;
}

void Flag::Release()
{
	m_transporter = nullptr;
	m_isTransported = true;
}
