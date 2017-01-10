//////////////////////////////////////////////
// Name : Player
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once
#include "Object3D.h"
#include "State.h"
#include "CollisionNode.h"
#include "Character.h"

#include "Debug.h"

namespace Math = DirectX::SimpleMath;

class Stage;

//////////////////////////////////////////////
// Class Name : Player
//
// Over View : プレイヤー
//////////////////////////////////////////////
class Player:public Character
{
private:
	//State
	std::weak_ptr<State<Player>> state_;

	//モデルパーツの定義
	enum PARTS
	{
		EMPTY,
		BODY,
		HEAD,
		EYE,

		NUM_PARTS
	};

#ifdef DEBUG
	//デバッグフラグ
	bool debugFlag_;
#endif

	//当たり判定オブジェクト
	SphereNode collisionBody_;

	//モデル
	Object3D parts_[NUM_PARTS];
public:
	Player();
	~Player();

	void Initialize();
	void Initialize(std::shared_ptr<State<Player>> state);
	void Update();
	void Render();

	//ポジションのセッターとゲッター
	void SetPosition(Math::Vector3 pos);
	Math::Vector3 GetPosition();
	
	//回転角のセッターとゲッター
	void SetRotate(Math::Vector3 rot);
	Math::Vector3 GetRotate();

	//頭の回転角のセッターとゲッター
	void SetHeadRotate(Math::Vector3 rot);
	Math::Vector3 GetHeadRotate();

	//目のゲッターとセッター
	Math::Vector3 GetEyePosition();
	Math::Matrix GetEyeMatrix();

	//当たり判定オブジェクトの取得
	SphereNode& GetCollisionBody() { return collisionBody_; }
	
	//見つかった通知
	void Found();

	//ワールド計算
	void Calc();
};

