#include "Player.h"
#include "State.h"
#include "PlayerMove.h"
#include "Utility.h"
#include "Stage.h"
#include "CollisionManager.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//モデルの行列計算
void Player::Calc()
{
	int a = 0;
	for (int i = 0; i < NUM_PARTS; i++)
	{
		parts_[i].Calc();
	}
}

//コンストラクタ
Player::Player()
{
	state_ = new PlayerMove;
}

//デストラクタ
Player::~Player()
{
	if (state_)
		delete state_;
}

//初期化
void Player::Initialize()
{
	//空のオブジェクト
	parts_[EMPTY].SetTrans(stage_->GetStartPos());
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
	//parts_[EYE].LoadModelFromFile(L"Resources\\cModels\\PlayerHead.cmo");
	parts_[EYE].SetTrans(Vector3(0.0f, 0.1f, -0.3f));
	parts_[EYE].SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	parts_[EYE].SetScale(Vector3(0.3f, 0.3f, 0.3f));
	parts_[EYE].SetParentWorld(&parts_[HEAD].GetWorld());

	collisionBody_.Initialize();
	collisionBody_.SetTrans(Vector3(0.0f, 0.85f, 0.3f));
	collisionBody_.SetLocalRadius(1.0f);
	collisionBody_.SetParentMatrix(&parts_[EMPTY].GetLocalWorld());
}

//更新処理
void Player::Update()
{
	//Stateパターン
	State<Player>* state = state_->Input(*this);
	if (state)
	{
		delete state_;
		state_ = state;
	}
	state_->Update(*this);

	//モデルの行列計算
	Calc();

	collisionBody_.Update();

	CollisionManager::GetInstance()->Entry(this);

	flag_ = false;
}

//描画
void Player::Render()
{
	for (int i = 0; i < NUM_PARTS; i++)
	{
		parts_[i].Draw();
	}

	collisionBody_.Draw();

	wchar_t flag[20];
	if (flag_)
		swprintf_s(flag, 20, L"PlayerFront = true");
	else
		swprintf_s(flag, 20, L"PlayerFront = false");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(0, 100));
}

void Player::SetStage(Stage * stage)
{
	stage_ = stage;
}

//座標の設定
void Player::SetPosition(Vector3 pos)
{
	parts_[EMPTY].SetTrans(pos);
}

//座標の取得
DirectX::SimpleMath::Vector3 Player::GetPosition()
{
	return parts_[EMPTY].GetTrans();
}

//回転角の設定
void Player::SetRotate(DirectX::SimpleMath::Vector3 rot)
{
	parts_[EMPTY].SetRotate(rot);
}

//回転角の取得
DirectX::SimpleMath::Vector3 Player::GetRotate()
{
	return parts_[EMPTY].GetRotate();
}

//頭パーツの回転角の設定
void Player::SetHeadRotate(Vector3 rot)
{
	//首の可動域に補正
	Clamp(-90.0f, 90.0f, rot.y);
	Clamp(-20.0f, 80.0f, rot.x);

	parts_[HEAD].SetRotate(rot);
}

//頭パーツの回転角の取得
Vector3 Player::GetHeadRotate()
{
	return parts_[HEAD].GetRotate();
}

//視線の座標を取得
Vector3 Player::GetEyePosition()
{
	Vector3 pos;
	Quaternion qua;
	Vector3 scale;
	parts_[EYE].GetWorld().Decompose(scale, qua, pos);
	return pos;
}

//視線の行列を取得
Matrix Player::GetEyeMatrix()
{
	return parts_[EYE].GetWorld();
}

void Player::Found()
{
	flag_ = true;
}
