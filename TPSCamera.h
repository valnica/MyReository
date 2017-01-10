//////////////////////////////////////////////
// Name : TPSCamera
//
// Author : 山田 聖弥
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
// Over View : 客観視点のState
//////////////////////////////////////////////
class TPSCamera:public State<Camera>,public Singleton<TPSCamera>
{
private:
	//注視点との距離
	const float distance_ = 10;
	
	//回転角
	DirectX::SimpleMath::Vector3 rotate_;
	
	//マウス感度
	float sensitivity_;

	friend class Singleton<TPSCamera>;

	TPSCamera();
public:
	~TPSCamera();

	//State切り替え関数
	std::shared_ptr<State<Camera>> Input(Camera& camera) override;
	void Update(Camera& camera) override;
};