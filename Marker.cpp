//////////////////////////////////////////////
// Name : Marker
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "Marker.h"
#include <SimpleMath.h>
#include "GameManager.h"
#include "Culling.h"

#include "Debug.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : Marker
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
Marker::Marker()
{
}

//////////////////////////////////////////////
// Name : ~Marker
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
Marker::~Marker()
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
void Marker::Initialize()
{
	marker_.LoadModelFromFile(L"Resources\\cModels\\Display.cmo");
	marker_.SetTrans(Vector3(0.0f, 0.0f, 0.0f));
	marker_.SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	marker_.SetScale(Vector3(2.0f, 1.5f, 1.0f));
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
void Marker::Update()
{
	marker_.Calc();

	//当たり判定に登録
	CollisionManager::GetInstance()->Entry(this);
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
void Marker::Render()
{
	marker_.Draw();

#ifdef DEBUG
	box_.Draw();
	wchar_t flag[20];
	if (Culling::InView(box_, Camera::MainCamera(), 6, 0.5f, 0.5f))
	{
		swprintf_s(flag, 20, L"In Camera = true");
	}
	else
		swprintf_s(flag, 20, L"In Camera = false");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(0, 80));
#endif
}

//////////////////////////////////////////////
// Name : SetPosition
//
// Over View : 座標の設定
//
// Argument : 座標
//
// Return :  無し
//////////////////////////////////////////////
void Marker::SetPosition(DirectX::SimpleMath::Vector3 pos)
{
	marker_.SetTrans(pos);
	box_.Translation(pos);
}

//////////////////////////////////////////////
// Name : SetRotate
//
// Over View : 回転角の設定
//
// Argument : 回転角
//
// Return :  無し
//////////////////////////////////////////////
void Marker::SetRotate(DirectX::SimpleMath::Vector3 rot)
{
	marker_.SetRotate(rot);
}

//////////////////////////////////////////////
// Name : SetScale
//
// Over View : 大きさの設定
//
// Argument : 大きさ
//
// Return :  無し
//////////////////////////////////////////////
void Marker::SetScale(DirectX::SimpleMath::Vector3 scale)
{
	marker_.SetScale(scale);
}
