//////////////////////////////////////////////
// Name : Enemy
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "Enemy.h"
#include "GameManager.h"
#include "Player.h"
#include "CollisionManager.h"

#include "Debug.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : Enemy
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
Enemy::Enemy()
{
}

//////////////////////////////////////////////
// Name : ~Enemy
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
Enemy::~Enemy()
{
	movePoint_.DataAllDelete();
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
void Enemy::Initialize()
{
	//空のオブジェクト
	parts_[EMPTY].SetTrans(movePoint_.Top()->GetData());
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

	//AIの初期処理
	now_ = movePoint_.Top();
	moveCount_ =(int)((now_->next_->GetData() - now_->GetData()).Length() / moveSpeed_ * 60);
	waitTime_ = 60; 
	currentCount_ = 0;
	
	//視野の設定
	viewAngle_ = 45.0f;
	viewDistance_ = 30.0f;
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
void Enemy::Update()
{
	currentCount_++;

	//適正時間を計算
	float time = (float)currentCount_ / moveCount_;
	if (time > 1.0f)
		time = 1.0f;

	//線形補間で移動
	Vector3 vec = now_->GetData() + time * (now_->next_->GetData() - now_->GetData());
	parts_[EMPTY].SetTrans(vec);

	for (int i = 0; i < NUM_PARTS; i++)
	{
		parts_[i].Calc();
	}
	//キャラクターの回転
	vec = now_->next_->GetData() - now_->GetData();
	float rad = atan2f(-vec.x, -vec.z);
	parts_[EMPTY].SetRotate(Vector3(0.0f, rad * 180.0f /3.14f , 0.0f));

	//次の目標座標更新
	if (currentCount_ >= moveCount_ + waitTime_)
	{
		currentCount_ = 0;
		now_ = now_->next_;
		moveCount_ = (int)((now_->next_->GetData() - now_->GetData()).Length() / moveSpeed_ * 60);
	}

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
void Enemy::Render()
{
	//描画
	for (int i = 0; i < NUM_PARTS; i++)
	{
		parts_[i].Draw();
	}

#ifdef DEBUG
	//プレイヤーが視野内にいるかどうかのデバッグ
	{
		//デバッグ　向いている方向を描画
		Vector3 dir(0.0f, 0.0f, -viewDistance_);
		Matrix rot = Matrix::CreateRotationY(parts_[EMPTY].GetRotate().y * 3.14f / 180);
		Vector3 vec = Vector3::TransformNormal(dir, rot);
		Debug::GetInstance()->DrawLine(parts_[EMPTY].GetTrans(), parts_[EMPTY].GetTrans() + vec);

		//視野のデバッグ
		rot = Matrix::CreateRotationY((parts_[EMPTY].GetRotate().y + viewAngle_) * 3.14f / 180.0f);
		vec = Vector3::TransformNormal(dir, rot);
		Debug::GetInstance()->DrawLine(parts_[EMPTY].GetTrans(), parts_[EMPTY].GetTrans() + vec);

		rot = Matrix::CreateRotationY((parts_[EMPTY].GetRotate().y - viewAngle_) * 3.14f / 180.0f);
		vec = Vector3::TransformNormal(dir, rot);
		Debug::GetInstance()->DrawLine(parts_[EMPTY].GetTrans(),parts_[EMPTY].GetTrans() + vec);
	}
#endif
}

//////////////////////////////////////////////
// Name : SetMovePoint
//
// Over View : 巡回場所のリストの設定
//
// Argument : 巡回場所を保存してあるリスト
//
// Return :  無し
//////////////////////////////////////////////
void Enemy::SetMovePoint(List<DirectX::SimpleMath::Vector3> movePoint)
{
	movePoint_ = movePoint;
}