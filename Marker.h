//////////////////////////////////////////////
// Name : Marker
//
// Author : �R�c ����
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once

#include "Object3D.h"
#include "CollisionManager.h"

//////////////////////////////////////////////
// Class Name : Marker
//
// Over View : �ʐ^���B����I�u�W�F�N�g
//////////////////////////////////////////////
class Marker
{
private:
	//�I�u�W�F�N�g
	Object3D marker_;
	
	//�����蔻��p�̃I�u�W�F�N�g
	Box box_;

public:
	Marker();
	~Marker();

	void Initialize();
	void Update();
	void Render();

	//�����蔻��p�̃I�u�W�F�N�g�̎擾
	Box& GetBox() { return box_; }

	//���W�̎擾
	DirectX::SimpleMath::Vector3 GetPos() { return marker_.GetTrans(); }
	
	//���W�̐ݒ�
	void SetPosition(DirectX::SimpleMath::Vector3 pos);
	
	//��]�p�̐ݒ�
	void SetRotate(DirectX::SimpleMath::Vector3 rot);
};

