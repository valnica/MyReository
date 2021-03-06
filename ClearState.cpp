//////////////////////////////////////////////
// Name : ClearState
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "ClearState.h"
#include "Player.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : ClearState
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
ClearState::ClearState()
	:angle_(0.0f)
{
}

//////////////////////////////////////////////
// Name : ~ClearState
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
ClearState::~ClearState()
{
}

//////////////////////////////////////////////
// Name : Input
//
// Over View : Stateの切り替え処理
//
// Argument : playerへの参照
//
// Return : Stateのポインタ
//////////////////////////////////////////////
std::shared_ptr<State<Player>> ClearState::Input(Player & player)
{
	//遷移条件と遷移先のポインタを設定する


	return nullptr;
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : 更新処理
//
// Argument : 無し
//
// Return : 無し 
//////////////////////////////////////////////
void ClearState::Update(Player & player)
{
	//プレイヤーの頭の回転
	angle_ += 0.1f;
	float rad = sinf(angle_) * 30;

	player.SetHeadRotate(Vector3(rad, 0.0f, 0.0f));
}