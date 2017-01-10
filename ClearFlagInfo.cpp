//////////////////////////////////////////////
// Name : ClearFlagInfo
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "ClearFlagInfo.h"
#include "Sprite.h"
#include "DirectXTK.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : CameraFlame
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
ClearFlagInfo::ClearFlagInfo()
{
}

//////////////////////////////////////////////
// Name : CameraFlame
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
ClearFlagInfo::~ClearFlagInfo()
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
void ClearFlagInfo::Initialize()
{
	sprite_.reset(new Sprite);
	sprite_->Initialize(L"Resources\\Images\\CharData.png", Vector2(WINDOW_W / 2.0f, WINDOW_H / 4.0f * 3.0f + 20.0f), RECT{ 0,0,448,64 }, true);

	alpha_ = 1.0f;
	count_ = 60;
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : 更新処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
bool ClearFlagInfo::Update()
{
	if (count_ > 0)
		count_--;
	else
		alpha_ -= 0.05f;

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
// Return :  無し
//////////////////////////////////////////////
void ClearFlagInfo::Render()
{
	sprite_->Draw();
}
