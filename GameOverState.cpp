//////////////////////////////////////////////
// Name : GameOverState
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "GameOverState.h"
#include "Player.h"

const float headRollSpeed = 0.1f;
const float rollSpeed = 50.0f;

//////////////////////////////////////////////
// Name : GameOverState
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
GameOverState::GameOverState()
	:angle_(0.0f)
{
}

//////////////////////////////////////////////
// Name : ~GameOverState
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
GameOverState::~GameOverState()
{
}

//////////////////////////////////////////////
// Name : Input
//
// Over View : State切り替え
//
// Argument : プレイヤーの参照
//
// Return :  無し
//////////////////////////////////////////////
State<Player>* GameOverState::Input(Player & player)
{
	return nullptr;
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : 更新処理
//
// Argument : プレイヤーの参照
//
// Return :  無し
//////////////////////////////////////////////
void GameOverState::Update(Player & player)
{
	//首の回転速度の更新
	angle_ += headRollSpeed;
	float rot = sinf(angle_) * rollSpeed;
	player.SetHeadRotate(DirectX::SimpleMath::Vector3(-20.0f, rot, 0.0f));
}
