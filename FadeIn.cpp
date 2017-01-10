//////////////////////////////////////////////
// Name : FadeIn
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "FadeIn.h"
#include "Sprite.h"
#include "DirectXTK.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

const float fadeSpeed = 0.01f;

//////////////////////////////////////////////
// Name : FadeIn
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
FadeIn::FadeIn()
	:alpha_(1.0f)
{
}

//////////////////////////////////////////////
// Name : ~FadeIn
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
FadeIn::~FadeIn()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : 初期化処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void FadeIn::Initialize()
{
	sprite_.reset(new Sprite);
	sprite_->Initialize(L"Resources\\Images\\Fade.png", Vector2(WINDOW_W / 2.0f, WINDOW_H / 2.0f), RECT{ 0,0,2,2 }, true);
	sprite_->SetScale(Vector2(WINDOW_W / 2.0f, WINDOW_H / 2.0f));
	alpha_ = 1.0f;
	sprite_->SetAlpha(alpha_);
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : 更新処理
//
// Argument : 無し
//
// Return :  役割が終わったかの判定
//////////////////////////////////////////////
bool FadeIn::Update()
{
	alpha_ -= fadeSpeed;

	if (alpha_ < 0)
	{
		return false;
	}

	sprite_->SetAlpha(alpha_);

	return true;
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : 初期化処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void FadeIn::Render()
{
	sprite_->Draw();
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : 初期化処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void FadeIn::Finalize()
{
}
