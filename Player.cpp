//////////////////////////////////////////////
// Name : Player
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "Player.h"
#include "State.h"
#include "Utility.h"
#include "Stage.h"
#include "CollisionManager.h"
#include "TPSMode.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : Calc
//
// Over View : ワールド計算
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void Player::Calc()
{
	int a = 0;
	for (int i = 0; i < NUM_PARTS; i++)
	{
		parts_[i].Calc();
	}
}

//////////////////////////////////////////////
// Name : Player
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
Player::Player()
{
}

//////////////////////////////////////////////
// Name : ~Player
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
Player::~Player()
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
void Player::Initialize()
{
	//空のオブジェクト
	parts_[EMPTY].SetTrans(Vector3(0.0f, 0.0f, 0.0f));
	parts_[EMPTY].SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	parts_[EMPTY].SetScale(Vector3(1.0f, 1.0f, 1.0f));

	parts_[BODY].LoadModelFromFile(L"Resources\\cModels\\PlayerBody.cmo");
	parts_[BODY].SetTrans(Vector3(0.0f, 0.0f, 0.0f));
	parts_[BODY].SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	parts_[BODY].SetScale(Vector3(1.0f, 1.0f, 1.0f));
	parts_[BODY].SetParentWorld(&parts_[EMPTY].GetWorld());

	parts_[HEAD].LoadModelFromFile(L"Resources\\cModels\\PlayerHead.cmo");
	parts_[HEAD].SetTrans(Vector3(0.0f, 1.3f, 0.3f));
	parts_[HEAD].SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	parts_[HEAD].SetScale(Vector3(1.0f, 1.0f, 1.0f));
	parts_[HEAD].SetParentWorld(&parts_[BODY].GetWorld());

	//視点の位置
	parts_[EYE].SetTrans(Vector3(0.0f, 0.1f, -0.3f));
	parts_[EYE].SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	parts_[EYE].SetScale(Vector3(0.3f, 0.3f, 0.3f));
	parts_[EYE].SetParentWorld(&parts_[HEAD].GetWorld());

	//当たり判定用のモデルの初期化
	collisionBody_.Initialize();
	collisionBody_.SetTrans(Vector3(0.0f, 0.85f, 0.3f));
	collisionBody_.SetLocalRadius(1.0f);
	collisionBody_.SetParentMatrix(&parts_[EMPTY].GetLocalWorld());
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : 初期化処理
//
// Argument : state
//
// Return :  無し
//////////////////////////////////////////////
void Player::Initialize(std::shared_ptr<State<Player>> state)
{
	state_ = state;
	Initialize();
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
void Player::Update()
{
	//Stateパターン
	std::weak_ptr<State<Player>> state = state_.lock()->Input(*this);
	if (state.lock())
	{
		state_ = state;
	}
	state_.lock()->Update(*this);

	//モデルの行列計算
	Calc();

	collisionBody_.Update();

	//当たり判定に登録
	CollisionManager::GetInstance()->Entry(this);

#ifdef DEBUG
	//デバッグフラグの初期化
	debugFlag_ = false;
#endif
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
void Player::Render()
{
	for (int i = 0; i < NUM_PARTS; i++)
	{
		parts_[i].Draw();
	}

	collisionBody_.Draw();

#ifdef DEBUG
	wchar_t flag[20];
	if (debugFlag_)
		swprintf_s(flag, 20, L"PlayerFront = true");
	else
		swprintf_s(flag, 20, L"PlayerFront = false");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(0, 100));
#endif //デバッグ
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
void Player::SetPosition(Vector3 pos)
{
	parts_[EMPTY].SetTrans(pos);
}

//////////////////////////////////////////////
// Name : GetPosition
//
// Over View : 座標の取得
//
// Argument : 無し
//
// Return :  座標
//////////////////////////////////////////////
DirectX::SimpleMath::Vector3 Player::GetPosition()
{
	return parts_[EMPTY].GetTrans();
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
void Player::SetRotate(DirectX::SimpleMath::Vector3 rot)
{
	parts_[EMPTY].SetRotate(rot);
}

//////////////////////////////////////////////
// Name : GetRotate
//
// Over View : 回転角の取得
//
// Argument : 無し
//
// Return :  回転角
//////////////////////////////////////////////
DirectX::SimpleMath::Vector3 Player::GetRotate()
{
	return parts_[EMPTY].GetRotate();
}

//////////////////////////////////////////////
// Name : SetHeadRotate
//
// Over View : 頭の回転角の設定
//
// Argument : 回転角
//
// Return :  無し
//////////////////////////////////////////////
void Player::SetHeadRotate(Vector3 rot)
{
	//首の可動域に補正
	Clamp(-90.0f, 90.0f, rot.y);
	Clamp(-20.0f, 80.0f, rot.x);

	parts_[HEAD].SetRotate(rot);
}

//////////////////////////////////////////////
// Name : GetHeadRotate
//
// Over View : 回転角の取得
//
// Argument : 無し
//
// Return :  回転角
//////////////////////////////////////////////
Vector3 Player::GetHeadRotate()
{
	return parts_[HEAD].GetRotate();
}

//////////////////////////////////////////////
// Name : GetEyePosition
//
// Over View : 目の座標取得
//
// Argument : 無し
//
// Return : 目の座標
//////////////////////////////////////////////
Vector3 Player::GetEyePosition()
{
	Vector3 pos;
	Quaternion qua;
	Vector3 scale;
	parts_[EYE].GetWorld().Decompose(scale, qua, pos);
	return pos;
}

//////////////////////////////////////////////
// Name : GetEyeMatrix
//
// Over View : 目の行列を取得
//
// Argument : 無し
//
// Return : 目のワールド
//////////////////////////////////////////////
Matrix Player::GetEyeMatrix()
{
	return parts_[EYE].GetWorld();
}

//////////////////////////////////////////////
// Name : Found
//
// Over View : 見つかった通知
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void Player::Found()
{
#ifdef DEBUG
	debugFlag_ = true;
#endif
}
