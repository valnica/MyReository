//////////////////////////////////////////////
// Name : TPSCamera
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once

#include "State.h"
#include "Camera.h"
#include <SimpleMath.h>

//////////////////////////////////////////////
// Name : TPSCamera
//
// Over View : �q�ώ��_��State
//////////////////////////////////////////////
class TPSCamera:public State<Camera>,public Singleton<TPSCamera>
{
private:
	//�����_�Ƃ̋���
	const float distance_ = 10;
	
	//��]�p
	DirectX::SimpleMath::Vector3 rotate_;
	
	//�}�E�X���x
	float sensitivity_;

	friend class Singleton<TPSCamera>;

	TPSCamera();
public:
	~TPSCamera();

	//State�؂�ւ��֐�
	std::shared_ptr<State<Camera>> Input(Camera& camera) override;
	void Update(Camera& camera) override;
};