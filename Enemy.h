#pragma once

#include <vector>
#include <SimpleMath.h>
#include "Object3D.h"
#include "List.h"
#include "Character.h"

class Enemy:public Character
{
private:
	enum PARTS
	{
		EMPTY,
		BODY,
		HEAD,
		EYE,

		NUM_PARTS
	};

	Object3D parts_[NUM_PARTS];

	//patten movement用の変数
	List<DirectX::SimpleMath::Vector3> movePoint_;
	ListNode<DirectX::SimpleMath::Vector3>* now_;

	//移動の速さ
	const float moveSpeed_ = 10.0f;

	//次の目標座標変更までの時間
	int moveCount_;
	int currentCount_;
	int waitTime_;
	
	float viewAngle_;
	float viewDistance_;

public:
	Enemy();
	~Enemy();

	void Initialize();
	void Update();
	void Render();

	void SetMovePoint(List<DirectX::SimpleMath::Vector3> movePoint);
	DirectX::SimpleMath::Vector3 GetPosition() { return parts_[EMPTY].GetTrans(); }
	DirectX::SimpleMath::Vector3 GetRotate() { return parts_[EMPTY].GetRotate(); }
	float GetViewAngle() { return viewAngle_; }
	float GetViewDistance() { return viewDistance_; }
};

