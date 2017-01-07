//////////////////////////////////////////////
// Name : FPSCamera
//
// Author : R“c ¹–í
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once

#include "State.h"

class Camera;
//////////////////////////////////////////////
// Class Name : FPSCamera
//
// Over View : åŠÏƒJƒƒ‰
//////////////////////////////////////////////
class FPSCamera :public State<Camera>, public Singleton<FPSCamera>
{
private:

	friend class Singleton<FPSCamera>;

	FPSCamera();
public:
	~FPSCamera();

	//StateØ‚è‘Ö‚¦ŠÖ”
	State<Camera>* Input(Camera& camera);
	void Update(Camera& camera);
};

