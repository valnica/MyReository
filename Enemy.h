//////////////////////////////////////////////
// Name : Enemy
//
// Author : �R�c ����
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
// Over View : �G
//////////////////////////////////////////////
class Enemy:public Character
{
private:
	//���f���̃p�[�c�̒�`
	enum PARTS
	{
		EMPTY,
		BODY,
		HEAD,
		EYE,

		NUM_PARTS
	};

	//���f���̃p�[�c
	Object3D parts_[NUM_PARTS];

	//����p�̕ϐ�
	List<DirectX::SimpleMath::Vector3> movePoint_;
	ListNode<DirectX::SimpleMath::Vector3>* now_;

	//�ړ��̑���
	const float moveSpeed_ = 10.0f;

	//���̖ڕW���W�ύX�܂ł̎���
	int moveCount_;
	int currentCount_;
	int waitTime_;
	
	//����p
	float viewAngle_;

	//���싗��
	float viewDistance_;

public:
	Enemy();
	~Enemy();

	void Initialize();
	void Update();
	void Render();

	//����p�̕ϐ��̐ݒ�
	void SetMovePoint(List<DirectX::SimpleMath::Vector3> movePoint);
	
	//���W�̎擾
	DirectX::SimpleMath::Vector3 GetPosition() { return parts_[EMPTY].GetTrans(); }
	
	//��]�p�̎擾
	DirectX::SimpleMath::Vector3 GetRotate() { return parts_[EMPTY].GetRotate(); }
	
	//����p�̎擾
	float GetViewAngle() { return viewAngle_; }
	
	//���싗���̎擾
	float GetViewDistance() { return viewDistance_; }
};

