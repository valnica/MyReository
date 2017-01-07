//////////////////////////////////////////////
// Name : Debug Camera
//
// Author : 山田 聖弥
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
// Over View : デバッグカメラState
//////////////////////////////////////////////
class DebugCamera :
	public State<Camera>
{
private:
	//注視点との距離
	float distance_;
	
	//回転角
	DirectX::SimpleMath::Vector3 rotate_;

public:
	DebugCamera();
	~DebugCamera();

	//State切り替えの関数
	State<Camera>* Input(Camera& camera);
	void Update(Camera& camera);
};

