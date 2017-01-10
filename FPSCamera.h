//////////////////////////////////////////////
// Name : FPSCamera
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "State.h"

class Camera;
//////////////////////////////////////////////
// Class Name : FPSCamera
//
// Over View : ��σJ����
//////////////////////////////////////////////
class FPSCamera :public State<Camera>, public Singleton<FPSCamera>
{
private:

	friend class Singleton<FPSCamera>;

	FPSCamera();
public:
	~FPSCamera();

	//State�؂�ւ��֐�
	std::shared_ptr<State<Camera>> Input(Camera& camera);
	void Update(Camera& camera);
};

