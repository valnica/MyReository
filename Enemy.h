//////////////////////////////////////////////
// Name : Enemy
//
// Author : 山田 聖弥
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once

#include <vector>
#include <SimpleMath.h>
#include "Object3D.h"
#include "List.h"
#include "Character.h"

//////////////////////////////////////////////
// Class Name : Enemy
//
// Over View : 敵
//////////////////////////////////////////////
class Enemy:public Character
{
private:
	//モデルのパーツの定義
	enum PARTS
	{
		EMPTY,
		BODY,
		HEAD,
		EYE,

		NUM_PARTS
	};

	//モデルのパーツ
	Object3D parts_[NUM_PARTS];

	//巡回用の変数
	List<DirectX::SimpleMath::Vector3> movePoint_;
	ListNode<DirectX::SimpleMath::Vector3>* now_;

	//移動の速さ
	const float moveSpeed_ = 10.0f;

	//次の目標座標変更までの時間
	int moveCount_;
	int currentCount_;
	int waitTime_;
	
	//視野角
	float viewAngle_;

	//視野距離
	float viewDistance_;

public:
	Enemy();
	~Enemy();

	void Initialize();
	void Update();
	void Render();

	//巡回用の変数の設定
	void SetMovePoint(List<DirectX::SimpleMath::Vector3> movePoint);
	
	//座標の取得
	DirectX::SimpleMath::Vector3 GetPosition() { return parts_[EMPTY].GetTrans(); }
	
	//回転角の取得
	DirectX::SimpleMath::Vector3 GetRotate() { return parts_[EMPTY].GetRotate(); }
	
	//視野角の取得
	float GetViewAngle() { return viewAngle_; }
	
	//視野距離の取得
	float GetViewDistance() { return viewDistance_; }
};

