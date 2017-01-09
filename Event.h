//////////////////////////////////////////////
// Class Name : Event
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once

#include "CollisionManager.h"
#include <SimpleMath.h>

class Stage;

//////////////////////////////////////////////
// Class Name : Event
//
// Over View : �Q�[���C�x���g�p�̊��N���X
//////////////////////////////////////////////
class Event
{
protected:
	//�����蔻��I�u�W�F�N�g
	Box box_;

public:
	Event() {};
	virtual ~Event() {};

	virtual void Initialize() {};
	virtual bool Run() = 0 ;
	virtual void Render() {};
	
	//�����蔻��I�u�W�F�N�g�̎擾
	Box GetBox() { return box_; }
};

//////////////////////////////////////////////
// Class Name : ClearEvent
//
// Over View : �N���A�C�x���g
//////////////////////////////////////////////
class ClearEvent :public Event
{
private:
	//���W
	DirectX::SimpleMath::Vector3 pos_;

	//�����蔻��I�u�W�F�N�g�̑傫��
	DirectX::SimpleMath::Vector3 scale_;

public:
	ClearEvent() {};
	~ClearEvent() {};

	void Initialize();
	bool Run() override;
	void Render()
	{
		box_.Draw();
	}

	//���W�̐ݒ�
	void SetPosition(DirectX::SimpleMath::Vector3 pos)
	{
		pos_ = pos;
	}

	//�����蔻��I�u�W�F�N�g�̑傫���̐ݒ�
	void SetScale(DirectX::SimpleMath::Vector3 scale)
	{
		scale_ = scale;
	}

	//�����蔻��I�u�W�F�N�g�̐ݒ�
	void SetBox(Box box)
	{
		box_ = box;
		box_.SetScale(scale_);
		box_.Translation(pos_ + DirectX::SimpleMath::Vector3(0.0f, scale_.y / 2.0f, 0.0f));
	}
};