//////////////////////////////////////////////
// Name : Debug Camera
//
// Author : �R�c ����
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once
#include "State.h"
#include <SimpleMath.h>

class Camera;

//////////////////////////////////////////////
// Class Name : DebugCamera
//
// Over View : �f�o�b�O�J����State
//////////////////////////////////////////////
class DebugCamera :
	public State<Camera>
{
private:
	//�����_�Ƃ̋���
	float distance_;
	
	//��]�p
	DirectX::SimpleMath::Vector3 rotate_;

public:
	DebugCamera();
	~DebugCamera();

	//State�؂�ւ��̊֐�
	State<Camera>* Input(Camera& camera);
	void Update(Camera& camera);
};

