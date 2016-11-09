#pragma once

#include <vector>
#include <SimpleMath.h>
#include "Object3D.h"
#include "List.h"

class Enemy
{
private:
	Object3D parts_;

	//patten movement�p�̕ϐ�
	List<DirectX::SimpleMath::Vector3> movePoint_;
	ListNode<DirectX::SimpleMath::Vector3>* now_;

	//�ړ��̑���
	const float moveSpeed_ = 10.0f;

	//���̖ڕW���W�ύX�܂ł̎���
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
	DirectX::SimpleMath::Vector3 GetPositon() { return parts_.GetTrans(); }
	DirectX::SimpleMath::Vector3 GetRotate() { return parts_.GetRotate(); }
	float GetViewAngle() { return viewAngle_; }
	float GetViewDistance() { return viewDistance_; }
};

