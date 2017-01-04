#pragma once

#include "State.h"
#include "Camera.h"
#include <SimpleMath.h>

class TPSCamera:public State<Camera>,public Singleton<TPSCamera>
{
private:
	const float distance_ = 10;
	DirectX::SimpleMath::Vector3 rotate_;
	float sensitivity_;

	friend class Singleton<TPSCamera>;

	TPSCamera();
public:
	~TPSCamera();

	State<Camera>* Input(Camera& camera) override;
	void Update(Camera& camera) override;
};