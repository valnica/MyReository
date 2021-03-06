//////////////////////////////////////////////
// Name : TPSCamera
//
// Author : Rc Ήν
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "State.h"
#include "Camera.h"

#include <SimpleMath.h>

//////////////////////////////////////////////
// Name : TPSCamera
//
// Over View : qΟ_ΜState
//////////////////////////////////////////////
class TPSCamera:public State<Camera>,public Singleton<TPSCamera>
{
private:
	//_ΖΜ£
	const float distance_ = 10;
	
	//ρ]p
	DirectX::SimpleMath::Vector3 rotate_;
	
	//}EX΄x
	float sensitivity_;

	friend class Singleton<TPSCamera>;

	TPSCamera();
public:
	~TPSCamera();

	//StateΨθΦ¦Φ
	std::shared_ptr<State<Camera>> Input(Camera& camera) override;
	void Update(Camera& camera) override;
};