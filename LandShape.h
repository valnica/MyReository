//////////////////////////////////////////////
// Class Name : LandShape
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "LandShapeData.h"
#include "Camera.h"
#include "Object3D.h"
#include "CollisionManager.h"

#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <CommonStates.h>


//////////////////////////////////////////////
// Class Name : LandShapeCommonDef
//
// Over View : �n�`�̃f�t�H���g�ݒ�p�N���X
//////////////////////////////////////////////
class LandShapeCommonDef
{
public:
	//�n�`�ɕK�v�ȕϐ�
	ID3D11Device* device_;
	ID3D11DeviceContext* deviceContext_;
};

//////////////////////////////////////////////
// Class Name : LandShapeCommon
//
// Over View : �n�`�̋��ʐݒ�N���X
//////////////////////////////////////////////
class LandShapeCommon
{
	friend class LandShape;
public:
	LandShapeCommon(std::shared_ptr<LandShapeCommonDef> def);
	~LandShapeCommon();
protected:
	//�n�`�ɕK�v�ȕϐ�
	std::unique_ptr<DirectX::CommonStates> state_;
	std::unique_ptr<DirectX::EffectFactory> effectFactory_;
	std::unique_ptr<DirectX::BasicEffect> effect_;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> primitiveBatch_;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout_;
	ID3D11DeviceContext* deviceContext_;
};

//////////////////////////////////////////////
// Class Name : LandShape
//
// Over View : �n�`
//////////////////////////////////////////////
class LandShape
{
protected:
	//�n�`�̐ݒ�
	static std::unique_ptr<LandShapeCommon> common_;
	
	//�n�`�̃v�[��
	static std::map<std::wstring, std::unique_ptr<LandShapeData>> dataArray_;

	//�n�`�ɕK�v�ȕϐ�
	Object3D object_;
	const LandShapeData* data_;
	DirectX::SimpleMath::Matrix world_;
	Box box_;

public:
	static void InitializeCommon(std::shared_ptr<LandShapeCommonDef>);

	LandShape();
	void Initialize(const wchar_t* fileNameMDL, const wchar_t* fileNameCMO = nullptr);
	void Update();
	void Calc();
	void Draw();

	//���W�̐ݒ�
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { object_.SetTrans(trans); }
	
	//��]�p�̐ݒ�
	void SetRotate(const DirectX::SimpleMath::Vector3& rotate) { object_.SetRotate(rotate); }
	
	//�傫���̐ݒ�
	void SetScale(DirectX::SimpleMath::Vector3 scale) { object_.SetScale(DirectX::SimpleMath::Vector3(scale)); }
	
	//���[���h�̐ݒ�
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { object_.SetLocalWorld(world); }

	//�����蔻��p�̃{�b�N�X�̐ݒ�
	void SetBox(Box box) 
	{
		box_ = box; 
		box_.SetScale(object_.GetScale());
		box_.Translation(object_.GetTrans() + DirectX::SimpleMath::Vector3(0.0f, object_.GetScale().y / 2.0f, 0.0f));
	}
	//�����蔻��p�̃{�b�N�X�̎擾
	Box GetBox() { return box_; }

	//���W�̎擾
	const DirectX::SimpleMath::Vector3& GetTrans() { return object_.GetTrans(); }
	
	//��]�p�̎擾
	const DirectX::SimpleMath::Vector3& GetRotate() { return object_.GetRotate(); }
	
	//�傫���̐ݒ�
	const float GetScale() { return object_.GetScale().x; }
	
	//���[���h�̎擾
	const DirectX::SimpleMath::Matrix& GetLocalWorld() { return object_.GetWorld(); }

	//���Ƃ̓����蔻��
	bool IntersectSphere(const Sphere& sphere, DirectX::SimpleMath::Vector3* reject);
	
	//�����Ƃ̓����蔻��
	bool IntersectSegment(const Segment& segment, DirectX::SimpleMath::Vector3* inter, float angleofFloor = 30);
};