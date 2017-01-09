//////////////////////////////////////////////
// Name : Flash
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "Flash.h"
#include "Sprite.h"
#include <SimpleMath.h>
#include <DirectXColors.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float transparentSpeed = 0.05f;

//////////////////////////////////////////////
// Name : Flash
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
Flash::Flash()
	:alpha_(1.0f)
{
}

//////////////////////////////////////////////
// Name : ~Flash
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
Flash::~Flash()
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
void Flash::Initialize()
{
	//画像の初期処理
	sprite_.reset(new Sprite);
	sprite_->Initialize(L"Resources\\Images\\Flash.png", Vector2(320, 240), RECT{ 0,0,2,2 }, true, Colors::White.v, 0.0f, 320.0f);
	sprite_->SetAlpha(1.0f);
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : 更新処理
//
// Argument : 無し
//
// Return : 仕事が終わったかの判定
//////////////////////////////////////////////
bool Flash::Update()
{
	//透明度の変更
	alpha_ -= transparentSpeed;

	//アルファが0になればこのクラスの仕事終了
	if (alpha_ < 0)
		return false;

	sprite_->SetAlpha(alpha_);

	return true;
}

//////////////////////////////////////////////
// Name : Render
//
// Over View : 描画処理
//
// Argument : 無し
//
// Return : 無し
//////////////////////////////////////////////
void Flash::Render()
{
	sprite_->Draw();
}
