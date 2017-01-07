#include "Flash.h"
#include "Sprite.h"
#include <SimpleMath.h>
#include <DirectXColors.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

Flash::Flash()
	:alpha_(1.0f)
{
}

Flash::~Flash()
{
}

void Flash::Initialize()
{
	sprite_.reset(new Sprite);
	sprite_->Initialize(L"Resources\\Images\\Flash.png", Vector2(320, 240), RECT{ 0,0,2,2 }, true, Colors::White.v, 0.0f, 320.0f);
	sprite_->SetAlpha(1.0f);
}

bool Flash::Update()
{
	alpha_ -= 0.05f;

	if (alpha_ < 0)
		return false;

	sprite_->SetAlpha(alpha_);

	return true;
}

void Flash::Render()
{
	sprite_->Draw();
}
