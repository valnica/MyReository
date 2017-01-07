//////////////////////////////////////////////
// Name : Debug Camera
//
// Author : Rc Ήν
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
// Over View : fobOJState
//////////////////////////////////////////////
class DebugCamera :
	public State<Camera>
{
private:
	//_ΖΜ£
	float distance_;
	
	//ρ]p
	DirectX::SimpleMath::Vector3 rotate_;

public:
	DebugCamera();
	~DebugCamera();

	//StateΨθΦ¦ΜΦ
	State<Camera>* Input(Camera& camera);
	void Update(Camera& camera);
};

