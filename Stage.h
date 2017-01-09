//////////////////////////////////////////////
// Name : Stage
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once
#include <vector>
#include <SimpleMath.h>
#include "CollisionManager.h"

class LandShape;
class Marker;
class ClearEvent;

//////////////////////////////////////////////
// Class Name : Stage
//
// Over View : �Q�[���X�e�[�W
//////////////////////////////////////////////
class Stage
{
protected:
	//�X�e�[�W�ɕK�v�ȃI�u�W�F�N�g
	std::vector<std::shared_ptr<LandShape>> landshapeList_;
	std::shared_ptr<Marker> marker_;
	std::shared_ptr<ClearEvent> clearEvent_;
	
	//�v���C���[�̃X�^�[�g���W
	DirectX::SimpleMath::Vector3 startPos_;
	
	//�N���A�t���O
	static bool clearFlag_;

public:
	Stage();
	virtual ~Stage();

	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Finalize();

	//�N���A�t���O�̐ݒ�
	static void SetClearFlag() { clearFlag_ = true; }
	
	//�X�^�[�g���W�̎擾
	DirectX::SimpleMath::Vector3 GetStartPos() { return startPos_; }
	
	//�N���A�t���O�̎擾
	static bool GetClearFlag() { return clearFlag_; }
};

