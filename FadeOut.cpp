//////////////////////////////////////////////
// Name : FadeOut
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "FadeOut.h"
#include "Sprite.h"
#include "DirectXTK.h"

using namespace DirectX::SimpleMath;

const float fadeSpeed = 0.05f;

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : 初期化処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
FadeOut::FadeOut()
	:alpha_(0.0f)
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
FadeOut::~FadeOut()
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
void FadeOut::Initialize()
{
	sprite_.reset(new Sprite);
	sprite_->Initialize(L"Resources\\Images\\Fade.png", Vector2(WINDOW_W / 2.0f, WINDOW_H / 2.0f), RECT{ 0,0,2,2 }, true);
	sprite_->SetScale(Vector2(WINDOW_W / 2.0f, WINDOW_H / 2.0f));
	alpha_ = 0.0f;
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
bool FadeOut::Update()
{
	alpha_ += fadeSpeed;

	if (alpha_ > 1.0f)
		return false;

	return true;
}

//////////////////////////////////////////////
// Name : Render
//
// Over View : 描画処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void FadeOut::Render()
{
	sprite_->Draw();
}

//////////////////////////////////////////////
// Name : Finalize
//
// Over View : 終了処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void FadeOut::Finalize()
{
}
