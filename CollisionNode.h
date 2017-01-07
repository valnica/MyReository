//////////////////////////////////////////////
// Name : CollitionNode
//
// Author : �R�c ����
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once

#include "Object3D.h"
#include "CollisionManager.h"

//////////////////////////////////////////////
// Class Name : SphereNode
//
// Over View : �����蔻��p�̋��I�u�W�F�N�g
//////////////////////////////////////////////
class SphereNode :public Sphere
{
protected:
	//�I�u�W�F�N�g
	Object3D object_;

	//���a
	float localRadius_;

	//���W
	DirectX::SimpleMath::Vector3 trans_;

public:
	SphereNode();
	
	void Initialize();
	void Update();
	void Draw();

	//�e�I�u�W�F�N�g�̐ݒ�
	void SetParentMatrix(const DirectX::SimpleMath::Matrix* parent);
	
	//���a�̐ݒ�
	void SetLocalRadius(float radius) { localRadius_ = radius; }
	
	//���W�̐ݒ�
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { trans_ = trans; }
	
	//���W�̎擾
	DirectX::SimpleMath::Vector3 GetTrans() { return object_.GetTrans(); }
};

//////////////////////////////////////////////
// Class Name : CapsuleNode
//
// Over View : �����蔻��p�̃J�v�Z���I�u�W�F�N�g
//////////////////////////////////////////////
class CapsuleNode :public Capsule
{
protected:
	//�I�u�W�F�N�g
	Object3D object_;

	//�J�v�Z���̒���
	float localLenght_;

	//���a
	float localRadius_;

	//���W
	DirectX::SimpleMath::Vector3 trans_;

public:
	CapsuleNode();

	void Initialize();
	void Update();
	void Draw();

	//�e�I�u�W�F�N�g�̐ݒ�
	void SetParentMatrix(const DirectX::SimpleMath::Matrix* parent);
	
	//��]�p�̐ݒ�
	void SetRotate(DirectX::SimpleMath::Vector3& rotate);
	
	//���a�̐ݒ�
	void SetLocalRadius(float radius) { localRadius_ = radius; }
	
	//�����̐ݒ�
	void SetLocalLenght(float lenght) { localLenght_ = lenght; }
	
	//���W�̐ݒ�
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { trans_ = trans; }
};

