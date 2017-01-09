//////////////////////////////////////////////
// Class Name : Object3D
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////

#pragma once

#include <Model.h>
#include <Effects.h>
#include "Camera.h"
#include <map>
#include <SimpleMath.h>

//////////////////////////////////////////////
// Class Name : Object3D
//
// Over View : 3D�I�u�W�F�N�g�֌W�̃N���X
//////////////////////////////////////////////
class Object3D
{
private:
	//3D�I�u�W�F�N�g�ɕK�v�ȕϐ�
	static ID3D11Device* device_;
	static ID3D11DeviceContext* deviceContext_;
	static DirectX::CommonStates* state_;
	static std::shared_ptr<DirectX::DGSLEffectFactory> effect_;
	static std::map<std::wstring, std::unique_ptr<DirectX::Model>> modelArray_;

public:
	//3D�I�u�W�F�N�g�ɕK�v�ȕϐ��̐ݒ�
	static void SetDevice(ID3D11Device* device) { device_ = device; }
	static void SetContext(ID3D11DeviceContext* devicecontect) { deviceContext_ = devicecontect; }
	static void SetState(DirectX::CommonStates* state) { state_ = state; }
	static void SetEffect(std::shared_ptr<DirectX::DGSLEffectFactory> effect) { effect_ = effect; }

private:
	//���f��
	const DirectX::Model* model_;
	
	//���W
	DirectX::SimpleMath::Vector3 trans_;

	//��]�p
	DirectX::SimpleMath::Vector3 rot_;
	
	//�傫��
	DirectX::SimpleMath::Vector3 scale_;
	
	//���[�J�����[���h�s��
	DirectX::SimpleMath::Matrix localWorld_;
	
	//���[���h�s��
	DirectX::SimpleMath::Matrix world_;
	
	//�e�I�u�W�F�N�g�̃��[���h�s��
	const DirectX::SimpleMath::Matrix* parentMatrix_;
	
	//�N�H�[�^�j�I���v�Z�t���O
	bool useQuaternion_;

	//��]�p
	DirectX::SimpleMath::Quaternion quaternion_;

public:
	Object3D();
	~Object3D();

	//���f���̓ǂݍ���
	void LoadModelFromFile(const wchar_t* fileName = nullptr);
	
	void Calc();
	void Draw();

	//���C�e�B���O�ݒ�
	void DesableLighting();

	//���W�̐ݒ�
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { trans_ = trans; }
	
	//��]�p�̐ݒ�
	void SetRotate(const DirectX::SimpleMath::Vector3& rot) { rot_ = rot; }
	
	//�傫���̐ݒ�
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { scale_ = scale; }
	
	//���[�J�����[���h�̐ݒ�
	void SetLocalWorld(const DirectX::SimpleMath::Matrix& world) { localWorld_ = world; }
	
	//�e�I�u�W�F�N�g�̐ݒ�
	void SetParentWorld(const DirectX::SimpleMath::Matrix* parentWorld) { parentMatrix_ = parentWorld; }
	
	//��]�p�̐ݒ�
	void SetQuaternion(const DirectX::SimpleMath::Quaternion quaternion) {quaternion_ = quaternion;}
	
	//�N�H�[�^�j�I���t���O�̐؂�ւ�
	void SetQuaternionFlag(bool flag) { useQuaternion_ = flag; }

	//���W�̎擾
	const DirectX::SimpleMath::Vector3& GetTrans() {return trans_;}
	
	//��]�p�̎擾
	const DirectX::SimpleMath::Vector3& GetRotate() { return rot_; }
	
	//�傫���̎擾
	const DirectX::SimpleMath::Vector3& GetScale() { return scale_; }
	
	//���[�J�����[���h�̎擾
	DirectX::SimpleMath::Matrix& GetLocalWorld() { return localWorld_; }
	
	//���[���h�̎擾
	DirectX::SimpleMath::Matrix& GetWorld() { return world_; }
	
	//�e�I�u�W�F�N�g�̎擾
	const DirectX::SimpleMath::Matrix* GetParentWorld() { return parentMatrix_; }
	
	//////////////////////////////////////////////
	// Name : HaveParent
	//
	// Over View : �e�I�u�W�F�N�g�����邩�ǂ���
	//
	// Argument : ����
	//
	// Return : true or false 
	//////////////////////////////////////////////
	bool HaveParent() 
	{
		if (parentMatrix_)
			return true;
		else
			return false;
	}
};

