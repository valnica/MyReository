//////////////////////////////////////////////
// Name : CameraFlame
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "CameraFlame.h"
#include "Sprite.h"

#include "Used\DirectXTK.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : CameraFlame
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
CameraFlame::CameraFlame()
{
}


//////////////////////////////////////////////
// Name : ~CameraFlame
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
CameraFlame::~CameraFlame()
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
void CameraFlame::Initialize()
{
	sprite_.reset(new Sprite);
	sprite_->Initialize(L"Resources\\Images\\Flame.png", Vector2(WINDOW_W / 2.0f, WINDOW_H / 2.0f), { 0,0,64,48 }, true);
	sprite_->SetScale(5.0f);

	count_ = 1;
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
bool CameraFlame::Update()
{
	count_--;

	if (count_ < 0)
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
void CameraFlame::Render()
{
	sprite_->Draw();
}
