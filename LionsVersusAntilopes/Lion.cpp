#include "pch.h"
#include "Lion.h"

using namespace LionsVersusAntilopes;


Lion::~Lion()
{
}

void Lion::Update(DX::StepTimer const & timer)
{
	float red = m_life / 100.0;
	if(m_life < 50.0)setColor(DirectX::Colors::Blue);
}
